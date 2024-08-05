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

    QSet<QPair<int, int>> getLegalMoves(std::vector<std::vector<QString>> chessBoard, QPair<int, int> sourceCoord, int turn);

private:
    Chess *chess;

    std::vector<QPair<int, int>> kingCoords;

    std::vector<bool> kingCanCastle;

    QSet<QPair<int, int>> legalMoves;

    std::vector<std::vector<QString>> board;

    QPair<int, int> sourceCoord;

    int sourceRow;

    int sourceCol;

    QString sourcePiece;

    int turn;

    void getLegalPawnMovement();

    void getLegalRookMovement();

    void getLegalKnightMovement();

    void getLegalBishopMovement();

    void getLegalQueenMovement();

    void getLegalKingMovement();

    std::vector<QPair<int, int>> findEnemyPawn();

    std::vector<QPair<int, int>> findEnemyRook();

    std::vector<QPair<int, int>> findEnemyKnight();

    std::vector<QPair<int, int>> findEnemyBishop();

    std::vector<QPair<int, int>> findEnemyQueen();

    std::vector<QPair<int, int>> findEnemyKing();

    bool pieceIsPinned();

    bool kingIsChecked();

    bool kingIsMated();
};

#endif // CHESS_LOGIC_H
