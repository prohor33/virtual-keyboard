#pragma once

#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>
#include <osg/LineWidth>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <osg/io_utils>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

const osg::Vec2d NormalizedToScreen(const osg::Vec2d vec);

#define BUTTON_SELECTION_TIME_S 3.0
#define CHECKPOINT_TIME_S 6.0
