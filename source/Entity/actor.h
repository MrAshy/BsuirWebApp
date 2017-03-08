#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QJsonObject>
#include <QVector>

#include "Entity/film.h"

class Actor
{
public:
    Actor();

    QString getName() const { return this->name; }
    QString getSecondName() const { return this->sname; }
    QString getImageLink() const { return this->imageLink; }
    int getId() const { return this->id; }
    int getCountryId() const { return this->countryId; }
    int getYearBorn() const { return this->yearBorn; }

    void setName(const QString& name) {this->name = name;}
    void setSecondName(const QString& sname) {this->sname = sname;}
    void setImageLink(const QString& link) {this->imageLink = link;}
    void setCountyId(int id) {this->countryId = id;}
    void setId(int id) {this->id = id;}
    void setYear(int year) {this->yearBorn = year;}

    QJsonObject serialize() const;

    class ActorDBController{
    public:
        ActorDBController() {}
        QVector<Actor> getActors();
        QString getCountry(const Actor& actor) const;
        Actor getActorById(int id);
        QVector<Actor> getActorByFilm(int filmId);
    };

private:
    QString name;
    QString sname;
    QString imageLink;
    int yearBorn;
    int id;
    int countryId;
};

#endif // ACTOR_H
