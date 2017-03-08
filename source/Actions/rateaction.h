#ifndef RATEACTION_H
#define RATEACTION_H

#include "action.h"
#include "Entity/rate.h"
#include "Entity/user.h"

class RateAction : public qttp::Action
{
public:
    RateAction() : qttp::Action() {}
    const char* getName() const { return "update_rate"; }
    void onGet(qttp::HttpData &data);
    void onPost(qttp::HttpData &data);
protected:
    int updateRate(const User& user, int filmId, int rate);
    
    QJsonObject getRateResponse(QVector<Rate>&& rates);
    QJsonObject updateRateResponse(int result);
    
    QVector<Rate> getRates(int userId);
};

#endif // UPDATERATEACTION_H
