#include "favoritesaction.h"
#include "Entity/user.h"
#include "Entity/film.h"
#include "Other/UserAuthorizationManager.h"
#include "DBControllers/managerdb.h"

void FavoritesAction::onGet(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    qDebug()<<request;
    if(UserAuthorizationManager::getInstance().isTokenExists(request.value("token").toString())){
        QJsonObject& response = data.getResponse().getJson();
        response = getFavoritesFilmsResponse(getFavoriteFilms(request.value("token").toString()));
        qDebug()<<response;
    }
}

void FavoritesAction::onPost(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    qDebug()<<request;
    if(request.value("event").toString() == "add"){
        if(request.contains("token") && request.contains("filmId")){
            int result = addToFavorites(request.value("token").toString(),
                                            request.value("filmId").toInt());
            QJsonObject& response = data.getResponse().getJson();
            response = addToFavoritesResponse(result);
        }
    }
    else if(request.value("event").toString() == "delete"){
        if(request.contains("token") && request.contains("filmId")){
            int result = deleteFromFavorites(request.value("token").toString(),
                                            request.value("filmId").toInt());
                QJsonObject& response = data.getResponse().getJson();
                response = deleteFromFavoritesResponse(result);
        }
    }

}

int FavoritesAction::addToFavorites(const QString& token, int filmId){

    if(UserAuthorizationManager::getInstance().isTokenExists(token)){
        qDebug()<<"token exists";
        Film::FilmDBController dbCont;
        if(dbCont.isFilmExists(filmId)){
            qDebug()<<"film exists";
            auto user = UserAuthorizationManager::getInstance().getUser(token);
            if(!ManagerDB::isFilmInFavorites(*(user.data()), filmId)){
                ManagerDB::addFilmsToFavorites(*(user.data()), filmId);
                return 1;
            }
            return -2;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}

QJsonObject FavoritesAction::addToFavoritesResponse(int result){
    QVariantMap responseMap;
    switch(result){
        case -2: {
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "The film is already in favorites");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.addToFavorites()");
            responseMap.insert("response", responseObj);
            break;
        }
        case -1: {
           return QJsonObject();
        }
        case 0: {
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Invalid parameters");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.addToFavorites()");
            responseMap.insert("response", responseObj);
            break;
        }
        case 1: {
            QVariantMap responseObj;
            QVariantMap okObj;
            okObj.insert("dsc", "Successfully added");
            responseObj.insert("ok", okObj);
            responseMap.insert("method", "LinBa.addToFavorites()");
            responseMap.insert("response", responseObj);
            break;
        }
    }
    return QJsonObject::fromVariantMap(responseMap);
}

QVector<Film> FavoritesAction::getFavoriteFilms(const QString& token){
    auto user = UserAuthorizationManager::getInstance().getUser(token);
    return ManagerDB::getFavoritesFilms(*(user.data()));
}

QJsonObject FavoritesAction::getFavoritesFilmsResponse(const QVector<Film>&& films){
    QJsonArray array;
    QVariantMap responseMap;
    QVariantMap responseObj;
    QVariantMap okObj;
    for(Film film : films){
        array.append(film.serialize());
    }
    okObj.insert("films", array);
    responseObj.insert("ok", okObj);
    responseMap.insert("method", "LinBa.getFavoriteFilms()");
    responseMap.insert("response", responseObj);
    return QJsonObject::fromVariantMap(responseMap);
}

int FavoritesAction::deleteFromFavorites(const QString& token, int filmId){
    if(UserAuthorizationManager::getInstance().isTokenExists(token)){
        Film::FilmDBController dbCont;
        if(dbCont.isFilmExists(filmId)){
            auto user = UserAuthorizationManager::getInstance().getUser(token);
            ManagerDB::deleteFilmsFromFavorites(*(user.data()), filmId);
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}

QJsonObject FavoritesAction::deleteFromFavoritesResponse(int result){
    QVariantMap responseMap;
    switch(result){
        case -1: {
           return QJsonObject();
        }
        case 0: {
            QVariantMap responseObj;
            QVariantMap errorObj;
            errorObj.insert("dsc", "Invalid parameters");
            responseObj.insert("error", errorObj);
            responseMap.insert("method", "LinBa.addToFavorites()");
            responseMap.insert("response", responseObj);
            break;
        }
        case 1: {
            QVariantMap responseObj;
            QVariantMap okObj;
            okObj.insert("dsc", "Successfully deleted");
            responseObj.insert("ok", okObj);
            responseMap.insert("method", "LinBa.addToFavorites()");
            responseMap.insert("response", responseObj);
            break;
        }
    }
    return QJsonObject::fromVariantMap(responseMap);

}
