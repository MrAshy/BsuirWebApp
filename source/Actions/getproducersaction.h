#ifndef GETPRODUCERSACTION_H
#define GETPRODUCERSACTION_H

#include "action.h"
#include "Entity/producer.h"

class GetProducersAction : public qttp::Action
{
public:
    GetProducersAction();
    const char* getName() const { return "getProducerc_action"; }
    void onGet(qttp::HttpData &data);

protected:
    QVector<Producer> getProducers();
    Producer getProducer(int id);
    QJsonObject response(const QVector<Producer>&& producers);
    QJsonObject response(const Producer& peoducer);
    QJsonObject executeRequest(const QJsonObject& request);
};

#endif // GETPRODUCERSACTION_H
