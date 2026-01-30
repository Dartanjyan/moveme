#include "Creature.h"

Creature::Creature(std::unique_ptr<BodyPart> body, std::vector<Limb *> &limbs)
    : body(std::move(body)), limbs(limbs)
{
}

Creature::~Creature()
{
    for (Limb *l : limbs) {
        delete l;
    }
}

std::unique_ptr<Creature> createBasicCreature()
{
    float scale = 1.0f;
    Vector2 bias(200, 200);

    auto body = std::make_unique<BodyPart>(nullptr, Vector2(0, 0)*scale+bias, Vector2(200, 0)*scale+bias);

    BodyPart *b1 = new BodyPart(nullptr, Vector2(100, 0)*scale+bias, Vector2(100, 200)*scale+bias);
    BodyPart *b2 = new BodyPart(nullptr, Vector2(100, 200)*scale+bias, Vector2(100, 250)*scale+bias);
    BodyPart *b3 = new BodyPart(nullptr, Vector2(100, 250)*scale+bias, Vector2(100, 275)*scale+bias);
    Constraint *c1 = new Constraint(b1, b2);
    Constraint *c2 = new Constraint(b2, b3);
    std::vector<BodyPart *> bps {b1, b2, b3};
    std::vector<Constraint *> cs {c1, c2};
    Limb *limb = new Limb(
        bps,
        cs
    );

    std::vector<Limb *> limbs {limb};

    auto creature = std::make_unique<Creature>(std::move(body), limbs);
    return std::move(creature);
}
