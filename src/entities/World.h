#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "Creature.h"

class World {
public:
  World();
  ~World();

  void addCreature(std::unique_ptr<Creature> creature);
  void removeCreature(uint32_t creatureId);
private:
  std::vector<std::unique_ptr<Creature>> creatures;
};

#endif