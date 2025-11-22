#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <iostream>
#include "BodyPart.h"
#include "Vector2.h"

class Constraint {
private:
    BodyPart* partA;
    BodyPart* partB;
    Vector2 anchor;
    float power;
    float minAngle;
    float maxAngle;

public:
    Constraint(BodyPart* partA, BodyPart* partB, Vector2 anchor, float power = 1);
    Constraint(BodyPart* partA, BodyPart* partB, float power = 1);

    BodyPart* getPartA() const { return partA; }
    BodyPart* getPartB() const { return partB; }
    Vector2 getAnchor() const { return anchor; }
    float getPower() const { return power; }
    float getMinAngle() const { return minAngle; }
    float getMaxAngle() const { return maxAngle; }

    float clampAngle(float angle) const;

    void setBodyA(BodyPart* part) { partA = part; }
    void setBodyB(BodyPart* part) { partB = part; }
    void setAnchor(Vector2 anchor) { anchor = anchor; }
    void setPower(float value) { power = value; }

};

#endif
