#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "network/exchange.h"

class Authentication : public Exchange {
Q_OBJECT

public:
    Authentication(QObject* parent);

    void handleResponse(const QString& data) override;
    void handleRequest() override;
};

#endif // AUTHENTICATION_H
