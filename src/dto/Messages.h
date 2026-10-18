#ifndef MESSAGES_H
#define MESSAGES_H

#include "Vector2.h"
#include "Snapshot.h"
#include <variant>

struct InputMsg
{
  Vector2 target;
  bool active = false;
};

struct SnapshotMsg
{
  WorldSnapshot world;
};

using ClientMessage = std::variant<InputMsg>;
using ServerMessage = std::variant<SnapshotMsg>;

#endif