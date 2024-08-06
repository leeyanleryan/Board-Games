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

    std::vector<QPair<int, int>> kingCoords;
    std::vector<bool> kingHasMoved;

    QSet<QPair<int, int>> getLegalMoves(std::array<std::array<char, 8>, 8> chessBoard, QPair<int, int> sCoord, int currTurn);

private:
    Chess *chess;

    QSet<QPair<int, int>> legalMoves;

    std::array<std::array<char, 8>, 8> board;

    QPair<int, int> sourceCoord;
    int sourceRow;
    int sourceCol;
    char sourcePiece;

    QPair<int, int> kingCoord;
    int kingRow;
    int kingCol;

    int turn;

    std::array<QSet<char>, 2> piecesSet;

    std::array<char, 2> pawnPieces;
    std::array<char, 2> rookPieces;
    std::array<char, 2> knightPieces;
    std::array<char, 2> bishopPieces;
    std::array<char, 2> queenPieces;
    std::array<char, 2> kingPieces;

    std::array<int, 2> pawnDirections;

    bool getLegalMovesHelper(int targetRow, int targetCol);

    void addLegalMoveIfNotPinned(QPair<int, int> targetCoord, int targetRow, int targetCol, char targetPiece);

    void getLegalPawnMovement();

    void getLegalRookMovement();

    void getLegalKnightMovement();

    void getLegalBishopMovement();

    void getLegalQueenMovement();

    void getLegalKingMovement();

    std::vector<QPair<int, int>> findEnemyPawn();

    bool findEnemyRookHelper(std::vector<QPair<int, int>> &enemyRookPool, int targetRow, int targetCol);

    std::vector<QPair<int, int>> findEnemyRook();

    std::vector<QPair<int, int>> findEnemyKnight();

    bool findEnemyBishopHelper(std::vector<QPair<int, int>> &enemyRookPool, int targetRow, int targetCol);

    std::vector<QPair<int, int>> findEnemyBishop();

    std::vector<QPair<int, int>> findEnemyQueen();

    bool kingIsChecked();

    bool kingIsMated();
};

#endif // CHESS_LOGIC_H
