#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <string>
#include <queue>
#include <atomic>

struct ServerOpts
{
  bool console = true;
};

class GameServer
{
public:
  GameServer(ServerOpts &opt);
  
  void run(std::atomic<bool> &stop);
  void pushCommand(std::string command);
private:
  ServerOpts opt;
  std::queue<std::string> commandsQueue;
};

#endif