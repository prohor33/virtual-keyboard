#pragma once

#include "main.h"

class Button {
public:
  Button() {};
  ~Button() {};
  void Draw(osg::ref_ptr<osg::Group> root);

  osg::Vec2d pos;
  osg::Vec2d size;
  vector<string> symbol; // for different localization
  vector<string> img_name;
};