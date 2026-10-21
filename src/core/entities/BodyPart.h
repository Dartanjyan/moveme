#ifndef BODYPART_H
#define BODYPART_H

#include <vector>
#include "IPhysics.h"
#include "Vector2.h"

class BodyPart {
public:
    BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2, float width1 = 0, float width2 = 0);
    ~BodyPart();

    std::vector<BodyPart *> getChildren() const { return children; }
    BodyPart *const getParent() const { return parent; }
    void addChild(BodyPart *child) { children.push_back(child); }
    Vector2 getPoint1() const { return p1; }
    Vector2 getPoint2() const { return p2; }
    
    void setPoint1(const Vector2& point) { p1 = point; }
    void setPoint2(const Vector2& point) { p2 = point; }
    // void setWidth1(const float width) { width1 = width; }
    // void setWidth2(const float width) { width2 = width; }
    
private:
    // p1 is starting point
    Vector2 p1, p2;
    PhysBodyId bodyId;

    std::vector<BodyPart *> children;
    BodyPart *parent;
};

#endif
