#ifndef LIMB_H
#define LIMB_H

#include <vector>
#include <memory>
#include "BodyPart.h"
#include "Constraint.h"
#include "Vector2.h"

class Limb {
public:
    Limb(std::vector<std::unique_ptr<BodyPart>> &bodyParts, std::vector<std::unique_ptr<Constraint>> &constraints);

    // std::vector<BodyPart *> getBodyParts() const { return bodyParts; }
    // std::vector<Constraint *> getConstraints() const { return constraints; }
    
    // FABRIK algorithm
    void reachTowards(const Vector2& target, const int iterations = 10);
    
private:
    std::vector<std::unique_ptr<BodyPart>> bodyParts;
    std::vector<std::unique_ptr<Constraint>> constraints;
    
    void forwardReach(const Vector2& target);
    void backwardReach(const Vector2& base);
};

#endif // LIMB_H
