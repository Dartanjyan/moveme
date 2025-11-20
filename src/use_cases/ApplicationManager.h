#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <memory>
#include <chrono>
#include "IApplication.h"

class ApplicationManager {
public:
    ApplicationManager(std::unique_ptr<IApplication> app);
    ~ApplicationManager();

    int run();
private:
    std::unique_ptr<IApplication> app;
    std::chrono::milliseconds updateInterval;
};

#endif // APPLICATIONMANAGER_H