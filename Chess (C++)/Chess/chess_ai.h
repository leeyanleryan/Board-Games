#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <QObject>

class Chess;

class ChessAI : public QObject
{
    Q_OBJECT

public:
    ChessAI(Chess *chessInstance);

    void setDifficulty(int computerDifficulty);

    void makeMove();

private:
    Chess *chess;

    int difficulty;
};

#endif // CHESS_AI_H
