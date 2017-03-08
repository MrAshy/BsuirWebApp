#include "getactorsaction.h"
#include "Other/UserAuthorizationManager.h"
#include <QVariant>

GetActorsAction::GetActorsAction() {}


void GetActorsAction::onGet(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    if(request.contains("token")){
        if(UserAuthorizationManager::getInstance().isTokenExists(request.value("token").toString())){
            QJsonObject& responseObj = data.getResponse().getJson();
            responseObj = executeRequest(request);
        }
    }
}

QVector<Actor> GetActorsAction::getActors(){
    Actor::ActorDBController db;
    QVector<Actor> actors = db.getActors();
    return actors;
}

QJsonObject GetActorsAction::response(const QVector<Actor>&& actors){
    QVariantMap responseMap;
    if(!actors.isEmpty()){
        QVariantMap responseObj;
        QVariantMap okObj;
        QJsonArray array;
        for(Actor actor : actors){
            array.append(actor.serialize());
        }
        okObj.insert("actors", array);
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LinBa.getActors()");
        responseMap.insert("response", responseObj);
    }
    else{
        QVariantMap responseObj;
        QVariantMap errorObj;
        errorObj.insert("dsc", "Server error");
        responseObj.insert("error", errorObj);
        responseMap.insert("method", "LinBa.getActors()");
        responseMap.insert("response", responseObj);
    }
    return QJsonObject::fromVariantMap(responseMap);
}


QVector<Actor> GetActorsAction::getActorsByFilm(int filmId){
    QVector<Actor> actors;
    Actor::ActorDBController db;
    actors = db.getActorByFilm(filmId);
    return actors;
}


QJsonObject GetActorsAction::executeRequest(const QJsonObject& request){
    QString event = request.value("event").toString();
    if(event == "all"){
        return response(getActors());
    }
    else if(event == "film"){
        int id = request.value("id").toString().toInt();
        return response(getActorsByFilm(id));
    }
    return QJsonObject();
}
