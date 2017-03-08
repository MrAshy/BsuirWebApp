#ifndef RATE_H
#define RATE_H

#include <QJsonObject>
#include <QVector>

class Rate
{
public:
    Rate();
    void setFilmId(int id) { this->filmId = id; }
    void setRate(int rate) { this->rate = rate; }
    void setUserId(int id) { this->userId = id; }
    
    int getRate() const { return rate; }
    int getFilmId() const {return filmId; }
    int getUserId() const { return userId; }
    
    QJsonObject serialize() const;
    
    class RateDBController {
    public:
        int insert(const Rate& rate);
        int update(const Rate& rate, int id);
        QVector<Rate> getUserRates(int userId);
    };

private:
    int userId;
    int filmId;
    int rate;
};

#endif // RATE_H
