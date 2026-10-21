#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <string>
#include <queue>
#include <atomic>

#include "CommandParser.h"

struct ServerOpts
{
  bool console = false;
};

class GameServer
{
public:
  GameServer(ServerOpts &opt);
  
  void run(std::atomic<bool> &stop);
  void pushCommand(Command command);
private:
  std::atomic_bool running;
  ServerOpts opt;
  std::queue<Command>commandsQueue;

  void executeCommands();
  void processConsoleInput();
};

#endif