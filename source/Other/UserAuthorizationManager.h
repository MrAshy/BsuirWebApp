#ifndef AUTORIEDUSERSTORAGE_H
#define AUTORIEDUSERSTORAGE_H

#include <QMap>
#include "Entity/user.h"
#include "Other/tokengenerator.h"
#include <QSharedPointer>

class UserAuthorizationManager
{
public:

    UserAuthorizationManager(const UserAuthorizationManager& other) = delete;
    UserAuthorizationManager& operator=(const UserAuthorizationManager& other) = delete;

    static UserAuthorizationManager& getInstance();
    void addUser(const QString& token, const QSharedPointer<User>& user);
    void removeUser(const QString& token);
    bool isUserAutorized(const QString& userLogin);
    QString getUserToken(const QString& userLogin);
    QSharedPointer<User> getUser(const QString& token);
    bool isTokenExists(const QString& token);
    QString generateToken() { return generator.generateNewToken(); }
    QString getToken() { return generator.getToken(); }

private:
    UserAuthorizationManager() {}
    QMap<QString, QSharedPointer<User> > authorizedTokens;
    TokenGenerator generator;
};

#endif // AUTORIEDUSERSTORAGE_H
