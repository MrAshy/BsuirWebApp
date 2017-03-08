#include "actor.h"
#include "DBControllers/managerdb.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Actor::Actor() {}


QJsonObject Actor::serialize() const{
    QJsonObject obj;
    obj.insert("id", id);
    obj.insert("name", name);
    obj.insert("sname", sname);
    obj.insert("year", yearBorn);
    Actor::ActorDBController db;
    QString country = db.getCountry(*this);
    obj.insert("country", country);
    obj.insert("imageLink", imageLink);
    return obj;
}


QString Actor::ActorDBController::getCountry(const Actor& actor) const{
    QString country;
    {
        QSqlDatabase db = ManagerDB::connect("getCountryForActor");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.country"
                               " WHERE country.idCountry=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", actor.getCountryId());
            query.exec();
            if(query.next()){
                country = query.value("name").toString();
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getCountryForActor");
    return country;
}

QVector<Actor> Actor::ActorDBController::getActors(){
    QVector<Actor> actors;
    {
        QSqlDatabase db = ManagerDB::connect("getActors");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.actors";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.exec();
            while(query.next()){
                Actor actor;
                actor.setId(query.value("idActors").toInt());
                actor.setName(query.value("name").toString());
                actor.setSecondName(query.value("sname").toString());
                actor.setYear(query.value("yearBorn").toInt());
                actor.setImageLink(query.value("imageLink").toString());
                actor.setCountyId(query.value("countryId").toInt());
                actors.push_back(actor);
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getActors");
    return actors;
}

Actor Actor::ActorDBController::getActorById(int id){
    Actor actor;
    {
        QSqlDatabase db = ManagerDB::connect("getActorById");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.actors WHERE idActors=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", id);
            query.exec();
            if(query.next()){
                actor.setId(query.value("idActors").toInt());
                actor.setName(query.value("name").toString());
                actor.setSecondName(query.value("sname").toString());
                actor.setYear(query.value("yearBorn").toInt());
                actor.setImageLink(query.value("imageLink").toString());
                actor.setCountyId(query.value("countryId").toInt());
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getActorById");
    return actor;
}

QVector<Actor> Actor::ActorDBController::getActorByFilm(int filmId){
    QVector<Actor> actors;
    {
        QSqlDatabase db = ManagerDB::connect("getActorsByFilm");
        if(db.open()){
            QString queryStr = "SELECT actors.* FROM FilmsDB.actors, FilmsDB.actors_films WHERE "
                               "actors_films.actorsId=actors.idActors AND actors_films.filmsId=:id";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":id", filmId);
            query.exec();
            while(query.next()){
                Actor actor;
                actor.setId(query.value("idActors").toInt());
                actor.setName(query.value("name").toString());
                actor.setSecondName(query.value("sname").toString());
                actor.setImageLink(query.value("imageLink").toString());
                actor.setYear(query.value("yearBorn").toInt());
                actor.setCountyId(query.value("countryId").toInt());
                actors.push_back(actor);
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getActorsByFilm");
    return actors;
}
