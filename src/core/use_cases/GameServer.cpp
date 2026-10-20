#include "GameServer.h"

GameServer::GameServer(ServerOpts &opt)
  : opt(opt)
{

}

void GameServer::run(std::atomic<bool> &stop)
{
  while (!stop.load())
  {

  }
}

void GameServer::pushCommand(std::string command)
{
  commandsQueue.push(command);
}
