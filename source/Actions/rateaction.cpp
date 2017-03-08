#include "rateaction.h"

#include "Other/UserAuthorizationManager.h"
#include "DBControllers/managerdb.h"
#include "Entity/rate.h"

void RateAction::onPost(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    QString token = request.value("token").toString();
    if(UserAuthorizationManager::getInstance().isTokenExists(token)){
        auto user = UserAuthorizationManager::getInstance().getUser(token);
        if(request.contains("filmId") && request.contains("rate")){
            int filmId = request.value("filmId").toInt();
            int rate = request.value("rate").toInt();
            QJsonObject& response = data.getResponse().getJson();
            response = updateRateResponse(updateRate(*(user.data()), filmId, rate));
        }
    }
}

void RateAction::onGet(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    QString token = request.value("token").toString();
    if(UserAuthorizationManager::getInstance().isTokenExists(token)){
       auto user = UserAuthorizationManager::getInstance().getUser(token);
       QJsonObject& response = data.getResponse().getJson();
       response = getRateResponse(getRates(user.data()->getId()));
    }
}

QJsonObject RateAction::updateRateResponse(int result){
    QVariantMap responseMap;
    if(result){
        QVariantMap responseObj;
        QVariantMap okObj;
        okObj.insert("dsc", "Rate was accepted");
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LinBa.updateRate()");
        responseMap.insert("response", responseObj);
    }
    else{
        QVariantMap responseObj;
        QVariantMap errorObj;
        errorObj.insert("dsc", "Server error");
        responseObj.insert("error", errorObj);
        responseMap.insert("method", "LinBa.updateRate()");
        responseMap.insert("response", responseObj);
    }
    return QJsonObject::fromVariantMap(responseMap);
}

int RateAction::updateRate(const User &user, int filmId, int rate){
    int id = ManagerDB::getRateId(user.getId(), filmId);
    Rate rates;
    rates.setFilmId(filmId);
    rates.setRate(rate);
    rates.setUserId(user.getId());
    Rate::RateDBController db;
    //TODO updateFilm
    if(id >= 0){
        return db.update(rates, id);
    }
    return db.insert(rates);
}

QVector<Rate> RateAction::getRates(int userId){
    Rate::RateDBController db;
    return db.getUserRates(userId);
}

QJsonObject RateAction::getRateResponse(QVector<Rate> &&rates){
    QVariantMap responseMap;
    if(!rates.isEmpty()){
        QVariantMap responseObj;
        QVariantMap okObj;
        QJsonArray array;
        for(Rate rate : rates){
            array.append(rate.serialize());
        }
        okObj.insert("rates", array);
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LinBa.getRates()");
        responseMap.insert("response", responseObj);
    }
    return QJsonObject::fromVariantMap(responseMap);
}
