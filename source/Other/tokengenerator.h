#ifndef TOKENGENERATOR_H
#define TOKENGENERATOR_H

#include <QString>

class TokenGenerator
{
public:
    TokenGenerator() : token("123AB456CD789EF") {}
    void setStartSequence(const QString& sequence) { token = sequence; }
    QString getToken() { return token; }
    QString generateNewToken();
private:
    QString token;
};

#endif // TOKENGENERATOR_H
