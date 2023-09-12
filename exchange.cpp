#include "exchange.h"


Exchange::Exchange(QObject* parent) : QObject(parent)
{
}


void Exchange::send(const QString &data)
{
    m_socket.sendTextMessage(data);
}
