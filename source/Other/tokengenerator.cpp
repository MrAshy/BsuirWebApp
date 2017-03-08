#include "tokengenerator.h"
#include <QTime>

QString TokenGenerator::generateNewToken(){
    qsrand(QTime().currentTime().msec());
    int index = qrand() % 10;
    qSwap(token[index], token[token.size()-1-index]);
    std::random_shuffle(token.begin(), token.end());
    return token;
}
