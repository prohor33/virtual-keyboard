cmake_minimum_required(VERSION 2.6)

  PROJECT(virtual-keyboard)

  INCLUDE(FindZeroMQ.cmake)

  SET(PROTOBUF_LIBRARY "/opt/local/lib/libprotobuf.dylib")

  FIND_PACKAGE(OpenThreads)
  FIND_PACKAGE(osg)
  FIND_PACKAGE(osgDB)
  FIND_PACKAGE(osgViewer)
  FIND_PACKAGE(osgGA)
  FIND_PACKAGE(osgText)
  FIND_PACKAGE(osgUtil)

  SET(SOURCES
          button.cpp
          coord.pb.cc
          coord_proc.cpp
          data_receiver.cpp
          keyboard.cpp
          main.cpp
          osg_stuff.cpp
          two_dim_manipulator.cpp
          manager.cpp
          callbacks.cpp
          )

  INCLUDE_DIRECTORIES(${ZEROMQ_INCLUDE_DIRS}
                      ${OPENTHREADS_INCLUDE_DIR}
                      ${OSG_INCLUDE_DIR})

  LINK_DIRECTORIES(${OSG_LIB_DIR})

  ADD_EXECUTABLE(keyboard ${SOURCES})

  TARGET_LINK_LIBRARIES(keyboard
                        ${PROTOBUF_LIBRARY}
                        ${ZEROMQ_LIBRARIES}
                        ${OSG_LIBRARY}
                        ${OSGUTIL_LIBRARY}
                        ${OSGDB_LIBRARY}
                        ${OSGVIEWER_LIBRARY}
                        ${OPENTHREADS_LIBRARY}
                        ${OSGGA_LIBRARY}
                        ${OSGTEXT_LIBRARY}
                        ${OSGUTIL_LIBRARY})
