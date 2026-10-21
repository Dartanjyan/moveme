#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "Creature.h"
#include "IPhysics.h"

class World {
public:
  World(std::unique_ptr<IPhysics> physicsEngine);
  ~World();

  void tick(float dt);
  void addCreature(std::unique_ptr<Creature> creature);
  void removeCreature(uint32_t creatureId);
private:
  std::unique_ptr<IPhysics> physicsEngine;
  std::vector<std::unique_ptr<Creature>> creatures;
};

#endif
