#pragma once

#include "main.h"

class Button {
public:
  Button(osg::Vec2d pos, osg::Vec2d size, wstring symbol, string img_name) :
  m_vPos(pos),
  m_vSize(size)
  {
    m_vSymbol.push_back(symbol);
    m_cImgName.push_back(img_name);
  };
  ~Button() {};
  void Draw(osg::ref_ptr<osg::Group> root);
  void Push();
  
private:
  osg::Vec2d m_vPos;
  osg::Vec2d m_vSize;
  vector<wstring> m_vSymbol; // for different localization
  vector<string> m_cImgName;
};