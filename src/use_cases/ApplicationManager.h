#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <memory>
#include <chrono>
#include "GameState.h"
#include "IApplication.h"

class ApplicationManager {
public:
    ApplicationManager(std::unique_ptr<IApplication> app);
    ~ApplicationManager();

    int run();
    int gameTick();
private:
    GameState gameState;
    std::unique_ptr<IApplication> app;
    std::chrono::milliseconds updateInterval;
    unsigned tickCounter;
    
    float width = 800, height = 600;
};

#endif // APPLICATIONMANAGER_H