#ifndef IPHYSICS_H
#define IPHYSICS_H

#include "Vector2.h"
#include <cstdint>

using PhysBodyId = uint32_t;

class IPhysics {
public:
    virtual ~IPhysics() = default;
    virtual PhysBodyId addSegment(Vector2 p1, Vector2 p2, float mass) = 0;
    virtual void addJoint(PhysBodyId a, PhysBodyId b, Vector2 anchor,
                          float minAngle, float maxAngle) = 0;
    virtual void setTarget(PhysBodyId tip, Vector2 target) = 0;
    virtual void step(float dt) = 0;
    //virtual SegmentPose getPose(PhysBodyId id) const = 0;  // p1, p2
    virtual void remove(PhysBodyId id) = 0;
};
// server/frameworks/ChipmunkPhysics.cpp реализует его
// на cpSpace/cpBody/cpConstraint

#endif
