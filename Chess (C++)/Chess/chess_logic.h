#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include <QObject>
#include <QSet>

class Chess;

class ChessLogic : public QObject
{
    Q_OBJECT

public:
    ChessLogic(Chess *chessInstance);

    std::vector<std::vector<QString>> board;

    QSet<QPair<int, int>> legalMoves;

    void getLegalPawnMovement();

    void getLegalRookMovement();

    void getLegalKnightMovement();

    void getLegalBishopMovement();

    void getLegalQueenMovement();

    void getLegalKingMovement();

private:
    Chess *chess;
};

#endif // CHESS_LOGIC_H
