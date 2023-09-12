#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <QtWebSockets/QtWebSockets>


class IWebSocketMessage
{
public:
    virtual void handle() = 0;
    virtual void handle(const QString& data) = 0;
};

#endif // NETWORK_MESSAGE_H
