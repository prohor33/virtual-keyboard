cmake_minimum_required(VERSION 2.6)

  PROJECT(virtual-keyboard)

  FIND_PACKAGE(OpenThreads)
  FIND_PACKAGE(osg)
  FIND_PACKAGE(osgDB)
  FIND_PACKAGE(osgViewer)
  FIND_PACKAGE(osgGA)

  SET(SOURCES
          button.cpp
          keyboard.cpp
          main.cpp
          osg_stuff.cpp
          two_dim_manipulator.cpp
          )

  INCLUDE_DIRECTORIES(${OPENTHREADS_INCLUDE_DIR} ${OSG_INCLUDE_DIR})

  LINK_DIRECTORIES(${OSG_LIB_DIR})

  ADD_EXECUTABLE(keyboard ${SOURCES})

  TARGET_LINK_LIBRARIES(keyboard ${OSG_LIBRARY} ${OSGUTIL_LIBRARY}
                        ${OSGDB_LIBRARY} ${OSGVIEWER_LIBRARY}
                        ${OPENTHREADS_LIBRARY} ${OSGGA_LIBRARY})
