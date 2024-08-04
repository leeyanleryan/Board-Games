#include "chess_logic.h"
#include "chess.h"

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{

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
