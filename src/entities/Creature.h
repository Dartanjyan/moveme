#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include "BodyPart.h"
#include "Limb.h"

class Creature {
public:
    Creature(BodyPart *body, std::vector<Limb *> &limbs);
    ~Creature();

    std::vector<Limb *> getLimbs() const { return limbs; }
    BodyPart* getBody() { return body; }
private:
    std::vector<Limb *> limbs;
    BodyPart *body;
};

#endif
