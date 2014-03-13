#include "coord_proc.h"
#include "osg_stuff.h"

CoordProcessor* CoordProcessor::m_pCoordProcessor = NULL;

void CoordProcessor::UpdateEyeCoord(const osg::Vec2d& x) {
  m_vEyeCoord = x;

  if (m_bCalibration)
    CheckCalibration();

  if (m_bCalibrationFinished)
    ProcessCoord();
}

void CoordProcessor::CheckCalibration() {
  double dt =  difftime(time(NULL), m_tChangePointTime);
  double max_time = 10.0;
  int progress = dt / max_time * 100.0;
  if (dt > max_time)
    NextCheckPoint();

  if (!m_bCalibration)
    return;

  if (dt > max_time/2.0)  // feature
    m_vCheckPoints[m_iCurrentCheckpoint].AddCoord(m_vEyeCoord);

  // for debug
  root->removeChild(1);
  //root->removeChildren(1, root->getNumChildren());
  root->addChild(DrawProgressPoint(
        NormalizedToScreen(GetCurrentCheckPoint()->n_coord), progress));
}

void CoordProcessor::ProcessCoord() {
  osg::Vec2d& p = m_vEyeCoord;
  osg::Vec2d p_l, p_r;
  CheckPoint cp_up_l, cp_up_r, cp_down_l, cp_down_r;
  int i_left;
  int cp_size = m_vCheckPoints.size();
  for (int i=0; i<cp_size/2-1; i++) {
    if (p.x() > m_vCheckPoints[i+1].eye_coord.x() ||
        i == cp_size/2-2) {
      cp_up_l = m_vCheckPoints[cp_size-1-i-1];
      cp_up_r = m_vCheckPoints[cp_size-1-i];
      cp_down_l = m_vCheckPoints[i+1];
      cp_down_r = m_vCheckPoints[i];
      //i_left = i;
      break;
    }
  }
  double up_d_x = p.x() - cp_up_l.eye_coord.x();
  double down_d_x = p.x() - cp_down_l.eye_coord.x();
  up_d_x /= cp_up_r.eye_coord.x() - cp_up_l.eye_coord.x();
  down_d_x /= cp_down_r.eye_coord.x() - cp_down_l.eye_coord.x();
  osg::Vec2d p_up_n = cp_up_l.n_coord +
    (cp_up_r.n_coord - cp_up_l.n_coord)*up_d_x;
  osg::Vec2d p_down_n = cp_down_l.n_coord +
    (cp_down_r.n_coord - cp_down_l.n_coord)*down_d_x;

  double up_y = cp_up_l.eye_coord.y() + cp_up_r.eye_coord.y();
  up_y /= 2.0;
  double down_y = cp_down_l.eye_coord.y() + cp_down_r.eye_coord.y();
  down_y /= 2.0;
  double y_coef = (p.y() - down_y)/(up_y - down_y);
  m_vNormalizedCoord = p_down_n + (p_up_n - p_down_n)*y_coef;

  // for debug
  root->removeChild(1);
  //root->removeChildren(1, root->getNumChildren());
  root->addChild(DrawProgressPoint(
        NormalizedToScreen(m_vNormalizedCoord), 100));
}
