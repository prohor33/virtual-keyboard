#pragma once

#include "main.h"
#include <OpenThreads/Thread>
#include <zmq.hpp>
#include "coord.pb.h"
#include "coord_proc.h"

class DataReceiver : public OpenThreads::Thread
{
public:
  virtual ~DataReceiver() {}
  static DataReceiver* Instance() {
    if (!m_pDataReceiver)
      m_pDataReceiver = new DataReceiver();
    return m_pDataReceiver;
  }

  virtual void run();
  void StopWorking() { m_bDone = true; }

protected:
  DataReceiver() : m_bDone(false) {}

  bool m_bDone;
  static DataReceiver* m_pDataReceiver;
  osg::Vec2d m_vCoord;
};

#define DATA_RECEIVER DataReceiver::Instance()

