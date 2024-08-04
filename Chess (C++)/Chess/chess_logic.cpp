#include "chess_logic.h"
#include "chess.h"

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{

}

QSet<QPair<int, int>> ChessLogic::getLegalMoves(std::vector<std::vector<QString>> chessBoard, QPair<int, int> sourceCoord, int turn)
{
    this->board = chessBoard;
    QString piece = board[sourceCoord.first][sourceCoord.second];
    legalMoves = {};

    if (turn == 0)
    {
        if (!chess->whitePiecesSet.contains(piece))
        {
            legalMoves = {};
        }
        else if (piece == "P")
        {
            legalMoves = {qMakePair(1, 2)};
        }
        else if (piece == "R")
        {
            legalMoves = {qMakePair(1, 2)};
        }
        else if (piece == "N")
        {
            legalMoves = {qMakePair(1, 2)};
        }
        else if (piece == "B")
        {
            legalMoves = {qMakePair(1, 2)};
        }
        else if (piece == "Q")
        {
            legalMoves = {qMakePair(1, 2)};
        }
        else if (piece == "K")
        {
            legalMoves = {qMakePair(1, 2)};
        }
    }
    else if (turn == 1)
    {
        if (!chess->blackPiecesSet.contains(piece))
        {
            legalMoves = {};
        }
        else if (piece == "p")
        {
            legalMoves = {qMakePair(1, 1)};
        }
        else if (piece == "r")
        {
            legalMoves = {qMakePair(1, 1)};
        }
        else if (piece == "n")
        {
            legalMoves = {qMakePair(1, 1)};
        }
        else if (piece == "b")
        {
            legalMoves = {qMakePair(1, 1)};
        }
        else if (piece == "q")
        {
            legalMoves = {qMakePair(1, 1)};
        }
        else if (piece == "k")
        {
            legalMoves = {qMakePair(1, 1)};
        }
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

}

void ChessLogic::getLegalBishopMovement()
{

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
