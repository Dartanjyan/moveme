#include "World.h"

#include <algorithm>

World::World()
{
}

World::~World()
{
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
