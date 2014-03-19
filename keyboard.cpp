#include "keyboard.h"
#include "button.h"

void Keyboard::AddButton(wstring symbol, osg::Vec2d pos,
                         osg::Vec2d size, string img_name) {
  Button* btn = new Button(pos, size, symbol, img_name);
  btn->Push();
  m_vButtons.push_back(std::shared_ptr<Button>(btn));
}

void Keyboard::Draw() {
  for (vector<shared_ptr<Button> >::iterator it=m_vButtons.begin(); it!=m_vButtons.end(); ++it) {
    (*it)->Draw(m_gRoot);
  }
}