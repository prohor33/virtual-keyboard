#pragma once

#include "main.h"

class Button {
public:
  Button(string name, osg::Vec2d pos, osg::Vec2d size, wstring symbol, string img_name) :
  m_sName(name),
  m_vPos(pos),
  m_vSize(size),
  m_vSymbol(symbol),
  m_bSelected(false)
  {
    m_cImgName.push_back(img_name);
  };
  ~Button() {};
  void Draw(osg::ref_ptr<osg::Group> root);
  void Push();
  void Select();
  void Unselect();
  
private:
  string m_sName;
  osg::Vec2d m_vPos;
  osg::Vec2d m_vSize;
  wstring m_vSymbol;
  vector<string> m_cImgName; // for different localization
  bool m_bSelected;
  osg::Timer_t m_tSelectStart;
};