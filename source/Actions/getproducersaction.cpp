#include "getproducersaction.h"
#include "Other/UserAuthorizationManager.h"

GetProducersAction::GetProducersAction() {}

void GetProducersAction::onGet(qttp::HttpData &data){
    const QJsonObject& request = data.getRequest().getJson();
    if(request.contains("token")){
        if(UserAuthorizationManager::getInstance().isTokenExists(request.value("token").toString())){
            QJsonObject& response = data.getResponse().getJson();
            response = executeRequest(request);
        }
    }
}


QVector<Producer> GetProducersAction::getProducers(){
    QVector<Producer> producers;
    Producer::ProducerDBController db;
    producers = db.getProducers();
    return producers;
}

QJsonObject GetProducersAction::response(const QVector<Producer>&& producers){
    QVariantMap responseMap;
    if(!producers.isEmpty()){
        QVariantMap responseObj;
        QVariantMap okObj;
        QJsonArray array;
        for(Producer producer : producers){
            array.append(producer.serialize());
        }
        okObj.insert("producers", array);
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LibBa.getProducers()");
        responseMap.insert("response", responseObj);
    }
    else{
        QVariantMap responseObj;
        QVariantMap errorObj;
        errorObj.insert("dsc", "Server error");
        responseObj.insert("error", errorObj);
        responseMap.insert("method", "LibBa.getProducers()");
        responseMap.insert("response", responseObj);
    }
    return QJsonObject::fromVariantMap(responseMap);
}

Producer GetProducersAction::getProducer(int id){
    Producer producer;
    Producer::ProducerDBController db;
    producer = db.getProducerById(id);
    return producer;
}

QJsonObject GetProducersAction::response(const Producer &producer){
    QVariantMap responseMap;
    if(!producer.getName().isEmpty()){
        QVariantMap responseObj;
        QVariantMap okObj;
        okObj.insert("producer", producer.serialize());
        responseObj.insert("ok", okObj);
        responseMap.insert("method", "LinBa.getProducer()");
        responseMap.insert("response", responseObj);
    }
    else{
        QVariantMap responseObj;
        QVariantMap errorObj;
        errorObj.insert("dsc", "Server problem");
        responseObj.insert("error", errorObj);
        responseMap.insert("method", "LinBa.getProducer()");
        responseMap.insert("response", responseObj);
    }
    return QJsonObject::fromVariantMap(responseMap);
}

QJsonObject GetProducersAction::executeRequest(const QJsonObject &request){
    QString event = request.value("event").toString();
    if(event == "all"){
        return response(getProducers());
    }
    else if(event == "id"){
        int id = request.value("id").toString().toInt();
        return response(getProducer(id));
    }
    return QJsonObject();
}
