#include "Entity/user.h"
#include "DBControllers/managerdb.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

void User::setLogin(const QString& login){
    this->login = login;
}

void User::setPassword(const QString& password){
    this->password = password;
}

void User::setId(uint32_t id){
    this->id = id;
}


int User::UserDBController::hasUser(const QString& login, const QString& password){
    int result = -1;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("hasUserConnect");
        if(dbConnect.open()){
            QSqlQuery query(dbConnect);
            QString queryString = "SELECT login, cast(aes_decrypt(password, :Key) AS char(255)) AS pass FROM filmsDB.users WHERE login = :Login";
            query.prepare(queryString);
            query.bindValue(":Login", login);
            query.bindValue(":Key", "TrYHaCkIt");
            query.exec();
            if(query.next()){
                if(query.value("pass").toString() == password){
                    result = 1;
                }
            }
            else{
                result = 0;
            }
            qDebug()<<query.lastError();
            query.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("hasUserConnect");
    return result; // db error
}

int User::UserDBController::hasUser(const QString& login){
    int result = -1;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("hasUserConnect");
        if(dbConnect.open()){
            QSqlQuery query(dbConnect);
            QString queryString = "SELECT login FROM filmsDB.users WHERE login = :Login";
            query.prepare(queryString);
            query.bindValue(":Login", login);
            query.exec();
            if(query.next()){
                result = 1;
            }
            else{
                result = 0;
            }
            query.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("hasUserConnect");
    return result; // db error
}

int User::UserDBController::insert(const User& user){
    int result = -1;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("insertUserConnect");
        if(dbConnect.open()){
            QSqlQuery query(dbConnect);
            QString queryString = "INSERT INTO filmsDB.users (login, password) values (:Login, aes_encrypt(:Password, :Key))";
            query.prepare(queryString);
            query.bindValue(":Login", user.getLogin());
            query.bindValue(":Password", user.getPassword());
            query.bindValue(":Key", "TrYHaCkIt");
            if(query.exec()){
                result = 1;
            }
            else{
                result = 0;
            }
            query.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("insertUserConnect");
    return result;
}

User* User::UserDBController::getUser(const QString& login){
    User* user = nullptr;
    {
        QSqlDatabase dbConnect = ManagerDB::connect("getUserConnect");
        if(dbConnect.open()){
            QSqlQuery checkLoginQuery(dbConnect);
            QString query = "SELECT userId, cast(aes_decrypt(password, :Key) AS char(255)) AS pass FROM FilmsDB.users where login=:login";
            checkLoginQuery.prepare(query);
            checkLoginQuery.bindValue(":login", login);
            checkLoginQuery.bindValue(":Key", "TrYHaCkIt");
            checkLoginQuery.exec();
            if(checkLoginQuery.next()){
                user = new User();
                user->setId(checkLoginQuery.value("userId").toUInt());
                user->setLogin(login);
                user->setPassword(checkLoginQuery.value("pass").toString());
            }
            checkLoginQuery.finish();
            dbConnect.close();
        }
    }
    ManagerDB::disconnect("getUserConnect");
    return user;
}




