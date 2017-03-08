#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

#include "action.h"

class RegistrationAction : public qttp::Action
{
public:

    RegistrationAction() : Action() {}
    virtual ~RegistrationAction() {}
    const char* getName() const { return "registration_action"; }

    void onPost(qttp::HttpData& data);

protected:

    int registerUser(const QString& login, const QString& password);
    QJsonObject response(int result);

};

#endif // REGISTRATIONCONTROLLER_H
