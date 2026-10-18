#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <memory>
#include "BodyPart.h"
#include "Limb.h"
#include <cstdint>

class Creature {
public:
    Creature(std::shared_ptr<BodyPart> body, std::vector<std::unique_ptr<Limb>> limbs);
    ~Creature();

    // std::vector<Limb *> getLimbs() const { return limbs; }
    // const BodyPart* getBody() const { return body; }

    static std::unique_ptr<Creature> createBasicCreature();
    uint32_t getId() const { return id; }
private:
    const uint32_t id;
    static uint32_t lastId;
    static uint32_t getNextId() { return lastId++; }
    
    std::vector<std::unique_ptr<Limb>> limbs;
    std::shared_ptr<BodyPart> body;
};

#endif
