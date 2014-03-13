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
  void StartCalibration() {
    m_bCalibration = true;
    m_bCalibrationFinished = false;
    m_iCurrentCheckpoint = 0;
    m_tChangePointTime = time(NULL);
    cout << "Start calibration." << endl;
    m_vCheckPoints[m_iCurrentCheckpoint].StartAdding();
  }
  void EndCalibration() {
    m_bCalibration = false;
    m_bCalibrationFinished = true;
    m_iCurrentCheckpoint = -1;
    cout << "End calibration." << endl;
  }
  void NextCheckPoint() {
    m_vCheckPoints[m_iCurrentCheckpoint].EndAdding();

    cout << m_vCheckPoints[m_iCurrentCheckpoint].eye_coord.x() <<
      " " << m_vCheckPoints[m_iCurrentCheckpoint].eye_coord.y() <<
      endl;

    m_iCurrentCheckpoint++;
    m_vCheckPoints[m_iCurrentCheckpoint].StartAdding();
    if (m_iCurrentCheckpoint >= m_vCheckPoints.size()) {
      EndCalibration();
      return;
    }
    m_tChangePointTime = time(NULL);
    cout << "Next checkpoint" << endl;
  }
  CheckPoint* GetCurrentCheckPoint() {
    if (!m_bCalibration)
      return NULL;
    return &m_vCheckPoints[m_iCurrentCheckpoint];
  }

  // lets try
  osg::Group* root;

 protected:
  CoordProcessor() :
  m_bCalibration(false),
  m_bCalibrationFinished(false),
  m_iCurrentCheckpoint(-1)
  {
    // Initialize checkpoints
    m_vCheckPoints.push_back(osg::Vec2d(0.1, 0.1));
    //m_vCheckPoints.push_back(osg::Vec2d(0.5, 0.1));
    m_vCheckPoints.push_back(osg::Vec2d(0.9, 0.1));
    m_vCheckPoints.push_back(osg::Vec2d(0.9, 0.9));
    //m_vCheckPoints.push_back(osg::Vec2d(0.5, 0.9));
    m_vCheckPoints.push_back(osg::Vec2d(0.1, 0.9));
  };
  void ProcessCoord();

  static CoordProcessor* m_pCoordProcessor;
  osg::Vec2d m_vEyeCoord;
  osg::Vec2d m_vNormalizedCoord;

  bool m_bCalibration;
  bool m_bCalibrationFinished;
  vector<CheckPoint> m_vCheckPoints;
  int m_iCurrentCheckpoint;

  time_t m_tChangePointTime;

  ProgressPoint m_cProgressPoint;
};

#define COORD_PROC CoordProcessor::Instance()
