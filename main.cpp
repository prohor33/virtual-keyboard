#include "main.h"
#include "two_dim_manipulator.h"
#include "osg_stuff.h"
#include "data_receiver.h"

using namespace std;

osg::Vec2 main_window_size(800, 500);

int main (int argc, char **argv) {

  osg::Camera* camera = createHUDCamera(0, main_window_size.x(),
                                        0, main_window_size.y());

  osg::Group* root = new osg::Group;
  root->addChild(camera);

  osgViewer::Viewer viewer;

  viewer.getCamera()->setClearColor(
      osg::Vec4(0.8f, 0.9f, 0.7f, 1.0f));
  viewer.setSceneData(root);
	viewer.addEventHandler( new PickHandler );
	viewer.setCameraManipulator( new TwoDimManipulator );
	viewer.setUpViewInWindow(50, 50, 50 + main_window_size.x(),
                           50 + main_window_size.y(), 0);

  // change window title
  viewer.realize();
  typedef osgViewer::Viewer::Windows Windows;
  Windows windows;
  viewer.getWindows(windows);
  for (Windows::iterator window = windows.begin();
       window != windows.end(); ++window)
  (*window)->setWindowName("Virtual keyboard");

  DATA_RECEIVER->start();

  viewer.run();

  DATA_RECEIVER->StopWorking();

  return 0;
}
