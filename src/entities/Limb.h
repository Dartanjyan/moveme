#ifndef LIMB_H
#define LIMB_H

#include <vector>
#include "BodyPart.h"
#include "Constraint.h"

class Limb {
public:
    Limb(std::vector<BodyPart *> &bodyParts, std::vector<Constraint *> &constraints);

    std::vector<BodyPart *> getBodyParts() { return bodyParts; }
    std::vector<Constraint *> getConstraints() { return constraints; }
private:
    std::vector<BodyPart *> bodyParts;
    std::vector<Constraint *> constraints;
};

#endif // LIMB_H