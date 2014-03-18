#include "keyboard.h"
#include "button.h"

void Keyboard::AddButton(string symbol, osg::Vec2d pos,
                         osg::Vec2d size, string img_name) {
  Button* btn = new Button();
  btn->pos = pos;
  btn->size = size;
  btn->symbol.push_back(symbol);
  btn->img_name.push_back(img_name);
  m_vButtons.push_back(std::shared_ptr<Button>(btn));
}

void Keyboard::Draw() {
  for (vector<shared_ptr<Button> >::iterator it=m_vButtons.begin(); it!=m_vButtons.end(); ++it) {
    (*it)->Draw(root);
  }
}