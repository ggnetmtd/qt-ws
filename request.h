#ifndef REQUEST_H
#define REQUEST_H


#include "message.h"

class IWebSocketRequest: public IWebSocketMessage {
public:
    void virtual handleRequest() = 0;

    void handle() override
    {
        handleRequest();
    }

    virtual void send(const std::string&) = 0;
};

#endif // REQUEST_H
