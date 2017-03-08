#include "GetFilmsAction.h"
#include "Other/UserAuthorizationManager.h"

#include <QDebug>

void GetFilmsAction::onGet(qttp::HttpData& data){
    const QJsonObject& request = data.getRequest().getJson();
    QJsonObject& response = data.getResponse().getJson();
    if(request.contains("token")){
        bool isUserAuthorized = UserAuthorizationManager::getInstance()
                                .isTokenExists(request.value("token").toString());
        response = this->response(isUserAuthorized);
    }
}


QJsonObject GetFilmsAction::response(int result){

    if(result){
        Film::FilmDBController dbController;
        QVector<Film> films = dbController.getFilms();
        QJsonArray array;
        for(Film film : films){
            array.append(film.serialize());
        };
        QVariantMap responseMap;
        QVariantMap responseObj;

        if(!films.isEmpty()){
            QVariantMap okObject;
            okObject.insert("films", array);
            responseObj.insert("ok", okObject);
        }
        else{
            QVariantMap errorObject;
            errorObject.insert("dsc", "Server error");
            responseObj.insert("error", errorObject);
        }
        responseMap.insert("method", "LinBa.getFilms()");
        responseMap.insert("response", responseObj);

        QJsonObject obj = QJsonObject::fromVariantMap(responseMap);
    //    qDebug()<<obj;
        return obj;
    }
   // qDebug()<<"error";
    return QJsonObject();
}
