#include "ClientApp.h"
#include "SDLApp.h"
#include <iostream>
#include <memory>

int main() {
  auto sdl_app = std::make_unique<SDLApp>("Moveme!");
  ClientApp app(std::move(sdl_app));

  int code = app.run();
  
  if (code != 0) {
    std::cerr << "Application ended with return code " << code << std::endl;
    return code;
  }

  return 0;
}