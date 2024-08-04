#include "chess_logic.h"
#include "chess.h"
#include <algorithm>

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{

}

QSet<QPair<int, int>> ChessLogic::getLegalMoves(std::vector<std::vector<QString>> chessBoard, QPair<int, int> sourceCoord, int turn)
{
    board = chessBoard;
    this->sourceCoord = sourceCoord;
    sourceRow = sourceCoord.first;
    sourceCol = sourceCoord.second;
    sourcePiece = board[sourceRow][sourceCol];
    this->turn = turn;
    legalMoves = {};

    if (!chess->piecesSet[turn].contains(sourcePiece))
    {
        return legalMoves;
    }

    if (sourcePiece == "P" || sourcePiece == "p")
    {
        legalMoves = {qMakePair(1, 2)};
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
        legalMoves = {qMakePair(1, 2)};
    }

    return legalMoves;
}

void ChessLogic::getLegalPawnMovement()
{

}

void ChessLogic::getLegalRookMovement()
{
    // up
    for (int i = 0; i < sourceRow; i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow-i-1, sourceCol);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // down
    for (int i = 0; i < 7-sourceRow; i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow+i+1, sourceCol);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // left
    for (int i = 0; i < sourceCol; i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow, sourceCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // right
    for (int i = 0; i < 7-sourceCol; i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow, sourceCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
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
        legalMoves.insert(targetCoord);
    }
}

void ChessLogic::getLegalBishopMovement()
{
    // top-left
    for (int i = 0; i < std::min(sourceRow, sourceCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow-i-1, sourceCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // top-right
    for (int i = 0; i < std::min(sourceRow, 7-sourceCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow-i-1, sourceCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // bottom-left
    for (int i = 0; i < std::min(7-sourceRow, sourceCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow+i+1, sourceCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
    // bottom-right
    for (int i = 0; i < std::min(7-sourceRow, 7-sourceCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(sourceRow+i+1, sourceCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            break;
        }
        else if (chess->piecesSet[1-turn].contains(targetPiece))
        {
            legalMoves.insert(targetCoord);
            break;
        }
        legalMoves.insert(targetCoord);
    }
}

void ChessLogic::getLegalQueenMovement()
{
    getLegalRookMovement();
    getLegalBishopMovement();
}

void ChessLogic::getLegalKingMovement()
{

}

std::vector<QPair<int, int>> findEnemyPawn()
{
    return {};
}

std::vector<QPair<int, int>> findEnemyRook()
{
    return {};
}

std::vector<QPair<int, int>> findEnemyKnight()
{
    return {};
}

std::vector<QPair<int, int>> findEnemyBishop()
{
    return {};
}

std::vector<QPair<int, int>> findEnemyQueen()
{
    return {};
}

std::vector<QPair<int, int>> findEnemyKing()
{
    return {};
}

bool sourcePieceIsPinned()
{
    return false;
}

bool kingIsChecked()
{
    return false;
}

bool kingIsMated()
{
    return false;
}
