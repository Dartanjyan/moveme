#ifndef SERVERCOMMAND_H
#define SERVERCOMMAND_H

#include <string>

enum class CommandToken
{
  SAY,
  EXIT
};

struct Command
{
  CommandToken command;
  std::string args;
};

Command parseCommand(std::string command);

#endif