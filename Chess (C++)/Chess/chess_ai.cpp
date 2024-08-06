#include "chess_ai.h"
#include "chess.h"

ChessAI::ChessAI(Chess *chessInstance)
    : chess(chessInstance)
{

}

void ChessAI::makeMove()
{

}

char ChessAI::promotePawn()
{
    return chess->logic->queenPieces[turn];
}
