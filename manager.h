#pragma once

#include "main.h"

class Manager
{
public:
  virtual ~Manager() {}
  static Manager* Instance() {
    if (!m_pManager)
      m_pManager = new Manager();
    return m_pManager;
  }
  
  const osg::Vec2d& GetWindowSize() const {
    return m_vWindowSize;
  }
  const string& GetMessage() const {
    return m_sMessage;
  }
  void SetMessage(const string& msg) {
    m_sMessage = msg;
  }
  void SetViewer(osgViewer::Viewer* viewer) {
    m_pViewer = viewer;
  }
  osgViewer::Viewer* GetViewer() {
    return m_pViewer;
  }
private:
  Manager() :
//  m_vWindowSize(800, 500)
  m_vWindowSize(1440, 900),
  m_pViewer(NULL)
  {}
  
  static Manager* m_pManager;
  osg::Vec2d m_vWindowSize;
  string m_sMessage;
  osgViewer::Viewer* m_pViewer;
};

#define MANAGER Manager::Instance()
#define WND_SZ MANAGER->GetWindowSize()

