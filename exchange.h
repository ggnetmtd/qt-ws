#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "request.h"
#include "response.h"

class Exchange : public QObject,
                 public IWebSocketRequest, public IWebSocketResponse {
Q_OBJECT

public:
    Exchange(QObject* parent = Q_NULLPTR);
    virtual ~Exchange() {}

    virtual void send(const QString& data);

    virtual void open(QUrl url)
    {
        m_socket.open(url);
    }

    virtual void close()
    {
        m_socket.close();
    }

public slots:
    virtual void handleRequest() override = 0;
    virtual void handleResponse(const QString& data) override = 0;
protected:
    QString m_rpc;
    QWebSocket m_socket;

    virtual void init()
    {
        connect(&m_socket, &QWebSocket::connected, this, &handleRequest);
        connect(&m_socket, &QWebSocket::textMessageReceived, this, &handleResponse);
    }
};

#endif // EXCHANGE_H
