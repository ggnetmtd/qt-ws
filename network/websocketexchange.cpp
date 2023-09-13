#include "websocketexchange.h"

WebSocketExchange::WebSocketExchange(QObject* parent) : QObject(parent)
{
    init();
}


void WebSocketExchange::init()
{
    connect(&m_socket, &QWebSocket::connected, this, &handleRequest);
    connect(&m_socket, &QWebSocket::textMessageReceived, this, &handleResponse);
}

void WebSocketExchange::handleRequest()
{
    if(!m_isRequestBinded)
        throw std::invalid_argument("No binded request.");

    QString header = m_rpc + '\n';
    QString request = QJsonDocument(m_request).toJson();

    request = header + request;

    this->send(request);
}

void WebSocketExchange::handleResponse(const QString &response)
{
    m_jdo->setSerialized(response);

    m_jdo->deserialize();

    emit gotResponse(m_jdo);
}

WebSocketExchange* WebSocketExchange::setRequest(QJsonObject &request)
{
    m_request = request;
    m_isRequestBinded = true;

    return this;
}

WebSocketExchange* WebSocketExchange::setRPC(const QString &rpc)
{
    m_rpc = rpc;

    return this;
}

WebSocketExchange* WebSocketExchange::setJDO(JsonDeserializedObject* jdo)
{
    m_jdo = jdo;

    return this;
}

void WebSocketExchange::subscribe(QObject *subscriber, std::function<void(JsonDeserializedObject*)> handler)
{
    connect(this, &WebSocketExchange::gotResponse, subscriber, handler);
}

void WebSocketExchange::send(const QString &request)
{
    m_socket.sendTextMessage(request);
}
