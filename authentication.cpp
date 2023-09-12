#include "authentication.h"

Authentication::Authentication(QObject *parent) : Exchange(parent)
{
    m_rpc = "/sign-in\n";

    // connect signals & slots
    init();
}

void Authentication::handleRequest()
{

}

void Authentication::handleResponse(const QString& data)
{
    close();
}


