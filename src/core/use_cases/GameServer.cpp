#include <iostream>
#include "GameServer.h"
#include "CommandParser.h"

GameServer::GameServer(ServerOpts &opt)
  : opt(opt)
{

}

void GameServer::run(std::atomic<bool> &stop)
{
  running.store(true);

  while (!stop.load() && running.load())
  {
    processConsoleInput();
    executeCommands();
  }

  std::cout << "Server stopped\n";
  running.store(false);
}

void GameServer::pushCommand(Command command)
{
  commandsQueue.push(command);
}

void GameServer::executeCommands()
{
  while (!commandsQueue.empty())
  {
    Command cmd = commandsQueue.front();
    commandsQueue.pop();

    switch (cmd.command)
    {
      case CommandToken::EXIT:
        running.store(false);
        break;
      case CommandToken::SAY:
        std::cout << cmd.args << "\n";
        break;
    }
  }
}

void GameServer::processConsoleInput()
{
  if (!opt.console) 
  {
    std::cout << "Console is disabled\n";
    return;
  }

  std::string line;
  while (std::getline(std::cin, line)) 
  {
    pushCommand(parseCommand(line));
  }
}
