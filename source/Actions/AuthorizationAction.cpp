#include <QSqlDatabase>
#include <QSqlQuery>

#include "Actions/AuthorizationAction.h"

#include "Other/UserAuthorizationManager.h"

void AutorizationAction::onGet(qttp::HttpData& data){;
    const QJsonObject& jsonRequest = data.getRequest().getJson();
    QJsonObject& jsonResponse = data.getResponse().getJson();
    qDebug()<<jsonRequest;
    if(jsonRequest.value("event").toString() == "logIn"){
        if(jsonRequest.contains("login") && jsonRequest.contains("password")){
            int result = -1;
            result = logIn(jsonRequest["login"].toString(), jsonRequest["password"].toString());
            jsonResponse = response(result, "logIn");
        }
    }
    if(jsonRequest.value("event").toString() == "logOut"){
        int result = logOut(jsonRequest.value("token").toString());
        jsonResponse = response(result, "logOut");
    }
}

int AutorizationAction::logIn(const QString& login, const QString& password){
    int result = 0;
     User::UserDBController dbController;
    if(!UserAuthorizationManager::getInstance().isUserAutorized(login)){
        result = dbController.hasUser(login, password);
        if(result == 1){
            QString token = UserAuthorizationManager::getInstance().generateToken();
            QSharedPointer<User> userPtr(dbController.getUser(login));
            if(!userPtr.isNull()){
                UserAuthorizationManager::getInstance().addUser(token, userPtr);
            }
        }
    }
    else{
        QString token = UserAuthorizationManager::getInstance().getUserToken(login);
        if(!token.isEmpty()){
            QString newToken = UserAuthorizationManager::getInstance().generateToken();
            UserAuthorizationManager::getInstance().addUser(newToken, UserAuthorizationManager::getInstance().getUser(token));
            UserAuthorizationManager::getInstance().removeUser(token);
            result = 1;
        }
    }
    return result;
}

bool AutorizationAction::logOut(const QString& token){
    if(!token.isNull()){
        if(!token.isEmpty()){
            UserAuthorizationManager::getInstance().removeUser(token);
            return true;
        }
    }
    return false;
}

QJsonObject AutorizationAction::logInResponse(int logInResult){
    QJsonObject jsonResponse;
    switch(logInResult){
        case 1: {
            QVariantMap responseMap;
            QVariantMap responseObj;
            QVariantMap okObj;
            okObj.insert("token", UserAuthorizationManager::getInstance().getToken());
            responseObj.insert("ok", okObj);
            responseMap.insert("method", "LinBa.logIn()");
            responseMap.insert("response", responseObj);
            jsonResponse = QJsonObject::fromVariantMap(responseMap);
            break;
        }
        case 0: {
            QVariantMap responseMap;
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Invalid login or password");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.logIn()");
            responseMap.insert("response", responseObj);
            jsonResponse = QJsonObject::fromVariantMap(responseMap);
            break;
        }
        case -1: {
            QVariantMap responseMap;
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Server problem");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.logIn()");
            responseMap.insert("response", responseObj);
            jsonResponse = QJsonObject::fromVariantMap(responseMap);
            break;
        }
    }
    return jsonResponse;
}

QJsonObject AutorizationAction::logOutResponse(int logOutResult){
    QJsonObject jsonResponse;
    if(logOutResult){
        QVariantMap responseMap;
        QVariantMap responseObj;
        QVariantMap okObj;
        okObj.insert("dsc", "Logout success");
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LinBa.logOut()");
        responseMap.insert("response", responseObj);
        jsonResponse = QJsonObject::fromVariantMap(responseMap);
    }
    else{
        QVariantMap responseMap;
        QVariantMap responseObj;
        QVariantMap errorObj;
        errorObj.insert("dsc", "Logout failed");
        responseObj.insert("error", errorObj);
        responseMap.insert("method", "LinBa.logOut()");
        responseMap.insert("response", responseObj);
        jsonResponse = QJsonObject::fromVariantMap(responseMap);
    }
    return jsonResponse;
}

QJsonObject AutorizationAction::response(int result, const QString &eventName){
    if(eventName == "logIn"){
        return logInResponse(result);
    }
    if(eventName == "logOut"){
        return logOutResponse(result);
    }
    return QJsonObject();
}
