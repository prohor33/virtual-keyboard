#pragma once

#include "main.h"
#include "coord_proc.h"

osg::Camera* createHUDCamera(double left, double right,
                             double bottom, double top);

osg::ref_ptr<osg::Vec3Array> PointVert(int progress,
    int approx, double radius);
osg::ref_ptr<osg::Node> DrawProgressPoint(osg::Vec2d coord,
    int progress);
osg::ref_ptr<osg::Node> DrawDPSText();
osg::ref_ptr<osg::Node> DrawMessageText();
osg::ref_ptr<osg::Node> DrawTexture(string name, string img_name, osg::Vec2d pos, osg::Vec2d size);
osg::ref_ptr<osg::Node> DrawInputText();
osg::ref_ptr<osg::Node> DrawPolygon(osg::Vec2d pos, osg::Vec2d size, osg::Vec4d color);
bool SelectObject(const double x, const double y, osgViewer::Viewer* viewer);


// class to handle events with a pick
class PickHandler : public osgGA::GUIEventHandler {
public:
  
  PickHandler()
  {}
  
  ~PickHandler() {}
  
  bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);
  
  virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);
  
  void setLabel(const std::string& name)
  {
    cout << name << endl;
  }
  
protected:
};







