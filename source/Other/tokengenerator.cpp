#include "tokengenerator.h"
#include <QTime>
#include <QString>

QString TokenGenerator::generateNewToken(){
    qsrand(QTime().currentTime().msec());
    int index = qrand() % 10;
    QChar temp = token[index];
    token.replace(index, 1, token[token.size()-index-1]);
    token.replace(token.size()-index-1, 1, temp);
    std::random_shuffle(token.begin(), token.end());
    return token;
}
