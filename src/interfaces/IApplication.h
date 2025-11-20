#ifndef IAPPLICATION_H
#define IAPPLICATION_H

class IApplication {
public:
    ~IApplication() = default;

    virtual int initialize() = 0;
    virtual void shutdown() = 0;
    virtual int update() = 0;
};

#endif // IAPPLICATION_H