#ifndef BODYPART_H
#define BODYPART_H

#include <vector>
#include "Vector2.h"

class BodyPart {
public:
    BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2, float width1 = 0, float width2 = 0);
    ~BodyPart();

    std::vector<BodyPart *> getChildren() { return children; }
    BodyPart* getParent() { return parent; }
    void addChild(BodyPart *child) { children.push_back(child); }
    Vector2 getPoint1() const { return p1; }
    Vector2 getPoint2() const { return p2; }
    float getWidth1() const { return width1; }
    float getWidth2() const { return width2; }
    
    void setPoint1(Vector2 point) { p1 = point; }
    void setPoint2(Vector2 point) { p2 = point; }
    void setWidth1(float width) { width1 = width; }
    void setWidth2(float width) { width2 = width; }
    
private:
    // p1 is starting point
    Vector2 p1, p2;

    // width1 is visible width of BodyPart at the p1, the same with p2
    float width1, width2;

    std::vector<BodyPart *> children;
    BodyPart *parent;
};

#endif