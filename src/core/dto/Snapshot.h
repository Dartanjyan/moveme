#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <vector>
#include <cstdint>
#include "Vector2.h"

struct LimbSnapshot
{
  std::vector<Vector2> joints;
};

struct CreatureSnapshot
{
  uint32_t id;
  std::vector<LimbSnapshot>
  limbs;
};

struct WorldSnapshot
{
  uint32_t tick = 0;
  std::vector<CreatureSnapshot> creatures;
};

#endif