#include "GameServer.h"
#include <atomic>
#include <thread>
#include <iostream>
#include <cstring>

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

int main(int argc, char** argv)
{
  auto opt = parseArgs(argc, argv);
  GameServer server(opt);
  std::atomic<bool> stop{false};
  if (opt.console)
    std::thread([&]{
      std::string line;
      while (std::getline(std::cin, line)) server.pushCommand(line);
      // EOF (stdin закрыт) — это НЕ повод останавливать сервер
    }).detach();
  server.run(stop);
  std::cout << "Hello Server!" << std::endl;

  return 0;
}