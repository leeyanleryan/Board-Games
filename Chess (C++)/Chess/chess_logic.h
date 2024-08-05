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

    //bool isPinned;

    //bool isChecked;

    bool getLegalMovesHelper(int targetRow, int targetCol);

    void addLegalMoveIfNotPinned(QPair<int, int> targetCoord, int targetRow, int targetCol, QString targetPiece);

    void getLegalPawnMovement();

    void getLegalRookMovement();

    void getLegalKnightMovement();

    void getLegalBishopMovement();

    void getLegalQueenMovement();

    void getLegalKingMovement();

    bool hitEnemyPiece(int eRow, int eCol);

    bool hitPiece(int targetRow, int targetCol);

    std::vector<QPair<int, int>> findEnemyPawn();

    std::vector<QPair<int, int>> findEnemyRook();

    std::vector<QPair<int, int>> findEnemyKnight();

    std::vector<QPair<int, int>> findEnemyBishop();

    std::vector<QPair<int, int>> findEnemyQueen();

    std::vector<QPair<int, int>> findEnemyKing();

    bool kingIsChecked();

    bool kingIsMated();
};

#endif // CHESS_LOGIC_H
