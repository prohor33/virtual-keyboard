#pragma once

#include "main.h"
#include <OpenThreads/Thread>
#include <zmq.hpp>
#include "coord.pb.h"
#include "coord_proc.h"

using namespace std;

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
};

#define DATA_RECEIVER DataReceiver::Instance()

