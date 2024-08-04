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
    this->turn = turn;
    piece = board[sourceCoord.first][sourceCoord.second];
    legalMoves = {};

    if (!chess->piecesSet[turn].contains(piece))
    {
        return legalMoves;
    }

    if (piece == "P" || piece == "p")
    {
        legalMoves = {qMakePair(1, 2)};
    }
    else if (piece == "R" || piece == "r")
    {
        getLegalRookMovement();
    }
    else if (piece == "N" || piece == "n")
    {
        getLegalKnightMovement();
    }
    else if (piece == "B" || piece == "b")
    {
        getLegalBishopMovement();
    }
    else if (piece == "Q" || piece == "q")
    {
        legalMoves = {qMakePair(1, 2)};
    }
    else if (piece == "K" || piece == "k")
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

}

void ChessLogic::getLegalKnightMovement()
{
    std::vector<QPair<int, int>> pool = {qMakePair(-2, -1), qMakePair(-2, 1),
                                         qMakePair(-1, -2), qMakePair(-1, 2),
                                         qMakePair( 1, -2), qMakePair( 1, 2),
                                         qMakePair( 2, -1), qMakePair( 2, 1)};

    for (QPair<int, int> coord : pool)
    {
        QPair<int, int> targetCoord = qMakePair(sourceCoord.first + coord.first, sourceCoord.second + coord.second);
        int row = targetCoord.first;
        int col = targetCoord.second;
        if (row < 0 || row > 7 || col < 0 || col > 7)
        {
            continue;
        }

        QString targetPiece = board[row][col];
        if (chess->piecesSet[turn].contains(targetPiece))
        {
            continue;
        }

        legalMoves.insert(targetCoord);
    }
}

void ChessLogic::getLegalBishopMovement()
{
    int row = sourceCoord.first;
    int col = sourceCoord.second;

    // top-left
    for (int i = 0; i < std::min(row, col); i++)
    {
        QPair<int, int> targetCoord = qMakePair(row-i-1, col-i-1);
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
    for (int i = 0; i < std::min(row, 7-col); i++)
    {
        QPair<int, int> targetCoord = qMakePair(row-i-1, col+i+1);
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
    for (int i = 0; i < std::min(7-row, col); i++)
    {
        QPair<int, int> targetCoord = qMakePair(row+i+1, col-i-1);
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
    for (int i = 0; i < std::min(7-row, 7-col); i++)
    {
        QPair<int, int> targetCoord = qMakePair(row+i+1, col+i+1);
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

bool pieceIsPinned()
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
