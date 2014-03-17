#include "data_receiver.h"

DataReceiver* DataReceiver::m_pDataReceiver = NULL;

void DataReceiver::run()
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  tutorial::Coord coord;

  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind ("tcp://*:5555");

  while (!m_bDone)
  {
    zmq::message_t resultset(100);

    socket.recv (&resultset);

    if (!coord.ParseFromArray(resultset.data(), resultset.size())) {
      cerr << "Failed to parse address book." << endl;
      return;
    }

//    COORD_PROC->UpdateEyeCoord(osg::Vec2d(0.5, 0.5));
    COORD_PROC->UpdateEyeCoord(osg::Vec2d(coord.x(), coord.y()));
    //cout << "x = " << coord.x() << " y = " << coord.y() << endl;

    //  Send reply back to client
    zmq::message_t reply(5);
    memcpy((void *) reply.data (), "World", 5);
    socket.send(reply);

//    OpenThreads::Thread::microSleep(50);
  }
}

