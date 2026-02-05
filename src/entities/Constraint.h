#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <iostream>
#include "BodyPart.h"
#include "Vector2.h"

class Constraint {
private:
    // TODO: partA and partB should be shared_ptr
    const BodyPart* partA;
    const BodyPart* partB;

    const Vector2 anchor;
    float power;
    float minAngle;
    float maxAngle;

public:
    Constraint(const BodyPart* partA, const BodyPart* partB, const Vector2& anchor, float power = 1);
    Constraint(const BodyPart* partA, const BodyPart* partB, float power = 1);

    const BodyPart* getPartA() const { return partA; }
    const BodyPart* getPartB() const { return partB; }
    const Vector2 getAnchor() const { return anchor; }
    float getPower() const { return power; }
    float getMinAngle() const { return minAngle; }
    float getMaxAngle() const { return maxAngle; }

    float clampAngle(float angle) const;

    // void setBodyA(BodyPart* part) { partA = part; }
    // void setBodyB(BodyPart* part) { partB = part; }
    // void setAnchor(Vector2 anchor) { anchor = anchor; }
    void setPower(const float value) { power = value; }

};

#endif
