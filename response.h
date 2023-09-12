#ifndef RESPONSE_H
#define RESPONSE_H

#include "message.h"

class IWebSocketResponse: public IWebSocketMessage  {
public:
    void virtual handleResponse(const QString& data) = 0;

    void handle(const QString& data) override
    {
        handleResponse(data);
    }
};

#endif // RESPONSE_H
