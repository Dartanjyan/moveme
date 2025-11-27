#ifndef LIMB_H
#define LIMB_H

#include <vector>
#include "BodyPart.h"
#include "Constraint.h"
#include "Vector2.h"

class Limb {
public:
    Limb(std::vector<BodyPart *> &bodyParts, std::vector<Constraint *> &constraints);

    std::vector<BodyPart *> getBodyParts() { return bodyParts; }
    std::vector<Constraint *> getConstraints() { return constraints; }
    
    // FABRIK algorithm
    void reachTowards(Vector2 target, int iterations = 10);
    
private:
    std::vector<BodyPart *> bodyParts;
    std::vector<Constraint *> constraints;
    
    void forwardReach(Vector2 target);
    void backwardReach(Vector2 base);
};

#endif // LIMB_H