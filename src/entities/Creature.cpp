#include "Creature.h"

Creature::Creature(std::shared_ptr<BodyPart> body, std::vector<std::unique_ptr<Limb>> limbs)
    : body(std::move(body)), limbs(std::move(limbs))
{
}

Creature::~Creature()
{
}

std::unique_ptr<Creature> createBasicCreature()
{
    float scale = 1.0f;
    const Vector2 bias(200, 200);

    auto body = std::make_shared<BodyPart>(nullptr, Vector2(0, 0)*scale+bias, Vector2(200, 0)*scale+bias);

    std::vector<std::shared_ptr<BodyPart>> bps {
        std::make_shared<BodyPart>(nullptr, Vector2(100, 0)*scale+bias, Vector2(100, 200)*scale+bias), 
        std::make_shared<BodyPart>(nullptr, Vector2(100, 200)*scale+bias, Vector2(100, 250)*scale+bias), 
        std::make_shared<BodyPart>(nullptr, Vector2(100, 250)*scale+bias, Vector2(100, 275)*scale+bias)
    };
    std::vector<std::unique_ptr<Constraint>> cs;
    cs.push_back(std::make_unique<Constraint>(bps[0], bps[1]));
    cs.push_back(std::make_unique<Constraint>(bps[1], bps[2]));

    std::vector<std::unique_ptr<Limb>> limbs;
    limbs.push_back(std::make_unique<Limb>(bps, std::move(cs)));

    auto creature = std::make_unique<Creature>(body, std::move(limbs));
    return creature;
}
