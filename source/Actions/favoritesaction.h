#ifndef FAVORITESACTION_H
#define FAVORITESACTION_H


#include "action.h"
#include "Entity/film.h"

class FavoritesAction : public qttp::Action
{
public:
    FavoritesAction() : Action() {}
    virtual ~FavoritesAction() {}
    const char* getName() const {return "favorites_action";}

    void onGet(qttp::HttpData &data);
    void onPost(qttp::HttpData &data);

protected:
    int addToFavorites(const QString& token, int filmId);
    int deleteFromFavorites(const QString& token, int filmId);
    QVector<Film> getFavoriteFilms(const QString& token);
    QJsonObject getFavoritesFilmsResponse(const QVector<Film>&& films);
    QJsonObject addToFavoritesResponse(int result);
    QJsonObject deleteFromFavoritesResponse(int result);
};

#endif // FAVORITESACTION_H
