#pragma once

#include "main.h"
#include "data_receiver.h"

class CheckPoint {
 public:
  CheckPoint(osg::Vec2d x=osg::Vec2d()) :
  n_coord(x) {};

  void StartAdding() {
    n = 0;
  }
  void AddCoord(const osg::Vec2d& x) {
    eye_coord += x;
    n++;
  }
  void EndAdding() {
    eye_coord /= n;
  }

  osg::Vec2d eye_coord, n_coord;
  int n;
};

class ProgressPoint {
 public:
   ProgressPoint() :
     size(10),
     visible(false),
     progress(0)
  {};

   osg::Vec2d coord;
   double size;
   int progress;
   bool visible;
};

class CoordProcessor {
 public:
  ~CoordProcessor() {};
  static CoordProcessor* Instance() {
    if (!m_pCoordProcessor)
      m_pCoordProcessor = new CoordProcessor();
    return m_pCoordProcessor;
  }
  void UpdateEyeCoord(const osg::Vec2d&);
  void CheckCalibration();

  const osg::Vec2d& GetNormalizedCoord() {
    return m_vNormalizedCoord;
  }
  const osg::Vec2d& GetEyeCoord() {
    return m_vEyeCoord;
  }
  osg::Vec2d GetNormalizedCoordScr() {
    if (m_bCalibrationFinished)
      return NormalizedToScreen(m_vNormalizedCoord);
    else if (m_bCalibration)
      return NormalizedToScreen(m_vCheckPoints[m_iCurrentCheckpoint].n_coord);
    return osg::Vec2d();
  }
  
  void StartCalibration();
  void EndCalibration();
  void NextCheckPoint();
  CheckPoint* GetCurrentCheckPoint() {
    if (!m_bCalibration)
      return NULL;
    return &m_vCheckPoints[m_iCurrentCheckpoint];
  }
  int GetDPS() const {
    return m_iDPS;
  }
  ProgressPoint* GetProgressPoint() {
    return &m_cProgressPoint;
  }

 protected:
  CoordProcessor() :
  m_bCalibration(false),
  m_bCalibrationFinished(false),
  m_iCurrentCheckpoint(-1),
  m_iDPS(0)
  {
    // Initialize checkpoints
    m_vCheckPoints.push_back(osg::Vec2d(0.1, 0.1));
    m_vCheckPoints.push_back(osg::Vec2d(0.5, 0.1));
    m_vCheckPoints.push_back(osg::Vec2d(0.9, 0.1));
    m_vCheckPoints.push_back(osg::Vec2d(0.9, 0.9));
    m_vCheckPoints.push_back(osg::Vec2d(0.5, 0.9));
    m_vCheckPoints.push_back(osg::Vec2d(0.1, 0.9));
    
    m_tLastDataRecieveTime = osg::Timer::instance()->tick();
  };
  void ProcessCoord();

  static CoordProcessor* m_pCoordProcessor;
  osg::Vec2d m_vEyeCoord;
  osg::Vec2d m_vNormalizedCoord;

  bool m_bCalibration;
  bool m_bCalibrationFinished;
  vector<CheckPoint> m_vCheckPoints;
  int m_iCurrentCheckpoint;

  osg::Timer_t m_tChangePointTime;
  osg::Timer_t m_tLastDataRecieveTime;

  ProgressPoint m_cProgressPoint;
  
  int m_iDPS;
};

#define COORD_PROC CoordProcessor::Instance()
