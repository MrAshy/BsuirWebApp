#ifndef AUTHORIZATIONCONTROLLER_H
#define AUTHORIZATIONCONTROLLER_H

#include "action.h"
#include "Entity/user.h"
#include <QMap>

class AutorizationAction : public qttp::Action
{
public:
    AutorizationAction() : Action() {}
    virtual ~AutorizationAction() {}
    const char* getName() const { return "authorization_action"; }
    void onGet(qttp::HttpData& data);

protected:
    int logIn(const QString& login, const QString& password);
    bool logOut(const QString& token);

    QJsonObject response(int result, const QString& eventName);

    QJsonObject logInResponse(int logInResult);
    QJsonObject logOutResponse(int logOutResult);
};

#endif // AUTHORIZATIONCONTROLLER_H
