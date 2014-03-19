#include "main.h"
#include "coord_proc.h"
#include "osg_stuff.h"
#include "manager.h"
#include "keyboard.h"

struct DPSUpdateCallback : public osg::Drawable::UpdateCallback
{
	    virtual void update(osg::NodeVisitor*, osg::Drawable* drawable)
	    {
        osgText::Text* text = dynamic_cast<osgText::Text*>(drawable);
        int dps = COORD_PROC->GetDPS();
        string str = std::to_string(dps);
        text->setText("DPS: " + str);
	    }
};

struct MessageUpdateCallback : public osg::Drawable::UpdateCallback
{
  virtual void update(osg::NodeVisitor*, osg::Drawable* drawable)
  {
    osgText::Text* text = dynamic_cast<osgText::Text*>(drawable);
    string str = MANAGER->GetMessage();
    text->setText("State: " + str);
  }
};

struct InputTextUpdateCallback : public osg::Drawable::UpdateCallback
{
  virtual void update(osg::NodeVisitor*, osg::Drawable* drawable)
  {
    osgText::Text* text = dynamic_cast<osgText::Text*>(drawable);
    text->setText(KEYBOARD->GetInputText().c_str());
  }
};

struct ProgressPointCallback : public osg::Drawable::UpdateCallback
{
  virtual void update(osg::NodeVisitor*, osg::Drawable* drawable)
  {
    int approx = 50;
    double radius = 20;
    ProgressPoint* cp = COORD_PROC->GetProgressPoint();
    int progress = cp->progress;
    osg::Vec2d coord = COORD_PROC->GetNormalizedCoordScr();
    osg::Geometry* geom = dynamic_cast<osg::Geometry*>(drawable);
    osg::ref_ptr<osg::Vec3Array> v = PointVert(progress, approx, radius);
    geom->setVertexArray( v );
    osg::PrimitiveSet* ps = geom->getPrimitiveSet(0);
    osg::DrawArrays* points = dynamic_cast<osg::DrawArrays*>(ps);
    points->setCount((approx*progress/100.0)*3);
    points->dirty();
    geom->dirtyBound();
    
    osg::Node* p1 = geom->getParent(0);
    osg::MatrixTransform* tx = dynamic_cast<osg::MatrixTransform*>(p1->getParent(0));
    tx->setMatrix(osg::Matrix::translate(coord.x(), coord.y(), 0));
  }
};