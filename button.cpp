#include "button.h"
#include "osg_stuff.h"
#include "keyboard.h"

void Button::Draw(osg::ref_ptr<osg::Group> root) {
  root->addChild(DrawTexture(m_cImgName[0], m_vPos, m_vSize));
}

void Button::Push() {
  if (m_vSymbol.size())
    KEYBOARD->AddToText(m_vSymbol[0]);
}