#include "main.h"
#include "two_dim_manipulator.h"
#include "osg_stuff.h"
#include "data_receiver.h"
#include "coord_proc.h"
#include "manager.h"
#include "keyboard.h"

const osg::Vec2d NormalizedToScreen(const osg::Vec2d vec) {
  return osg::Vec2d(vec.x()*WND_SZ.x(), vec.y()*WND_SZ.y());
}

int main (int argc, char **argv) {

  osg::Camera* camera = createHUDCamera(0, WND_SZ.x(),
                                        0, WND_SZ.y());

  osg::Group* root = new osg::Group;
  root->addChild(camera);

  osgViewer::Viewer viewer;

  viewer.getCamera()->setClearColor(
      osg::Vec4(0.8f, 0.9f, 0.7f, 1.0f));
  viewer.setSceneData(root);
  viewer.addEventHandler( new osgViewer::StatsHandler );
	viewer.addEventHandler( new PickHandler );
	viewer.setCameraManipulator( new TwoDimManipulator );
	viewer.setUpViewInWindow(50, 50, 50 + WND_SZ.x(),
                           50 + WND_SZ.y(), 0);

  // change window title
  viewer.realize();
  typedef osgViewer::Viewer::Windows Windows;
  Windows windows;
  viewer.getWindows(windows);
  for (Windows::iterator window = windows.begin();
       window != windows.end(); ++window)
  (*window)->setWindowName("Virtual keyboard");

  camera->addChild(DrawDPSText());
  camera->addChild(DrawMessageText());
  camera->addChild(DrawInputText());
  camera->addChild(DrawProgressPoint(osg::Vec2d(100, 100), 50));
  camera->addChild(DrawPolygon(osg::Vec2d(300, WND_SZ.y()-100), osg::Vec2d(600, 60), osg::Vec4d(1.0, 1.0, 1.0, 1.0)));
  
  osg::ref_ptr<osg::Group> gKeyboard = new osg::Group;
  root->addChild(gKeyboard);
  KEYBOARD->Initialize();
  KEYBOARD->SetRoot(gKeyboard);
  KEYBOARD->Draw();
  
  MANAGER->SetViewer(&viewer);
  
  DATA_RECEIVER->start();
  COORD_PROC->StartCalibration();
  
  viewer.run();

  DATA_RECEIVER->StopWorking();

  return 0;
}
