#include "main.h"
#include "two_dim_manipulator.h"
#include "osg_stuff.h"
#include "data_receiver.h"
#include "coord_proc.h"

osg::Vec2 window_size(800, 500);

const osg::Vec2d NormalizedToScreen(const osg::Vec2d vec) {
  return osg::Vec2d(vec.x()*window_size.x(), vec.y()*window_size.y());
}

int main (int argc, char **argv) {

  osg::Camera* camera = createHUDCamera(0, window_size.x(),
                                        0, window_size.y());

  osg::Group* root = new osg::Group;
  root->addChild(camera);

  osgViewer::Viewer viewer;

  viewer.getCamera()->setClearColor(
      osg::Vec4(0.8f, 0.9f, 0.7f, 1.0f));
  viewer.setSceneData(root);
	viewer.addEventHandler( new PickHandler );
	viewer.setCameraManipulator( new TwoDimManipulator );
	viewer.setUpViewInWindow(50, 50, 50 + window_size.x(),
                           50 + window_size.y(), 0);

  // change window title
  viewer.realize();
  typedef osgViewer::Viewer::Windows Windows;
  Windows windows;
  viewer.getWindows(windows);
  for (Windows::iterator window = windows.begin();
       window != windows.end(); ++window)
  (*window)->setWindowName("Virtual keyboard");

  DATA_RECEIVER->start();
  COORD_PROC->StartCalibration();
  COORD_PROC->root = camera;

  //camera->addChild(DrawProgressPoint(osg::Vec2d(100, 100), 80));

  viewer.run();

  DATA_RECEIVER->StopWorking();

  return 0;
}
