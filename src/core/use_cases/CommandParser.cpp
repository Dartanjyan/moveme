#include "CommandParser.h"

Command parseCommand(std::string command)
{
  Command cmd;
  
  if (command.starts_with("say"))
  {
    cmd.command = CommandToken::SAY;
    cmd.args = command.substr(4);
  }
  else if (command.starts_with("exit"))
  {
    cmd.command = CommandToken::EXIT;
  }

  return cmd;
}