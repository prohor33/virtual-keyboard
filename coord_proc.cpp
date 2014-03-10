#include "coord_proc.h"

CoordProcessor* CoordProcessor::m_pCoordProcessor = NULL;

void CoordProcessor::UpdateCoord(const osg::Vec2d& x) {
  m_vCoord = x;
}
