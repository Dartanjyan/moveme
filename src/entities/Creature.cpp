#include "Creature.h"

Creature::Creature(std::unique_ptr<BodyPart> body, std::vector<std::unique_ptr<Limb>> &limbs)
    : body(std::move(body)), limbs(std::move(limbs))
{
}

Creature::~Creature()
{
}

std::unique_ptr<Creature> createBasicCreature()
{
    float scale = 1.0f;
    Vector2 bias(200, 200);

    auto body = std::make_unique<BodyPart>(nullptr, Vector2(0, 0)*scale+bias, Vector2(200, 0)*scale+bias);

    auto b1 = std::make_unique<BodyPart>(nullptr, Vector2(100, 0)*scale+bias, Vector2(100, 200)*scale+bias);
    auto b2 = std::make_unique<BodyPart>(nullptr, Vector2(100, 200)*scale+bias, Vector2(100, 250)*scale+bias);
    auto b3 = std::make_unique<BodyPart>(nullptr, Vector2(100, 250)*scale+bias, Vector2(100, 275)*scale+bias);
    auto c1 = std::make_unique<Constraint>(b1.get(), b2.get());
    auto c2 = std::make_unique<Constraint>(b2.get(), b3.get());
    std::vector<std::unique_ptr<BodyPart>> bps {
        std::move(b1), 
        std::move(b2), 
        std::move(b3)
    };
    std::vector<std::unique_ptr<Constraint>> cs {
        std::move(c1), 
        std::move(c2)
    };
    auto limb = std::make_unique<Limb>(
        bps,
        cs
    );

    std::vector<std::unique_ptr<Limb>> limbs {std::move(limb)};

    auto creature = std::make_unique<Creature>(std::move(body), limbs);
    return std::move(creature);
}
