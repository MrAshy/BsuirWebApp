#ifndef SERVERACTION_H
#define SERVERACTION_H

#include <QJsonObject>

class ServerAction
{
public:
    ServerAction() {}
    virtual ~ServerAction() = 0 {}
protected:
    virtual QJsonObject response(int result) {return QJsonObject();}
    virtual QJsonObject response(int result, const QString& eventName) { return QJsonObject();}
};

#endif // SERVERACTION_H
