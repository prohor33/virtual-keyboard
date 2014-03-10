#include "coord_proc.h"

CoordProcessor* CoordProcessor::m_pCoordProcessor = NULL;

void CoordProcessor::UpdateEyeCoord(const osg::Vec2d& x) {
  m_vEyeCoord = x;

  CheckCalibration();
}

void CoordProcessor::CheckCalibration() {
  if (!m_bCalibration)
    return;
  double dt =  difftime(time(NULL), m_tChangePointTime);
  if (dt > 3.0)
    NextCheckPoint();

  if (!m_bCalibration)
    return;

  m_vCheckPoints[m_iCurrentCheckpoint].AddCoord(m_vEyeCoord);
}
