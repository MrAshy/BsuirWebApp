#include "Actions/RegistrationAction.h"

#include "Entity/user.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QUrlQuery>


void RegistrationAction::onPost(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    int result = -2;
    if(request.contains("login") && request.contains("password")){
        QString login = request.value("login").toString();
        QString pass = request.value("password").toString();
        if(!login.isEmpty() && !pass.isEmpty()){
            result = registerUser(login, pass);
        }
    }
    QJsonObject& response = data.getResponse().getJson();
    response = this->response(result);
}


int RegistrationAction::registerUser(const QString& login, const QString& password){
    User::UserDBController dbController;
    int result = dbController.hasUser(login);
    if(result == 0){
        User user(login, password);
        result = dbController.insert(user);
    }
    else{
        if(result == 1){
            return 0;
        }
    }
    return result;
}

QJsonObject RegistrationAction::response(int result){
    QVariantMap responseMap;
    switch(result){
        case -2:{
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Invalid parameters");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.registerUser()");
            responseMap.insert("response", responseObj);
            break;
        }
        case -1: {
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Server error");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.registerUser()");
            responseMap.insert("response", responseObj);
            break;
        }
        case 0: {
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Such user exists");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.registerUser()");
            responseMap.insert("response", responseObj);
            break;
        }
        case 1:{
            QVariantMap responseObj;
            QVariantMap okObj;
            okObj.insert("dsc", "User successfully registered");
            responseObj.insert("ok", okObj);
            responseMap.insert("method", "LinBa.registerUser()");
            responseMap.insert("response", responseObj);
            break;
        }
    }
    return QJsonObject::fromVariantMap(responseMap);
}
