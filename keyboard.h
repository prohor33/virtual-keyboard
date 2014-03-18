#pragma once

#include "main.h"

class Button;

class Keyboard {
public:
  static Keyboard* Instance() {
    static Keyboard* pKeyboard = NULL;
    if (!pKeyboard)
      pKeyboard = new Keyboard();
    return pKeyboard;
  }

  void AddButton(string symbol, osg::Vec2d pos,
                 osg::Vec2d size, string img_name);
//  void AddSymbol(main_symbol, opt_symbol, opt_img_name);
  void Draw();
  void SetRoot(const osg::ref_ptr<osg::Group>& _root) {
    root = _root;
  }
  
private:
  Keyboard() {
    AddButton("A", osg::Vec2d(10, 10), osg::Vec2d(64, 64), "A.jpg");
  };
  vector<std::shared_ptr<Button> > m_vButtons;
  osg::ref_ptr<osg::Group> root;
};

#define KEYBOARD Keyboard::Instance()