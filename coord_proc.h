#pragma once

#include "main.h"
#include "data_receiver.h"

class CoordProcessor {
 public:
  ~CoordProcessor() {};
  static CoordProcessor* Instance() {
    if (!m_pCoordProcessor)
      m_pCoordProcessor = new CoordProcessor();
    return m_pCoordProcessor;
  }
  void UpdateCoord(const osg::Vec2d&);
  const osg::Vec2d& GetCoord() {
    return m_vCoord;
  }

 protected:
  CoordProcessor() {};
  static CoordProcessor* m_pCoordProcessor;
  osg::Vec2d m_vCoord;
};

#define COORD_PROC CoordProcessor::Instance()
