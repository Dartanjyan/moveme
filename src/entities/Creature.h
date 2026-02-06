#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <memory>
#include "BodyPart.h"
#include "Limb.h"

class Creature {
public:
    Creature(std::shared_ptr<BodyPart> body, std::vector<std::unique_ptr<Limb>> limbs);
    ~Creature();

    // std::vector<Limb *> getLimbs() const { return limbs; }
    // const BodyPart* getBody() const { return body; }

    static std::unique_ptr<Creature> createBasicCreature();
private:
    std::vector<std::unique_ptr<Limb>> limbs;
    std::shared_ptr<BodyPart> body;
};

#endif
