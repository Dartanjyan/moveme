#ifndef BODYPART_H
#define BODYPART_H

#include <vector>
#include "Vector2.h"

class BodyPart {
public:
    BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2);
    ~BodyPart();

    std::vector<BodyPart *> getChildren() { return children; }
    BodyPart* getParent() { return parent; }
    void addChild(BodyPart *child) { children.push_back(child); }
    Vector2 getPoint1() const { return p1; }
    Vector2 getPoint2() const { return p2; }
    
    void setPoint1(Vector2 point) { p1 = point; }
    void setPoint2(Vector2 point) { p2 = point; }
    
private:
    Vector2 p1, p2;

    std::vector<BodyPart *> children;
    BodyPart *parent;
};

#endif