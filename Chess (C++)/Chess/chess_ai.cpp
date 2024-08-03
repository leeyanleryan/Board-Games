#include "chess_ai.h"
#include "chess.h"

ChessAI::ChessAI(Chess *chessInstance)
    : chess(chessInstance)
{

}

void ChessAI::setDifficulty(int computerDifficulty)
{
    difficulty = computerDifficulty;
}

void ChessAI::makeMove()
{

}
