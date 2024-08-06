#include "chess_logic.h"
#include "chess.h"
#include <algorithm>

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{
    kingCoords = {qMakePair(5, 6), qMakePair(2, 6)};
    kingHasMoved = {false, false};

    pawnPieces = {"P", "p"};
    rookPieces = {"R", "r"};
    knightPieces = {"N", "n"};
    bishopPieces = {"B", "b"};
    queenPieces = {"Q", "q"};
    kingPieces = {"K", "k"};

    pawnDirections = {-1, 1};
}

QSet<QPair<int, int>> ChessLogic::getLegalMoves(std::vector<std::vector<QString>> chessBoard, QPair<int, int> sourceCoord, int currTurn)
{
    board = chessBoard;
    this->sourceCoord = sourceCoord;
    sourceRow = sourceCoord.first;
    sourceCol = sourceCoord.second;
    sourcePiece = board[sourceRow][sourceCol];
    kingCoord = kingCoords[currTurn];
    kingRow = kingCoord.first;
    kingCol = kingCoord.second;
    turn = currTurn;

    if (!chess->piecesSet[turn].contains(sourcePiece))
    {
        return {};
    }

    legalMoves = {};

    if (sourcePiece == "P" || sourcePiece == "p")
    {
        getLegalPawnMovement();
    }
    else if (sourcePiece == "R" || sourcePiece == "r")
    {
        getLegalRookMovement();
    }
    else if (sourcePiece == "N" || sourcePiece == "n")
    {
        getLegalKnightMovement();
    }
    else if (sourcePiece == "B" || sourcePiece == "b")
    {
        getLegalBishopMovement();
    }
    else if (sourcePiece == "Q" || sourcePiece == "q")
    {
        getLegalQueenMovement();
    }
    else if (sourcePiece == "K" || sourcePiece == "k")
    {
        getLegalKingMovement();
    }

    return legalMoves;
}

void ChessLogic::getLegalPawnMovement()
{
    std::vector<int> homeRow = {6, 1};
    QPair<int, int> forwardOnce = qMakePair(sourceRow+pawnDirections[turn], sourceCol);
    QPair<int, int> forwardTwice = qMakePair(sourceRow+2*pawnDirections[turn], sourceCol);
    QPair<int, int> diagonalLeft = qMakePair(sourceRow+pawnDirections[turn], sourceCol-1);
    QPair<int, int> diagonalRight = qMakePair(sourceRow+pawnDirections[turn], sourceCol+1);

    // Can move forward if no piece in front
    if (forwardOnce.first >= 0 && forwardOnce.first <= 7 && board[forwardOnce.first][forwardOnce.second] == "-")
    {
        legalMoves.insert(forwardOnce);
    }
    // Home square can move one extra
    if (sourceRow == homeRow[turn] && board[forwardTwice.first][forwardTwice.second] == "-")
    {
        legalMoves.insert(forwardTwice);
    }
    // Capture diagonally left
    if (diagonalLeft.second >= 0 && chess->piecesSet[1-turn].contains(board[diagonalLeft.first][diagonalLeft.second]))
    {
        legalMoves.insert(diagonalLeft);
    }
    // Capture diagonally right
    if (diagonalRight.second <= 7 && chess->piecesSet[1-turn].contains(board[diagonalRight.first][diagonalRight.second]))
    {
        legalMoves.insert(diagonalRight);
    }
    // En passant left

    // En passant right

}

bool ChessLogic::getLegalMovesHelper(int targetRow, int targetCol)
{
    QPair<int, int> targetCoord = qMakePair(targetRow, targetCol);
    QString targetPiece = board[targetRow][targetCol];
    if (chess->piecesSet[turn].contains(targetPiece))
    {
        return true;
    }
    else if (chess->piecesSet[1-turn].contains(targetPiece))
    {
        addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
        return true;
    }
    addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
    return false;
}

void ChessLogic::addLegalMoveIfNotPinned(QPair<int, int> targetCoord, int targetRow, int targetCol, QString targetPiece)
{
    board[targetRow][targetCol] = sourcePiece;
    board[sourceRow][sourceCol] = "-";
    if (!kingIsChecked())
    {
        legalMoves.insert(targetCoord);
    }
    board[targetRow][targetCol] = targetPiece;
    board[sourceRow][sourceCol] = sourcePiece;
}

void ChessLogic::getLegalRookMovement()
{
    // up
    for (int i = 0; i < sourceRow; i++)
    {
        if (getLegalMovesHelper(sourceRow-i-1, sourceCol))
        {
            break;
        }
    }
    // down
    for (int i = 0; i < 7-sourceRow; i++)
    {
        if (getLegalMovesHelper(sourceRow+i+1, sourceCol))
        {
            break;
        }
    }
    // left
    for (int i = 0; i < sourceCol; i++)
    {
        if (getLegalMovesHelper(sourceRow, sourceCol-i-1))
        {
            break;
        }
    }
    // right
    for (int i = 0; i < 7-sourceCol; i++)
    {
        if (getLegalMovesHelper(sourceRow, sourceCol+i+1))
        {
            break;
        }
    }
}

void ChessLogic::getLegalKnightMovement()
{
    std::vector<QPair<int, int>> pool = {qMakePair(-2, -1), qMakePair(-2, 1),
                                         qMakePair(-1, -2), qMakePair(-1, 2),
                                         qMakePair( 1, -2), qMakePair( 1, 2),
                                         qMakePair( 2, -1), qMakePair( 2, 1)};

    for (QPair<int, int> coord : pool)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow + coord.first, sourceCol + coord.second);
        int targetRow = targetCoord.first;
        int targetCol = targetCoord.second;
        if (targetRow < 0 || targetRow > 7 || targetCol < 0 || targetCol > 7)
        {
            continue;
        }
        QString targetPiece = board[targetRow][targetCol];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            continue;
        }
        addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
    }
}

void ChessLogic::getLegalBishopMovement()
{
    // top-left
    for (int i = 0; i < std::min(sourceRow, sourceCol); i++)
    {
        if (getLegalMovesHelper(sourceRow-i-1, sourceCol-i-1))
        {
            break;
        }
    }
    // top-right
    for (int i = 0; i < std::min(sourceRow, 7-sourceCol); i++)
    {
        if (getLegalMovesHelper(sourceRow-i-1, sourceCol+i+1))
        {
            break;
        }
    }
    // bottom-left
    for (int i = 0; i < std::min(7-sourceRow, sourceCol); i++)
    {
        if (getLegalMovesHelper(sourceRow+i+1, sourceCol-i-1))
        {
            break;
        }
    }
    // bottom-right
    for (int i = 0; i < std::min(7-sourceRow, 7-sourceCol); i++)
    {
        if (getLegalMovesHelper(sourceRow+i+1, sourceCol+i+1))
        {
            break;
        }
    }
}

void ChessLogic::getLegalQueenMovement()
{
    getLegalRookMovement();
    getLegalBishopMovement();
}

void ChessLogic::getLegalKingMovement()
{
    std::vector<QPair<int, int>> pool = {qMakePair(-1, -1), qMakePair(-1, 0), qMakePair(-1, 1),
                                         qMakePair( 0, -1),                   qMakePair( 0, 1),
                                         qMakePair( 1, -1), qMakePair( 1, 0), qMakePair( 1, 1)};

    for (QPair<int, int> coord : pool)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow + coord.first, sourceCol + coord.second);
        int targetRow = targetCoord.first;
        int targetCol = targetCoord.second;
        if (targetRow < 0 || targetRow > 7 || targetCol < 0 || targetCol > 7)
        {
            continue;
        }
        QString targetPiece = board[targetRow][targetCol];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            continue;
        }
        QPair<int, int> enemyKingCoord = kingCoords[1-turn];
        int kingRowDiff = enemyKingCoord.first - targetRow;
        int kingColDiff = enemyKingCoord.second - targetCol;
        if (kingRowDiff >= -1 && kingRowDiff <= 1 && kingColDiff >= -1 && kingColDiff <= 1)
        {
            continue;
        }
        board[targetRow][targetCol] = sourcePiece;
        board[sourceRow][sourceCol] = "-";
        kingCoord = qMakePair(targetRow, targetCol);
        kingRow = targetRow;
        kingCol = targetCol;
        if (!kingIsChecked())
        {
            legalMoves.insert(targetCoord);
        }
        board[targetRow][targetCol] = targetPiece;
        board[sourceRow][sourceCol] = sourcePiece;
        kingCoord = qMakePair(sourceRow, sourceCol);
        kingRow = sourceRow;
        kingCol = sourceCol;
    }
}

std::vector<QPair<int, int>> ChessLogic::findEnemyPawn()
{
    std::vector<QPair<int, int>> enemyPawnPool = {};

    // diagonal left
    if (kingCol-1 >= 0 && board[kingRow + pawnDirections[turn]][kingCol-1] == pawnPieces[1-turn])
    {
        enemyPawnPool.push_back(qMakePair(kingRow + pawnDirections[turn], kingCol-1));
    }
    // diagonal right
    if (kingCol+1 <= 7 && board[kingRow + pawnDirections[turn]][kingCol+1] == pawnPieces[1-turn])
    {
        enemyPawnPool.push_back(qMakePair(kingRow + pawnDirections[turn], kingCol+1));
    }

    return enemyPawnPool;
}

bool ChessLogic::findEnemyRookHelper(std::vector<QPair<int, int>> &enemyRookPool, int targetRow, int targetCol)
{
    QPair<int, int> targetCoord = qMakePair(targetRow, targetCol);
    QString targetPiece = board[targetCoord.first][targetCoord.second];
    if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
    {
        enemyRookPool.push_back(targetCoord);
        return true;
    }
    else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
    {
        return true;
    }
    return false;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyRook()
{
    std::vector<QPair<int, int>> enemyRookPool = {};

    // up
    for (int i = 0; i < kingRow; i++)
    {
        if (findEnemyRookHelper(enemyRookPool, kingRow-i-1, kingCol))
        {
            break;
        }
    }
    // down
    for (int i = 0; i < 7-kingRow; i++)
    {
        if (findEnemyRookHelper(enemyRookPool, kingRow+i+1, kingCol))
        {
            break;
        }
    }
    // left
    for (int i = 0; i < kingCol; i++)
    {
        if (findEnemyRookHelper(enemyRookPool, kingRow, kingCol-i-1))
        {
            break;
        }
    }
    // right
    for (int i = 0; i < 7-kingCol; i++)
    {
        if (findEnemyRookHelper(enemyRookPool, kingRow, kingCol+i+1))
        {
            break;
        }
    }

    return enemyRookPool;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyKnight()
{
    std::vector<QPair<int, int>> enemyKnightPool = {};
    std::vector<QPair<int, int>> pool = {qMakePair(-2, -1), qMakePair(-2, 1),
                                         qMakePair(-1, -2), qMakePair(-1, 2),
                                         qMakePair( 1, -2), qMakePair( 1, 2),
                                         qMakePair( 2, -1), qMakePair( 2, 1)};

    for (QPair<int, int> coord : pool)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow + coord.first, kingCol + coord.second);
        int targetRow = targetCoord.first;
        int targetCol = targetCoord.second;
        if (targetRow < 0 || targetRow > 7 || targetCol < 0 || targetCol > 7)
        {
            continue;
        }
        QString targetPiece = board[targetRow][targetCol];
        if (targetPiece == knightPieces[1-turn])
        {
            enemyKnightPool.push_back(targetCoord);
        }
    }

    return enemyKnightPool;
}

bool ChessLogic::findEnemyBishopHelper(std::vector<QPair<int, int>> &enemyBishopPool, int targetRow, int targetCol)
{
    QPair<int, int> targetCoord = qMakePair(targetRow, targetCol);
    QString targetPiece = board[targetCoord.first][targetCoord.second];
    if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
    {
        enemyBishopPool.push_back(targetCoord);
        return true;
    }
    else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
    {
        return true;
    }
    return false;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyBishop()
{
    std::vector<QPair<int, int>> enemyBishopPool = {};

    // top-left
    for (int i = 0; i < std::min(kingRow, kingCol); i++)
    {
        if (findEnemyBishopHelper(enemyBishopPool, kingRow-i-1, kingCol-i-1))
        {
            break;
        }
    }
    // top-right
    for (int i = 0; i < std::min(kingRow, 7-kingCol); i++)
    {
        if (findEnemyBishopHelper(enemyBishopPool, kingRow-i-1, kingCol+i+1))
        {
            break;
        }
    }
    // bottom-left
    for (int i = 0; i < std::min(7-kingRow, kingCol); i++)
    {
        if (findEnemyBishopHelper(enemyBishopPool, kingRow+i+1, kingCol-i-1))
        {
            break;
        }
    }
    // bottom-right
    for (int i = 0; i < std::min(7-kingRow, 7-kingCol); i++)
    {
        if (findEnemyBishopHelper(enemyBishopPool, kingRow+i+1, kingCol+i+1))
        {
            break;
        }
    }

    return enemyBishopPool;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyQueen()
{
    std::vector<QPair<int, int>> enemyQueenPool = {};

    for (QPair<int, int> enemyRook : findEnemyRook())
    {
        enemyQueenPool.push_back(enemyRook);
    }
    for (QPair<int, int> enemyBishop: findEnemyBishop())
    {
        enemyQueenPool.push_back(enemyBishop);
    }

    return enemyQueenPool;
}

bool ChessLogic::kingIsChecked()
{
    return (findEnemyPawn().size()   > 0 ||
            findEnemyKnight().size() > 0 ||
            findEnemyQueen().size()  > 0);
}

bool ChessLogic::kingIsMated()
{
    return false;
}
