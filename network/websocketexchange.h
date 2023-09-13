#ifndef WEBSOCKETEXCHANGE_H
#define WEBSOCKETEXCHANGE_H

#include <QWebSocket>

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include <QObject>
#include <functional>

class JsonDeserializedObject {
    QJsonObject m_serializedObject;
    bool m_deserialized;

public:
    virtual void setSerialized(const QString& json) {
        m_serializedObject = QJsonDocument::fromJson(json.toUtf8()).object();
    }
    virtual void deserialize() = 0;

protected:
    JsonDeserializedObject(const QString&);
};


class WebSocketExchange : public QObject
{
Q_OBJECT

public:
    WebSocketExchange(QObject* parent = nullptr);

    virtual WebSocketExchange* setRequest(QJsonObject&);
    virtual WebSocketExchange* setRPC(const QString&);
    virtual WebSocketExchange* setJDO(JsonDeserializedObject*);

    virtual void subscribe(QObject*, std::function<void(JsonDeserializedObject*)> handler);

signals:
    void gotResponse(JsonDeserializedObject*);


protected:
    virtual void init();

    virtual void send(const QString&);
    virtual void handleRequest();
    virtual void handleResponse(const QString&);

    QString m_rpc;
    QWebSocket m_socket;
    JsonDeserializedObject* m_jdo;

    bool m_isRequestBinded = false;
    QJsonObject m_request;
};

#endif // WEBSOCKETEXCHANGE_H
