#include <iostream>
#include <memory>
#include "ApplicationManager.h"
#include "SDLApp.h"

int main() {
    auto app = std::make_unique<SDLApp>("Move Me!");
    ApplicationManager am(std::move(app));

    int result = am.run();

    return result;
}