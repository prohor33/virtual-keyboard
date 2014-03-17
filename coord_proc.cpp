#include "coord_proc.h"
#include "osg_stuff.h"
#include "manager.h"

CoordProcessor* CoordProcessor::m_pCoordProcessor = NULL;

void CoordProcessor::StartCalibration() {
  m_bCalibration = true;
  m_bCalibrationFinished = false;
  m_iCurrentCheckpoint = 0;
  m_tChangePointTime = osg::Timer::instance()->tick();
  cout << "Start calibration." << endl;
  MANAGER->SetMessage("Calibration...");
  m_vCheckPoints[m_iCurrentCheckpoint].StartAdding();
}

void CoordProcessor::EndCalibration() {
  m_bCalibration = false;
  m_bCalibrationFinished = true;
  m_iCurrentCheckpoint = -1;
  MANAGER->SetMessage("Ready to work");
  cout << "End calibration." << endl;
}

void CoordProcessor::NextCheckPoint() {
  if (!m_vCheckPoints[m_iCurrentCheckpoint].n) {
    cout << "Cannot go to the next checkpoint, cause there is no data yet." << endl;
    cout << "Stay at this point for a while" << endl;
    m_tChangePointTime = osg::Timer::instance()->tick();
    return;
  }
  m_vCheckPoints[m_iCurrentCheckpoint].EndAdding();
  
  cout << "Check point eye_coord: ";
  cout << m_vCheckPoints[m_iCurrentCheckpoint].eye_coord.x() <<
  " " << m_vCheckPoints[m_iCurrentCheckpoint].eye_coord.y() <<
  endl;
  
  m_iCurrentCheckpoint++;
  m_vCheckPoints[m_iCurrentCheckpoint].StartAdding();
  if (m_iCurrentCheckpoint >= m_vCheckPoints.size()) {
    EndCalibration();
    return;
  }
  m_tChangePointTime = osg::Timer::instance()->tick();
  cout << "Next checkpoint" << endl;
}

void CoordProcessor::UpdateEyeCoord(const osg::Vec2d& x) {
  m_vEyeCoord = x;

  double dt = osg::Timer::instance()->delta_s(m_tLastDataRecieveTime,
                                              osg::Timer::instance()->tick());
  m_tLastDataRecieveTime = osg::Timer::instance()->tick();
  double coef = 0.9;
  if (dt == 0)
    dt = 1e-6;
  m_iDPS = coef * m_iDPS + (1.0 - coef) * 1.0 / dt;
//  cout << "dt = " << dt << " m_iDPS = " << m_iDPS << endl;
  
  if (m_bCalibration)
    CheckCalibration();

  if (m_bCalibrationFinished)
    ProcessCoord();
}

void CoordProcessor::CheckCalibration() {
  double dt =  osg::Timer::instance()->delta_s(m_tChangePointTime,
                                               osg::Timer::instance()->tick());
  double max_time = 8.0;
  
  if (dt > max_time) {
    NextCheckPoint();
    dt =  osg::Timer::instance()->delta_s(m_tChangePointTime,
                                                 osg::Timer::instance()->tick());
  }

  int progress = dt / max_time * 100.0;
  GetProgressPoint()->progress = progress;
  
  if (!m_bCalibration)
    return;
  
  if (dt > max_time/2.0)  // feature
    m_vCheckPoints[m_iCurrentCheckpoint].AddCoord(m_vEyeCoord);
}

void CoordProcessor::ProcessCoord() {
  osg::Vec2d& p = m_vEyeCoord;
  osg::Vec2d p_l, p_r;
  CheckPoint cp_up_l, cp_up_r, cp_down_l, cp_down_r;
  int cp_size = m_vCheckPoints.size();
  //cout << "proc coord" << endl;
  for (int i=0; i<cp_size/2-1; i++) {
    if (p.x() > m_vCheckPoints[i+1].eye_coord.x() ||
        i == cp_size/2-2) {
      cp_up_l = m_vCheckPoints[cp_size-1-i-1];
      cp_up_r = m_vCheckPoints[cp_size-1-i];
      cp_down_l = m_vCheckPoints[i+1];
      cp_down_r = m_vCheckPoints[i];
      break;
    }
  }
  //cout << "after loop" << endl;
  double up_d_x = p.x() - cp_up_l.eye_coord.x();
  double down_d_x = p.x() - cp_down_l.eye_coord.x();
  if (cp_up_r.eye_coord.x() == cp_up_l.eye_coord.x())
    cp_up_r.eye_coord.x() = cp_up_l.eye_coord.x() + 1e-6;
  up_d_x /= cp_up_r.eye_coord.x() - cp_up_l.eye_coord.x();
  if (cp_down_r.eye_coord.x() == cp_down_l.eye_coord.x())
    cp_down_r.eye_coord.x() = cp_down_l.eye_coord.x() + 1e-6;
  down_d_x /= cp_down_r.eye_coord.x() - cp_down_l.eye_coord.x();
  osg::Vec2d p_up_n = cp_up_l.n_coord +
    (cp_up_r.n_coord - cp_up_l.n_coord)*up_d_x;
  osg::Vec2d p_down_n = cp_down_l.n_coord +
    (cp_down_r.n_coord - cp_down_l.n_coord)*down_d_x;

  double up_y = cp_up_l.eye_coord.y() + cp_up_r.eye_coord.y();
  up_y /= 2.0;
  double down_y = cp_down_l.eye_coord.y() + cp_down_r.eye_coord.y();
  down_y /= 2.0;
  if (up_y == down_y)
    up_y = down_y + 1e-6;
  double y_coef = (p.y() - down_y)/(up_y - down_y);
  m_vNormalizedCoord = p_down_n + (p_up_n - p_down_n)*y_coef;
}
