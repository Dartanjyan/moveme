#ifndef ICONNECTION_H
#define ICONNECTION_H

#include "Messages.h"
#include <optional>

class IConnection {
public:
    virtual ~IConnection() = default;
    virtual void send(const ClientMessage&) = 0;
    virtual std::optional<ServerMessage> poll() = 0;  // неблокирующий
};

#endif