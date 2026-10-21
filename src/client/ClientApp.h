#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <memory>
#include <chrono>
#include "IApplication.h"

class ClientApp {
public:
    ClientApp(std::unique_ptr<IApplication> app);
    ~ClientApp();
    
    // Main application cycle
    int run();
    int gameTick();
private:
    std::unique_ptr<IApplication> app;
    std::chrono::milliseconds updateInterval;
    unsigned tickCounter;

    bool initialized = false;
    float width = 800, height = 600;
};

#endif // CLIENTAPP_H