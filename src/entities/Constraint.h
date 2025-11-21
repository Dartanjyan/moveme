#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <iostream>
#include "BodyPart.h"
#include "Vector2.h"

class Constraint {
private:
    BodyPart* partA;
    BodyPart* partB;
    Vector2 anchorA;
    float rest;
    float stiffness;
    float damping;
    float minAngle;
    float maxAngle;

public:
    Constraint(BodyPart* partA, BodyPart* partB,
        Vector2 anchorA = Vector2{},
        float rest = 0.0f, float stiffness = 8e5, 
        float damping = 4e4);
    ~Constraint();

    BodyPart* getPartA() const { return partA; }
    BodyPart* getPartB() const { return partB; }
    Vector2 getAnchorA() const { return anchorA; }
    float getStiffness() const { return stiffness; }
    float getDamping() const { return damping; }
    float getMinAngle() const { return minAngle; }
    float getMaxAngle() const { return maxAngle; }

    float clampAngle(float angle) const;

    void setBodyA(BodyPart* part) { partA = part; }
    void setBodyB(BodyPart* part) { partB = part; }
    void setAnchorA(Vector2 anchor) { anchorA = anchor; }
    void setRest(float value) { rest = value; }
    void setStiffness(float value) { stiffness = value; }
    void setDamping(float value) { damping = value; }

};

#endif
