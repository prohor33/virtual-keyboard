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

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

const osg::Vec2d NormalizedToScreen(const osg::Vec2d vec);
