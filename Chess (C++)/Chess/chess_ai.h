#ifndef CHESS_AI_H
#define CHESS_AI_H

#include <QObject>

class Chess;

class ChessAI : public QObject
{
    Q_OBJECT

public:
    ChessAI(Chess *chessInstance);

    void makeMove();

private:
    Chess *chess;
};

#endif // CHESS_AI_H
