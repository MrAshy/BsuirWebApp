#ifndef GETACTORSACTION_H
#define GETACTORSACTION_H

#include "action.h"
#include "Entity/actor.h"

class GetActorsAction : public qttp::Action
{
public:
    GetActorsAction();
    const char* getName() const{ return "getActors_action"; }
    void onGet(qttp::HttpData &data);
protected:
    QVector<Actor> getActors();
    QVector<Actor> getActorsByFilm(int filmId);
    QJsonObject response(const QVector<Actor>&& actors);
    QJsonObject executeRequest(const QJsonObject& request);
};

#endif // GETACTORSACTION_H
