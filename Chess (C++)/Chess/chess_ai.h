#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <QObject>

class Chess;

class ChessAI : public QObject
{
    Q_OBJECT

public:
    ChessAI(Chess *chessInstance);

    void setDifficulty(int computerDifficulty) { difficulty = computerDifficulty; }

    void setTurn(int computerTurn) { turn = computerTurn; }

    void makeMove();

    char promotePawn(QPair<int, int> sourceCoord, QPair<int, int> targetCoord);

private:
    Chess *chess;

    int difficulty;

    int turn;
};

#endif // CHESS_AI_H
