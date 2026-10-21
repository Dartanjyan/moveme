#include "GameServer.h"
#include <atomic>
#include <thread>
#include <iostream>

int main(int argc, char** argv) {
  // auto opt = parseArgs(argc, argv);
  // GameServer server(opt);
  // std::atomic<bool> stop{false};
  // if (opt.console)
  //   std::thread([&]{
  //     std::string line;
  //     while (std::getline(std::cin, line)) server.pushCommand(line);
  //     // EOF (stdin закрыт) — это НЕ повод останавливать сервер
  //   }).detach();
  // server.run(stop);
  std::cout << "Hello Server!" << std::endl;
}