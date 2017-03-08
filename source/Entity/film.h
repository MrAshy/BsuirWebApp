#ifndef FILM_H
#define FILM_H

#include <QString>
#include <QJsonObject>
#include <QStringList>

class Film
{
public:

    Film() {}

    Film(int id, const QString& name, int year,
         double rate, int producerId, const QString& link, const QString& imageLink);

    QString getName() const { return name; }
    QString getLink() const { return link; }
    QString getImageLink() const { return imageLink; }
    double getRate() const { return rate; }
    int getYear() const { return year; }
    int getId() const { return id; }
    int getProducerId() const { return producerId; }

    void setName(const QString& name){ this->name = name; }
    void setLink(const QString& link) { this->link = link; }
    void setImageLink(const QString& link) { this->imageLink = link; }
    void setRate(double rate) { this->rate = rate; }
    void setYear(int year) { this->year = year; }
    void setId(int id) { this->id = id; }
    void setProducerId(int id) { this->producerId = id; }

    class FilmDBController{
        public:
            FilmDBController() {}
            QVector<Film> getFilms();
            QStringList getCountries(const Film& film);
            bool isFilmExists(int filmId);
    };

    QJsonObject serialize();

private:
    int id;
    QString name;
    int year;
    double rate;
    int producerId;
    QString link;
    QString imageLink;

};

#endif // FILM_H
