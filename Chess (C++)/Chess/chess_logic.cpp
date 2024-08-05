#include "chess_logic.h"
#include "chess.h"
#include <algorithm>

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{
    kingCoords = {qMakePair(7, 4), qMakePair(0, 4)};
    kingCanCastle = {true, true};
}

QSet<QPair<int, int>> ChessLogic::getLegalMoves(std::vector<std::vector<QString>> chessBoard, QPair<int, int> sourceCoord, int turn)
{
    board = chessBoard;
    this->sourceCoord = sourceCoord;
    sourceRow = sourceCoord.first;
    sourceCol = sourceCoord.second;
    sourcePiece = board[sourceRow][sourceCol];
    this->turn = turn;
    //isPinned = pieceIsPinned();
    //isChecked = kingIsChecked();

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
    std::vector<int> direction = {-1, 1};
    QPair<int, int> forwardOnce = qMakePair(sourceRow+direction[turn], sourceCol);
    QPair<int, int> forwardTwice = qMakePair(sourceRow+2*direction[turn], sourceCol);
    QPair<int, int> diagonalLeft = qMakePair(sourceRow+direction[turn], sourceCol-1);
    QPair<int, int> diagonalRight = qMakePair(sourceRow+direction[turn], sourceCol+1);
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
        legalMoves.insert(targetCoord);
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
        board[targetRow][targetCol] = sourcePiece;
        board[sourceRow][sourceCol] = "-";
        kingCoords[turn] = qMakePair(targetRow, targetCol);
        if (!kingIsChecked())
        {
            legalMoves.insert(targetCoord);
        }
        board[targetRow][targetCol] = targetPiece;
        board[sourceRow][sourceCol] = sourcePiece;
        kingCoords[turn] = qMakePair(sourceRow, sourceCol);
    }
}

std::vector<QPair<int, int>> ChessLogic::findEnemyPawn()
{
    std::vector<QPair<int, int>> enemyPawnPool = {};
    std::vector<QString> pawnPieces = {"P", "p"};
    std::vector<int> direction = {-1, 1};
    QPair<int, int> kingCoord = kingCoords[turn];
    int kingRow = kingCoord.first;
    int kingCol = kingCoord.second;

    // find if there is enemy pawn at top/bottom left
    if (board[kingRow + direction[turn]][kingCol-1] == pawnPieces[1-turn])
    {
        enemyPawnPool.push_back(qMakePair(kingRow + direction[turn], kingCol-1));
    }
    // find if there is enemy pawn at top/bottom right
    if (board[kingRow + direction[turn]][kingCol+1] == pawnPieces[1-turn])
    {
        enemyPawnPool.push_back(qMakePair(kingRow + direction[turn], kingCol+1));
    }

    return enemyPawnPool;
}

bool ChessLogic::hitPiece(int targetRow, int targetCol)
{
    // QPair<int, int> targetCoord = qMakePair(kingRow-i-1, kingCol);
    // QString targetPiece = board[targetCoord.first][targetCoord.second];
    // if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
    // {
    //     enemyPiecePool.push_back(targetCoord);
    //     return true;
    // }
    // else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
    // {
    //     return true;
    // }
    // return false;
    return false;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyRook()
{
    std::vector<QPair<int, int>> enemyRookPool = {};
    std::vector<QString> rookPieces = {"R", "r"};
    std::vector<QString> queenPieces = {"Q", "q"};
    QPair<int, int> kingCoord = kingCoords[turn];
    int kingRow = kingCoord.first;
    int kingCol = kingCoord.second;

    // up
    for (int i = 0; i < kingRow; i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow-i-1, kingCol);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyRookPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // down
    for (int i = 0; i < 7-kingRow; i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow+i+1, kingCol);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyRookPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // left
    for (int i = 0; i < kingCol; i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow, kingCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyRookPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // right
    for (int i = 0; i < 7-kingCol; i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow, kingCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyRookPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }

    return enemyRookPool;
}

std::vector<QPair<int, int>> ChessLogic::findEnemyKnight()
{
    std::vector<QPair<int, int>> enemyKnightPool = {};
    std::vector<QString> knightPieces = {"N", "n"};
    QPair<int, int> kingCoord = kingCoords[turn];
    int kingRow = kingCoord.first;
    int kingCol = kingCoord.second;

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

std::vector<QPair<int, int>> ChessLogic::findEnemyBishop()
{
    std::vector<QPair<int, int>> enemyBishopPool = {};
    std::vector<QString> bishopPieces = {"B", "b"};
    std::vector<QString> queenPieces = {"Q", "q"};
    QPair<int, int> kingCoord = kingCoords[turn];
    int kingRow = kingCoord.first;
    int kingCol = kingCoord.second;

    // top-left
    for (int i = 0; i < std::min(kingRow, kingCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow-i-1, kingCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyBishopPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // top-right
    for (int i = 0; i < std::min(kingRow, 7-kingCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow-i-1, kingCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyBishopPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // bottom-left
    for (int i = 0; i < std::min(7-kingRow, kingCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow+i+1, kingCol-i-1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyBishopPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
        {
            break;
        }
    }
    // bottom-right
    for (int i = 0; i < std::min(7-kingRow, 7-kingCol); i++)
    {
        QPair<int, int> targetCoord = qMakePair(kingRow+i+1, kingCol+i+1);
        QString targetPiece = board[targetCoord.first][targetCoord.second];
        if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
        {
            enemyBishopPool.push_back(targetCoord);
            break;
        }
        else if (chess->piecesSet[turn].contains(targetPiece) || chess->piecesSet[1-turn].contains(targetPiece))
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

std::vector<QPair<int, int>> ChessLogic::findEnemyKing()
{
    return {};
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
