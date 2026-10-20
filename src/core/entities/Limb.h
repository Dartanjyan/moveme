#ifndef LIMB_H
#define LIMB_H

#include <vector>
#include <memory>
#include "BodyPart.h"
#include "Constraint.h"
#include "Vector2.h"

class Limb {
public:
    Limb(std::vector<std::shared_ptr<BodyPart>> bodyParts, std::vector<std::shared_ptr<Constraint>> constraints);
    
    std::vector<std::weak_ptr<const BodyPart>> getBodyParts() const;
    std::vector<std::weak_ptr<const Constraint>> getConstraints() const;
    
    // FABRIK algorithm
    void reachTowards(const Vector2& target, const int iterations = 10);
    
private:
    std::vector<std::shared_ptr<BodyPart>> bodyParts;
    std::vector<std::shared_ptr<Constraint>> constraints;
    
    void forwardReach(const Vector2& target);
    void backwardReach(const Vector2& base);
};

#endif // LIMB_H
