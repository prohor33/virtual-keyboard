#include "osg_stuff.h"

osg::Camera* createHUDCamera( double left, double right,
                             double bottom, double top ) {
  osg::ref_ptr<osg::Camera> camera = new osg::Camera;
  camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
  camera->setClearMask( GL_DEPTH_BUFFER_BIT );
  camera->setRenderOrder( osg::Camera::POST_RENDER );
  camera->setAllowEventFocus( false );
  camera->setProjectionMatrix( osg::Matrix::ortho2D(left, right, bottom, top) );
  camera->getOrCreateStateSet()->setMode( GL_LIGHTING,
      osg::StateAttribute::OFF );
  return camera.release();
}

osg::ref_ptr<osg::Vec3Array>
PointVert(int progress, int approx, double radius)
{
  const double angle( osg::PI * 2. / (double) approx );
  osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
  int idx;
  double x(0.), y(0.), z(0.);
  double x_n, y_n;

  for( idx=0; idx<approx*progress/100; idx++)
  {
    double cosAngle = cos(idx*angle);
    double sinAngle = sin(idx*angle);
    double cosAngle_n = cos((idx+1)*angle);
    double sinAngle_n = sin((idx+1)*angle);

    x = radius * sinAngle;
    y = radius * cosAngle;
    x_n = radius * sinAngle_n;
    y_n = radius * cosAngle_n;

    v->push_back(osg::Vec3(x, y, z));
    v->push_back(osg::Vec3(0, 0, z));
    v->push_back(osg::Vec3(x_n, y_n, z));
  }

  return v;
}

osg::ref_ptr<osg::Node>
DrawProgressPoint(osg::Vec2d coord, int progress)
{
  int approx = 50;
  int radius = 20;
  osg::Geode* geode = new osg::Geode;

  osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
  osg::ref_ptr<osg::Vec3Array> v = PointVert(progress, approx, radius);
  geom->setVertexArray( v );

  osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
  c->push_back( osg::Vec4( 1., 0.6, 0.6, 1. ) );
  geom->setColorArray( c );
  geom->setColorBinding( osg::Geometry::BIND_OVERALL );
  geom->addPrimitiveSet( new osg::DrawArrays( GL_TRIANGLES, 0,
        (approx*progress/100.0)*3 ) );

  geode->addDrawable( geom );
  osg::MatrixTransform *tx = new osg::MatrixTransform();
  tx->setMatrix(osg::Matrix::translate(coord.x(), coord.y(), 0));
  tx->addChild(geode);

  return tx;
}
