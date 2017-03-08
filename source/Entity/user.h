#ifndef USER_H
#define USER_H

#include <QString>


class User
{
public:
    User() {}
    User(const QString& login, const QString& password) : login(login), password(password) {}
    void setLogin(const QString& login);
    void setPassword(const QString& password);
    void setId(uint32_t id);

    uint32_t getId() const { return this->id; }
    QString getLogin() const { return this->login; }
    QString getPassword() const { return this->password; }

    class UserDBController
    {
    public:
        UserDBController() {}
        int insert(const User& user);
        int hasUser(const QString& login);
        int hasUser(const QString& login, const QString& password);
        User* getUser(const QString& login);
    };

private:
    QString login;
    QString password;
    uint32_t id;
};

#endif // USER_H
