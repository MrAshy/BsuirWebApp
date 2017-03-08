#include "producer.h"
#include "DBControllers/managerdb.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

Producer::Producer() {}


QJsonObject Producer::serialize() const{
    QJsonObject obj;
    obj.insert("id", QJsonValue(id));
    obj.insert("name", QJsonValue(name));
    obj.insert("sname", QJsonValue(sname));
    obj.insert("year", QJsonValue(yearBorn));
    obj.insert("imageLink", QJsonValue(imageLink));
    Producer::ProducerDBController db;
    QString country = db.getCountry(*this);
    obj.insert("country", country);
    return obj;
}

QVector<Producer> Producer::ProducerDBController::getProducers(){
    QVector<Producer> producers;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("getProducersConnect");
        if(dbConnect.open()){
            QString queryString = "SELECT * FROM FilmsDB.Producer";
            QSqlQuery query(dbConnect);
            query.prepare(queryString);
            query.exec();
            while(query.next()){
                Producer producer;
                producer.setId(query.value("idProducer").toInt());
                producer.setName(query.value("name").toString());
                producer.setSecondName(query.value("sname").toString());
                producer.setYearBorn(query.value("yearBorn").toInt());
                producer.setImageLink(query.value("imageLink").toString());
                producer.setCountryId(query.value("countryId").toInt());
                producers.push_back(producer);
            }
            query.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("getProducersConnect");
    return producers;
}

Producer Producer::ProducerDBController::getProducer(int id){
    Producer producer;
    {
        QSqlDatabase db = ManagerDB::connect("getProducerById");
        if(db.open()){
            QString queryStr = "SELECT* FROM FilmsDB.producer WHERE producer.idProducer=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", id);
            query.exec();
            if(query.next()){
                producer.setId(id);
                producer.setName(query.value("name").toString());
                producer.setSecondName(query.value("sname").toString());
                producer.setImageLink(query.value("imageLink").toString());
                producer.setYearBorn(query.value("yearBorn").toInt());
                producer.setCountryId(query.value("countryId").toInt());
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getProducerById");
    return producer;
}

QString Producer::ProducerDBController::getCountry(const Producer &producer) const{
    QString country;
    {
        QSqlDatabase db = ManagerDB::connect("getCountryForProducer");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.country"
                               " WHERE country.idCountry=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", producer.getCountryId());
            query.exec();
            if(query.next()){
                country = query.value("name").toString();
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getCountryForProducer");
    return country;
}

Producer Producer::ProducerDBController::getProducerById(int id){
    Producer producer;
    {
        QSqlDatabase db = ManagerDB::connect("getProducerById");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.producer WHERE idProducer=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", id);
            query.exec();
            if(query.next()){
                producer.setId(query.value("idProducer").toInt());
                producer.setName(query.value("name").toString());
                producer.setSecondName(query.value("sname").toString());
                producer.setYearBorn(query.value("yearBorn").toInt());
                producer.setImageLink(query.value("imageLink").toString());
                producer.setCountryId(query.value("countryId").toInt());
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getProducerById");
    return producer;
}
