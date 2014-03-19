#include "osg_stuff.h"
#include "manager.h"
#include "callbacks.h"

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
  if (approx < 3)
    approx = 3;
  if (radius <= 0)
    radius = 1e-4;
  if (approx*progress/100 < 1)
    progress = 100/approx;
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
  osg::ref_ptr<osg::DrawArrays> points =
  new osg::DrawArrays( GL_TRIANGLES, 0, (approx*progress/100.0)*3 );
  points->setDataVariance(osg::Object::DYNAMIC);
  geom->addPrimitiveSet( points.get() );
  geom->setUseDisplayList(false);
  geom->setDataVariance(osg::Object::DYNAMIC);
  geom->setUpdateCallback(new ProgressPointCallback);
  geode->addDrawable(geom);
  osg::MatrixTransform *tx = new osg::MatrixTransform();
  tx->setMatrix(osg::Matrix::translate(coord.x(), coord.y(), 0));
  tx->setDataVariance(osg::Object::DYNAMIC);
  tx->addChild(geode);

  return tx;
}

osg::ref_ptr<osg::Node> DrawDPSText() {
  osg::ref_ptr<osg::Geode> HUDGeode = new osg::Geode();
  osg::ref_ptr<osgText::Text> textDPS = new osgText::Text();
  textDPS->setCharacterSize(20);
  textDPS->setFont("/System/Library/Fonts/Apple Symbols.ttf");
  HUDGeode->addDrawable(textDPS);
  textDPS->setText("DPS: Data not available");
  textDPS->setAxisAlignment(osgText::Text::SCREEN);
  textDPS->setPosition( osg::Vec3(10,WND_SZ.y()-50,-1.5) );
  textDPS->setColor( osg::Vec4(69.0/255.0, 87.0/225.0, 87/255.0, 1) );
  textDPS->setDataVariance(osg::Object::DYNAMIC);
  textDPS->setUpdateCallback(new DPSUpdateCallback);
  return HUDGeode;
}

osg::ref_ptr<osg::Node> DrawMessageText() {
  osg::ref_ptr<osg::Geode> HUDGeode = new osg::Geode();
  osg::ref_ptr<osgText::Text> text = new osgText::Text();
  text->setCharacterSize(20);
  text->setFont("/System/Library/Fonts/Apple Symbols.ttf");
  HUDGeode->addDrawable(text);
  text->setText("Message: ...");
  text->setAxisAlignment(osgText::Text::SCREEN);
  text->setPosition( osg::Vec3(10,WND_SZ.y()-80,-1.5) );
  text->setColor( osg::Vec4(69.0/255.0, 87.0/225.0, 87/255.0, 1) );
  text->setDataVariance(osg::Object::DYNAMIC);
  text->setUpdateCallback(new MessageUpdateCallback);
  return HUDGeode;
}

osg::ref_ptr<osg::Node> DrawInputText() {
  osg::ref_ptr<osg::Geode> HUDGeode = new osg::Geode();
  osg::ref_ptr<osgText::Text> text = new osgText::Text();
  text->setCharacterSize(40);
  text->setFont("/System/Library/Fonts/LiberationSerif-Regular.ttf");
  HUDGeode->addDrawable(text);
  
  std::wstring wide = std::wstring(L"Русский текст!");
  text->setText(wide.c_str());
  text->setAxisAlignment(osgText::Text::SCREEN);
  text->setPosition( osg::Vec3(320,WND_SZ.y()-83,-1) );
  text->setColor( osg::Vec4(0.0/255.0, 0.0/225.0, 0.0/255.0, 1) );
  text->setDataVariance(osg::Object::DYNAMIC);
  text->setUpdateCallback(new InputTextUpdateCallback);
  return HUDGeode;
}

osg::ref_ptr<osg::Node> DrawTexture(string img_name, osg::Vec2d pos, osg::Vec2d size) {
  osg::ref_ptr<osg::Geode> HUDGeode = new osg::Geode();
  // Set up geometry for the HUD and add it to the HUD
  osg::Geometry* HUDBackgroundGeometry = new osg::Geometry();
  
  osg::Vec3Array* HUDBackgroundVertices = new osg::Vec3Array;
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x(), pos.y(), -1));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x()+size.x(), pos.y(), -1));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x()+size.x(), pos.y()+size.y(), -1));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x(), pos.y()+size.y(), -1));
  
  osg::DrawElementsUInt* HUDBackgroundIndices =
  new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON, 0);
  HUDBackgroundIndices->push_back(0);
  HUDBackgroundIndices->push_back(1);
  HUDBackgroundIndices->push_back(2);
  HUDBackgroundIndices->push_back(3);
  
  osg::Vec4Array* HUDcolors = new osg::Vec4Array;
  HUDcolors->push_back(osg::Vec4(0.8f,0.8f,0.8f,0.8f));
  
  osg::Vec2Array* texcoords = new osg::Vec2Array(4);
  (*texcoords)[0].set(0.0f,0.0f);
  (*texcoords)[1].set(1.0f,0.0f);
  (*texcoords)[2].set(1.0f,1.0f);
  (*texcoords)[3].set(0.0f,1.0f);
  
  HUDBackgroundGeometry->setTexCoordArray(0,texcoords);
  osg::Texture2D* HUDTexture = new osg::Texture2D;
  HUDTexture->setDataVariance(osg::Object::DYNAMIC);
  osg::Image* hudImage;
  hudImage = osgDB::readImageFile(img_name);
  if (!hudImage) {
    cout << "can't read image" << endl;
  }
  HUDTexture->setImage(hudImage);
  osg::Vec3Array* HUDnormals = new osg::Vec3Array;
  HUDnormals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
  HUDBackgroundGeometry->setNormalArray(HUDnormals);
  HUDBackgroundGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
  HUDBackgroundGeometry->addPrimitiveSet(HUDBackgroundIndices);
  HUDBackgroundGeometry->setVertexArray(HUDBackgroundVertices);
  HUDBackgroundGeometry->setColorArray(HUDcolors);
  HUDBackgroundGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
  
  // Create and set up a state set using the texture from above:
  osg::StateSet* HUDStateSet = new osg::StateSet();
  HUDGeode->setStateSet(HUDStateSet);
  HUDStateSet->
  setTextureAttributeAndModes(0,HUDTexture,osg::StateAttribute::ON);
  
  // For this state set, turn blending on (so alpha texture looks right)
  HUDStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
  
  // Disable depth testing so geometry is draw regardless of depth values
  // of geometry already draw.
  HUDStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
  HUDStateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
  
  // Need to make sure this geometry is draw last. RenderBins are handled
  // in numerical order so set bin number to 11
  HUDStateSet->setRenderBinDetails( 11, "RenderBin");
  
  HUDGeode->addDrawable(HUDBackgroundGeometry);
  return HUDGeode;
}


osg::ref_ptr<osg::Node> DrawPolygon(osg::Vec2d pos, osg::Vec2d size, osg::Vec4d color) {
  osg::ref_ptr<osg::Geode> HUDGeode = new osg::Geode();
  // Set up geometry for the HUD and add it to the HUD
  osg::Geometry* HUDBackgroundGeometry = new osg::Geometry();
  
  osg::Vec3Array* HUDBackgroundVertices = new osg::Vec3Array;
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x(), pos.y(), -2));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x()+size.x(), pos.y(), -2));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x()+size.x(), pos.y()+size.y(), -2));
  HUDBackgroundVertices->push_back(osg::Vec3(pos.x(), pos.y()+size.y(), -2));
  
  osg::DrawElementsUInt* HUDBackgroundIndices =
  new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON, 0);
  HUDBackgroundIndices->push_back(0);
  HUDBackgroundIndices->push_back(1);
  HUDBackgroundIndices->push_back(2);
  HUDBackgroundIndices->push_back(3);
  
  osg::Vec4Array* HUDcolors = new osg::Vec4Array;
  HUDcolors->push_back(color);
  
  osg::Vec3Array* HUDnormals = new osg::Vec3Array;
  HUDnormals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
  HUDBackgroundGeometry->setNormalArray(HUDnormals);
  HUDBackgroundGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
  HUDBackgroundGeometry->addPrimitiveSet(HUDBackgroundIndices);
  HUDBackgroundGeometry->setVertexArray(HUDBackgroundVertices);
  HUDBackgroundGeometry->setColorArray(HUDcolors);
  HUDBackgroundGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

  osg::StateSet* HUDStateSet = new osg::StateSet();
  HUDGeode->setStateSet(HUDStateSet);
  // For this state set, turn blending on (so alpha texture looks right)
  HUDStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
  
  // Disable depth testing so geometry is draw regardless of depth values
  // of geometry already draw.
  HUDStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
  HUDStateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
  
  // Need to make sure this geometry is draw last. RenderBins are handled
  // in numerical order so set bin number to 11
//  HUDStateSet->setRenderBinDetails( 11, "RenderBin");
  
  HUDGeode->addDrawable(HUDBackgroundGeometry);
  return HUDGeode;
}


