#ifndef PRODUCER_H
#define PRODUCER_H

#include <QString>
#include <QJsonObject>
#include <QVector>

class Producer
{
public:
    Producer();

    int getId() const { return id; }
    QString getName() const { return name; }
    QString getSecondName() const { return sname; }
    int getYearBorn() const { return yearBorn; }
    QString getImageLink() const { return imageLink; }
    int getCountryId() const { return countryId; }

    void setId(int id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setSecondName(const QString& sname) { this->sname = sname; }
    void setYearBorn(int year) { this->yearBorn = year; }
    void setImageLink(const QString& link) { this->imageLink = link; }
    void setCountryId(int id) { this->countryId = id; }

    QJsonObject serialize() const;

    class ProducerDBController{
        public:
            QVector<Producer> getProducers();
            Producer getProducer(int id);
            QString getCountry(const Producer& producer) const;
            Producer getProducerById(int id);
    };

private:
    int id;
    QString name;
    QString sname;
    int yearBorn;
    QString imageLink;
    int countryId;
};

#endif // PRODUCER_H
