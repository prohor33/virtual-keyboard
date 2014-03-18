#include "button.h"
#include "osg_stuff.h"

void Button::Draw(osg::ref_ptr<osg::Group> root) {
  root->addChild(DrawTexture(img_name[0], pos, size));
}