#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include "GameState.h"

class IApplication {
public:
    ~IApplication() = default;

    virtual int initialize(unsigned width, unsigned height, const GameState *gameState) = 0;
    virtual void shutdown() = 0;
    virtual int update() = 0;
};

#endif // IAPPLICATION_H