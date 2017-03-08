#include "DBControllers/managerdb.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


QSqlDatabase ManagerDB::connect(const QString& connectionName){
    QSqlDatabase dbConnect = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    dbConnect.setHostName("localhost");
    dbConnect.setUserName("root");
    dbConnect.setPassword("4818colonel");
    return dbConnect;
}

void ManagerDB::disconnect(const QString& connectionName){
    QSqlDatabase::removeDatabase(connectionName);
}

void ManagerDB::addFilmsToFavorites(const User& user, int filmId){
    {
        QSqlDatabase dbConnection = ManagerDB::connect("addToFavorites");
        if(dbConnection.open()){
            QString queryString = "INSERT INTO FilmsDB.users_films (idUser, idFilms) VALUES "
                                  "(:idUser, :idFilm)";
            qDebug()<<user.getId();
            QSqlQuery query(dbConnection);
            query.prepare(queryString);
            query.bindValue(":idUser", user.getId());
            query.bindValue(":idFilm", filmId);
            query.exec();
            qDebug()<<query.lastError();
            query.finish();
            dbConnection.close();

        }
    }
    ManagerDB::disconnect("addToFavorites");
}

QVector<Film> ManagerDB::getFavoritesFilms(const User& user){
    QVector<Film> films;
    {
        QSqlDatabase db = ManagerDB::connect("getFavorites");
        if(db.open()){
            QString queryStr = "SELECT films.* FROM FilmsDB.films, FilmsDB.users_films "
                               "WHERE users_films.idFilms=films.idFilms AND "
                               "users_films.idUser=:idUser";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":idUser", user.getId());
            query.exec();
            Film::FilmDBController dbCont;
            while(query.next()){
                Film film;
                film.setId(query.value("idFilms").toInt());
                film.setName(query.value("name").toString());
                film.setRate(query.value("rate").toDouble());
                film.setYear(query.value("year").toInt());
                film.setLink(query.value("link").toString());
                film.setImageLink(query.value("imageLink").toString());
                film.setProducerId(query.value("producerId").toInt());
                films.push_back(film);
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getFavorites");
    return films;
}

void ManagerDB::deleteFilmsFromFavorites(const User &user, int filmId){
    {
        QSqlDatabase db = ManagerDB::connect("deleteFromFavorites");
        if(db.open()){
            QString queryStr = "DELETE FROM FilmsDB.users_films WHERE "
                               "idUser=:idUser AND idFilms=:idFilm";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":idUser", user.getId());
            query.bindValue(":idFilm", filmId);
            query.exec();
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("deleteFromFavorites");
}

bool ManagerDB::isFilmInFavorites(const User &user, int filmId){
    bool exists = false;
    {
        QSqlDatabase db = ManagerDB::connect("isFilmIsFavorites");
        if(db.open()){
            QString queryStr = "SELECT * FROM FilmsDB.users_films WHERE idUser=:idUser AND "
                               "idFilms=:idFilm";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":idUser", user.getId());
            query.bindValue(":idFilm", filmId);
            query.exec();
            if(query.next()){
                exists = true;
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("isFilmIsFavorites");
    return exists;
}

int ManagerDB::getRateId(int userId, int filmId){
    int id = -1;
    {
        QSqlDatabase db = ManagerDB::connect("getRateId");
        if(db.open()){
            QString queryStr = "SELECT userRateId FROM FilmsDB.UsersRate WHERE userId=:user AND idFilms=:film";
            QSqlQuery query(db);
            query.prepare(queryStr);
            query.bindValue(":user", userId);
            query.bindValue(":film", filmId);
            query.exec();
            if(query.next()){
                id = query.value("userRateId").toInt();
            }
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("getRateId");
    return id;
}

