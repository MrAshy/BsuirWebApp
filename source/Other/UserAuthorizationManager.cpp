#include "Other/UserAuthorizationManager.h"

#include <QDebug>

UserAuthorizationManager& UserAuthorizationManager::getInstance(){
    static UserAuthorizationManager instance;
    return instance;
}

void UserAuthorizationManager::addUser(const QString& token, const QSharedPointer<User>& user){
    authorizedTokens.insert(token, user);
}

bool UserAuthorizationManager::isUserAutorized(const QString& userLogin){
    for(auto it = authorizedTokens.begin(); it!=authorizedTokens.end(); ++it){
        if(it.value().data()->getLogin() == userLogin){
            return true;
        }
    }
    return false;
}

QString UserAuthorizationManager::getUserToken(const QString& userLogin){
    for(auto it = authorizedTokens.begin(); it!=authorizedTokens.end(); ++it){
        if(it.value().data()->getLogin() == userLogin){
            return it.key();
        }
    }
    return "";
}

void UserAuthorizationManager::removeUser(const QString& token){
    authorizedTokens.remove(token);
}

QSharedPointer<User> UserAuthorizationManager::getUser(const QString &token){
    return authorizedTokens.value(token);
}

bool UserAuthorizationManager::isTokenExists(const QString &token){
    qDebug()<<authorizedTokens.keys();
    return authorizedTokens.contains(token);
}
