#include "rate.h"

#include "DBControllers/managerdb.h"
#include <QSqlQuery>
#include <QVariant>

Rate::Rate() {}

QJsonObject Rate::serialize() const {
    QJsonObject obj;
    obj.insert("filmId", filmId);
    obj.insert("rate", rate);
    return obj;
}

int Rate::RateDBController::insert(const Rate& rate){
    bool res = false;
    {
        QSqlDatabase db = ManagerDB::connect("addRate");
        if(db.open()){
            QString queryStr = "INSERT INTO FilmsDB.UsersRate (userId, idFilms, rate) VALUES (:user, :film, :rate)";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":user", rate.getUserId());
            query.bindValue(":film", rate.getFilmId());
            query.bindValue(":rate", rate.getRate());
            res = query.exec();
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("addRate");
    return res;
}

int Rate::RateDBController::update(const Rate& rate, int id){
    bool res = false;
    {
        QSqlDatabase db = ManagerDB::connect("updateRate");
        if(db.open()){
            QString queryStr = "UPDATE FilmsDB.UsersRate SET rate=:rate, userId=:user, idFilms=:film WHERE userRateId=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", id);
            query.bindValue(":rate", rate.getRate());
            query.bindValue(":user", rate.getUserId());
            query.bindValue(":film", rate.getFilmId());
            res = query.exec();
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("updateRate");
    return res;
}

QVector<Rate> Rate::RateDBController::getUserRates(int userId){
    QVector<Rate> rates;
    {
        QSqlDatabase db = ManagerDB::connect("getRates");
        if(db.open()){
            QString queryStr = "SELECT* FROM FilmsDB.UsersRate WHERE userId=:user";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":user", userId);
            query.exec();
            while(query.next()){
                Rate rate;
                rate.setFilmId(query.value("idFilms").toInt());
                rate.setRate(query.value("rate").toInt());
                rates.push_back(rate);
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getRates");
    return rates;
}
