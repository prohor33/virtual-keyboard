#pragma once

#include "main.h"

class Button;

class Keyboard {
public:
  static Keyboard* Instance() {
    static Keyboard* pKeyboard = NULL;
    if (!pKeyboard) {
      pKeyboard = new Keyboard();
    }
    return pKeyboard;
  }

  void AddButton(string name, wstring symbol, osg::Vec2d pos,
                 osg::Vec2d size, string img_name);
  void AddSymbol(wstring main_symbol, wstring opt_symbol, string opt_img_name) {}
  void Draw();
  void SetRoot(const osg::ref_ptr<osg::Group>& root) {
    m_gRoot = root;
  }
  const wstring& GetInputText() {
    return m_sInputText;
  }
  void AddToText(const wstring& str) {
    m_sInputText += str;
  }
  void ClearTheText() {
    m_sInputText.clear();
  }
  void SelectButton(string name);
  void PushButton(string name);
  void UnselcetAllButtons() {}
  
  void Initialize() {
    osg::Vec2d btn_size(10, 10);
    osg::Vec2d indent(2, 2);
    for (int i=0; i<10; i++) {
      for (int j=0; j<4; j++) {
        AddButton("A", L"Ф", osg::Vec2d(i*btn_size.x() + (i+1)*indent.x(),
                                   j*btn_size.y() + (j+1)*indent.y()), btn_size, "A.jpg");
      }
    }
  }
  
private:
  Keyboard() :
    m_sInputText(L"Привет мир!") {};

  map<string, std::shared_ptr<Button> > m_mButtons;
  osg::ref_ptr<osg::Group> m_gRoot;
  wstring m_sInputText;
};

#define KEYBOARD Keyboard::Instance()