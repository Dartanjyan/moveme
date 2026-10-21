#include "GameServer.h"
#include "CommandParser.h"
#include <atomic>
#include <cstring>

ServerOpts parseArgs(int argc, char** argv);

int main(int argc, char** argv)
{
  auto opt = parseArgs(argc, argv);
  GameServer server(opt);

  std::atomic<bool> stop{false};
  server.run(stop);

  return 0;
}

ServerOpts parseArgs(int argc, char** argv)
{
  ServerOpts options;
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--console")) {
      options.console = true;
    }
    else if (strcmp(argv[i], "--no-console")) {
      options.console = false;
    }
  }
  return options;
}
