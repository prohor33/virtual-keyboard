#include "keyboard.h"
#include "button.h"

void Keyboard::AddButton(string name, wstring symbol, osg::Vec2d pos,
                         osg::Vec2d size, string img_name) {
  Button* btn = new Button(name, pos, size, symbol, img_name);
  m_mButtons[name] = std::shared_ptr<Button>(btn);
}

void Keyboard::Draw() {
  for (map<string, shared_ptr<Button> >::iterator it=m_mButtons.begin(); it!=m_mButtons.end(); ++it) {
    (*it).second->Draw(m_gRoot);
  }
}

void Keyboard::SelectButton(string name) {
  for (map<string, shared_ptr<Button> >::iterator it=m_mButtons.begin(); it!=m_mButtons.end(); ++it) {
    (*it).second->Unselect();
  }
  if (m_mButtons.find(name) != m_mButtons.end())
    m_mButtons[name]->Select();
}
void Keyboard::PushButton(string name) {
  if (m_mButtons.find(name) != m_mButtons.end())
    m_mButtons[name]->Push();
}