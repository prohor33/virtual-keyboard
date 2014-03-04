#include "osg_stuff.h"

osg::Camera* createHUDCamera( double left, double right,
                             double bottom, double top ) {
  osg::ref_ptr<osg::Camera> camera = new osg::Camera;
  camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
 	camera->setClearMask(0);
  camera->setRenderOrder( osg::Camera::POST_RENDER );
  camera->setAllowEventFocus( false );
  camera->setProjectionMatrix( osg::Matrix::ortho2D(left, right,
                                                    bottom, top) );
  return camera.release();
}
