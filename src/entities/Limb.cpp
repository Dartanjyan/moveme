#include "Limb.h"

Limb::Limb(std::vector<BodyPart *> &bodyParts, std::vector<Constraint *> &constraints)
        : bodyParts(bodyParts), constraints(constraints)
{
}