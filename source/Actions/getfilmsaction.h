#ifndef GETFILMSACTION_H
#define GETFILMSACTION_H

#include "action.h"
#include "Entity/film.h"


class GetFilmsAction : public qttp::Action
{
public:
    GetFilmsAction() : Action() {}

    const char* getName() const { return "getFilms_action"; }
    void onGet(qttp::HttpData& data);

protected:
    virtual QJsonObject response(int result);

};

#endif // GETFILMSACTION_H
