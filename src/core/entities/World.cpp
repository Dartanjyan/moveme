#include "World.h"

#include <algorithm>

World::World(std::unique_ptr<IPhysics> physicsEngine)
    : physicsEngine(std::move(physicsEngine))
{
}

World::~World()
{
}

void World::tick(float dt)
{
    physicsEngine->step(dt);
}

void World::addCreature(std::unique_ptr<Creature> creature)
{
  creatures.push_back(std::move(creature));
}

void World::removeCreature(uint32_t creatureId)
{
  std::erase_if(creatures, [creatureId](const auto& creature) {
    return creature && creature->getId() == creatureId;
  });
}
