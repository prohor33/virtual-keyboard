#include "button.h"
#include "osg_stuff.h"
#include "keyboard.h"

void Button::Draw(osg::ref_ptr<osg::Group> root) {
  root->addChild(DrawTexture(m_sName, m_cImgName[0], m_vPos, m_vSize));
}

void Button::Push() {
  if (m_vSymbol.size())
    KEYBOARD->AddToText(m_vSymbol);
  cout << "pushed" << endl;
}

void Button::Select() {
  if (m_bSelected) {
    double dt = osg::Timer::instance()->delta_s(m_tSelectStart, osg::Timer::instance()->tick());
    if (dt > BUTTON_SELECTION_TIME_S) {
      Push();
      Unselect();
    }
    return;
  }
  m_bSelected = true;
  m_tSelectStart = osg::Timer::instance()->tick();
}

void Button::Unselect() {
  m_bSelected = false;
}