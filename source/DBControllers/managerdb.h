#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QSqlDatabase>
#include "Entity/film.h"
#include "Entity/user.h"
#include <QVector>

class ManagerDB
{
public:
    static QSqlDatabase connect(const QString& connectionName);
    static void disconnect(const QString& connectionName);
    static void addFilmsToFavorites(const User& user, int filmId);
    static void deleteFilmsFromFavorites(const User& user, int filmId);
    static QVector<Film> getFavoritesFilms(const User& user);
    static bool isFilmInFavorites(const User& user, int filmId);
    static int getRateId(int userId, int filmId);
    static int addRate(int userId, int filmId, int rate);
    static int updateRate(int userRateId, int rate);

    ManagerDB() = delete;
    ManagerDB(const ManagerDB& other) = delete;
    ManagerDB& operator=(const ManagerDB& other) = delete;
};

#endif // MANAGERDB_H
