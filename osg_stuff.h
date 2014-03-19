#pragma once

#include "main.h"
#include "coord_proc.h"

class PickHandler : public osgGA::GUIEventHandler
{
public:
	PickHandler() : _mX( 0. ),_mY( 0. ) {}
	bool handle( const osgGA::GUIEventAdapter& ea,
              osgGA::GUIActionAdapter& aa ) {
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>( &aa );
		if (!viewer)
			return false;
		switch( ea.getEventType() ) {
			case osgGA::GUIEventAdapter::PUSH:
			case osgGA::GUIEventAdapter::MOVE: {
				_mX = ea.getX();
				_mY = ea.getY();
				return false;
			}
			case osgGA::GUIEventAdapter::RELEASE: {
				if (_mX == ea.getX() && _mY == ea.getY()) {
					if (pick( ea.getX(), ea.getY(), viewer ))
						return true;
				}
				return false;
			}
      case osgGA::GUIEventAdapter::KEYDOWN: {
				switch( ea.getKey() ) {
        case osgGA::GUIEventAdapter::KEY_Down:
          break;
	  		case 'o':
				  break;
        case 's':
            COORD_PROC->StartCalibration();
          break;
				}
				return false;
			}
			default:
			return false;
		}
	}
protected:
  float _mX,_mY;
	int last_time;
	bool pick( const double x, const double y,
            osgViewer::Viewer* viewer ) {

		return false;
	}
};

osg::Camera* createHUDCamera(double left, double right,
                             double bottom, double top);

osg::ref_ptr<osg::Vec3Array> PointVert(int progress,
    int approx, double radius);
osg::ref_ptr<osg::Node> DrawProgressPoint(osg::Vec2d coord,
    int progress);
osg::ref_ptr<osg::Node> DrawDPSText();
osg::ref_ptr<osg::Node> DrawMessageText();
osg::ref_ptr<osg::Node> DrawTexture(string img_name, osg::Vec2d pos, osg::Vec2d size);
osg::ref_ptr<osg::Node> DrawInputText();
osg::ref_ptr<osg::Node> DrawPolygon(osg::Vec2d pos, osg::Vec2d size, osg::Vec4d color);









