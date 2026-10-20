#ifndef CONSTRAINT_H
#define CONSTRAINT_H
#include <iostream>
#include <memory>
#include "BodyPart.h"
#include "Vector2.h"

class Constraint {
private:
    std::shared_ptr<BodyPart> partA;
    std::shared_ptr<BodyPart> partB;

    const Vector2 anchor;
    float power;
    float minAngle;
    float maxAngle;

public:
    Constraint(const std::shared_ptr<BodyPart> partA, const std::shared_ptr<BodyPart> partB, const Vector2& anchor, float power = 1);
    Constraint(const std::shared_ptr<BodyPart> partA, const std::shared_ptr<BodyPart> partB, float power = 1);

    const std::shared_ptr<BodyPart> getPartA() const { return partA; }
    const std::shared_ptr<BodyPart> getPartB() const { return partB; }
    const Vector2& getAnchor() const { return anchor; }
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
