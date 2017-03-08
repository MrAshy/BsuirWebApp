#include "Entity/film.h"
#include "DBControllers/managerdb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVector>
#include <QJsonArray>
#include <QDebug>

Film::Film(int id, const QString& name, int year,
            double rate, int producerId, const QString& link, const QString& imageLink)
{
    this->id = id;
    this->name = name;
    this->year = year;
    this->rate = rate;
    this->producerId = producerId;
    this->link = link;
    this->imageLink = imageLink;
}

QJsonObject Film::serialize(){
    QJsonObject obj;
    QJsonArray countryArray;
    obj.insert("id", QJsonValue(id));
    obj.insert("name", QJsonValue(name));
    obj.insert("year", QJsonValue(year));
    obj.insert("rate", QJsonValue(rate));
    obj.insert("trailerLink", QJsonValue(link));
    obj.insert("imageLink", QJsonValue(imageLink));
    Film::FilmDBController db;
    QStringList countries = db.getCountries(*this);
    for(auto it = countries.begin(); it!=countries.end(); ++it){
        countryArray.append(QJsonValue(*it));
    }
    obj.insert("country", countryArray);
    obj.insert("producerId", producerId);
    return obj;
}


QVector<Film> Film::FilmDBController::getFilms(){
    QVector<Film> films;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("getFilmsConnect");
        if(dbConnect.open()){
            QString queryStr = "SELECT * from FilmsDB.Films";
            QSqlQuery query(dbConnect);
            query.prepare(queryStr);
            query.exec();
            while(query.next()){
                Film film;
                film.setName(query.value("name").toString());
                film.setLink(query.value("link").toString());
                film.setImageLink(query.value("imageLink").toString());
                film.setRate(query.value("rate").toDouble());
                film.setId(query.value("idFilms").toInt());
                film.setYear(query.value("year").toInt());
                film.setProducerId(query.value("producerId").toInt());
                films.push_back(film);
            }
            query.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("getFilmsConnect");
    return films;
}

QStringList Film::FilmDBController::getCountries(const Film &film){
    QStringList countries;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("setCountriesConnect");
        QString queryString = "SELECT country.* from FilmsDB.country, FilmsDB.films, "
                              "FilmsDB.films_country "
                              "WHERE country.idCountry = films_country.countryId AND "
                              "films.idFilms = films_country.filmsId AND "
                              "films.name=:FilmName";
        if(dbConnect.open()){
            QSqlQuery query(dbConnect);
            query.prepare(queryString);
            query.bindValue(":FilmName", film.getName());
            query.exec();
            while(query.next()){
                countries.append(query.value("name").toString());
            }
            query.finish();
            dbConnect.close();
        }

    }
    ManagerDB::disconnect("setCountriesConnect");
    return countries;
}

bool Film::FilmDBController::isFilmExists(int filmId){
    bool exists = false;
    {
        QSqlDatabase db = ManagerDB::connect("isFilm");
        if(db.open()){
            QString queryString = "SELECT * FROM FilmsDB.films WHERE idFilms=:id";
            QSqlQuery query(db);
            query.prepare(queryString);
            query.bindValue(":id", filmId);
            query.exec();
            if(query.next()){
                exists = true;
            }
            qDebug()<<query.lastError();
            query.finish();
            db.close();
        }
    }
    ManagerDB::disconnect("isFilm");
    return exists;
}
