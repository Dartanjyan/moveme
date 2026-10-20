#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include "Snapshot.h"

class IApplication {
public:
    virtual ~IApplication() = default;           // см. ниже, это важно
    virtual int  initialize(unsigned w, unsigned h) = 0;
    virtual void shutdown() = 0;
    // TODO: virtual bool pollInput(InputState& out) = 0; // false = выход
    virtual void render(const WorldSnapshot& s) = 0;
};

#endif // IAPPLICATION_H