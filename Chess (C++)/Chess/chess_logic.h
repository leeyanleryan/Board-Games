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

    std::array<char, 2> pawnPieces;
    std::array<char, 2> rookPieces;
    std::array<char, 2> knightPieces;
    std::array<char, 2> bishopPieces;
    std::array<char, 2> queenPieces;
    std::array<char, 2> kingPieces;

    std::array<bool, 2> kingHasMoved;

    std::array<bool, 2> leftRookHasMoved;
    std::array<bool, 2> rightRookHasMoved;

    QSet<QPair<int, int>> getLegalMoves(const std::array<std::array<char, 8>, 8> &chessBoard, QPair<int, int> sCoord, int currTurn);

    QString makeLegalMove(std::array<std::array<char, 8>, 8> &chessBoard, QMap<QPair<int, int>, char> &coordinatePieceMap, QPair<int, int> targetCoord, int &currTurn, bool changeUI);

    QString makeLegalPromotionMove(std::array<std::array<char, 8>, 8> &chessBoard, QMap<QPair<int, int>, char> &coordinatePieceMap, QPair<int, int> targetCoord, int &currTurn, char promotionPiece, QString &move);

    void resetGame(const std::array<std::array<char, 8>, 8> &chessBoard);

private:
    Chess *chess;

    QSet<QPair<int, int>> legalMoves;

    std::array<std::array<char, 8>, 8> board;

    std::vector<std::array<std::array<char, 8>, 8>> prevBoards;

    std::map<std::array<std::array<char, 8>, 8>, int> seenBoards;

    QPair<int, int> sourceCoord;
    int sourceRow;
    int sourceCol;
    char sourcePiece;

    std::array<QPair<int, int>, 2> kingCoords;

    QPair<int, int> kingCoord;
    int kingRow;
    int kingCol;

    int turn;

    std::array<QSet<char>, 2> piecesSet;

    std::array<int, 2> pawnDirections;
    std::array<int, 2> pawnHomeRows;

    QPair<int, int> enPassantCoord;

    int movesSinceLastCaptureOrPawnMove;

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

    char getKingState(const QMap<QPair<int, int>, char> &coordinatePieceMap);

    QString getGameState();

    bool reachedThreefoldRepetition();

    bool reachedFiftyMoveRule();
};

#endif // CHESS_LOGIC_H
