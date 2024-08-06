#include "chess_logic.h"
#include "chess.h"
#include <algorithm>

ChessLogic::ChessLogic(Chess *chessInstance)
    : chess(chessInstance)
{
    kingCoords = {};
    kingHasMoved = {};
    rookHasMoved = {};

    piecesSet[0] = {'R', 'N', 'B', 'Q', 'K', 'P'};
    piecesSet[1] = {'r', 'n', 'b', 'q', 'k', 'p'};

    pawnPieces = {'P', 'p'};
    rookPieces = {'R', 'r'};
    knightPieces = {'N', 'n'};
    bishopPieces = {'B', 'b'};
    queenPieces = {'Q', 'q'};
    kingPieces = {'K', 'k'};

    pawnDirections = {-1, 1};
    pawnHomeRows = {6, 1};

    enPassantCoord = qMakePair(-1, -1);
}

QSet<QPair<int, int>> ChessLogic::getLegalMoves(const std::array<std::array<char, 8>, 8> &chessBoard, QPair<int, int> sCoord, int currTurn)
{
    board = chessBoard;
    sourceCoord = sCoord;
    sourceRow = sourceCoord.first;
    sourceCol = sourceCoord.second;
    sourcePiece = board[sourceRow][sourceCol];
    kingCoord = kingCoords[currTurn];
    kingRow = kingCoord.first;
    kingCol = kingCoord.second;
    turn = currTurn;

    if (!piecesSet[turn].contains(sourcePiece))
    {
        return {};
    }

    legalMoves = {};

    if (sourcePiece == 'P' || sourcePiece == 'p')
    {
        getLegalPawnMovement();
    }
    else if (sourcePiece == 'R' || sourcePiece == 'r')
    {
        getLegalRookMovement();
    }
    else if (sourcePiece == 'N' || sourcePiece == 'n')
    {
        getLegalKnightMovement();
    }
    else if (sourcePiece == 'B' || sourcePiece == 'b')
    {
        getLegalBishopMovement();
    }
    else if (sourcePiece == 'Q' || sourcePiece == 'q')
    {
        getLegalQueenMovement();
    }
    else if (sourcePiece == 'K' || sourcePiece == 'k')
    {
        getLegalKingMovement();
    }

    return legalMoves;
}

QString ChessLogic::makeLegalMove(std::array<std::array<char, 8>, 8> &chessBoard, QPair<int, int> targetCoord, int &currTurn, bool changeUI)
{
    int targetRow = targetCoord.first;
    int targetCol = targetCoord.second;
    char targetPiece = chessBoard[targetRow][targetCol];

    QString move = "";

    enPassantCoord = qMakePair(-1, -1);

    if (sourcePiece == 'P' || sourcePiece == 'p')
    {
        // moved twice
        if (abs(targetRow - sourceRow) == 2)
        {
            enPassantCoord = targetCoord;
        }
        if (targetCol != sourceCol)
        {
            move += chess->coordinateNotationMap[sourceCoord][0];
        }
        // en passant
        if (targetPiece == '-' && targetCol != sourceCol)
        {
            move += "x";
            chessBoard[targetRow + pawnDirections[1-turn]][targetCol] = '-';
            if (changeUI)
            {
                chess->coordinateButtonMap[qMakePair(targetRow + pawnDirections[1-turn], targetCol)]->setIcon(QIcon());
            }
        }
        // promote to piece
    }
    else if (sourcePiece == 'K' || sourcePiece == 'k')
    {
        move += sourcePiece;
        kingCoords[turn] = targetCoord;
        kingHasMoved[turn] = true;
    }
    else if (sourcePiece == 'R' || sourcePiece == 'r')
    {
        move += sourcePiece;
        rookHasMoved[turn] = true;
    }
    else
    {
        move += sourcePiece;
    }

    if (targetPiece != '-')
    {
        move += "x";
    }

    move += chess->coordinateNotationMap[targetCoord];

    chessBoard[targetRow][targetCol] = chessBoard[sourceRow][sourceCol];
    chessBoard[sourceRow][sourceCol] = '-';
    currTurn = 1 - currTurn;

    return move;
}

void ChessLogic::setKingCoords(const std::array<std::array<char, 8>, 8> &chessBoard)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (chessBoard[i][j] == 'K')
            {
                kingCoords[0] = qMakePair(i, j);
            }
            if (chessBoard[i][j] == 'k')
            {
                kingCoords[1] = qMakePair(i, j);
            }
        }
    }
}

bool ChessLogic::getLegalMovesHelper(int targetRow, int targetCol)
{
    QPair<int, int> targetCoord = qMakePair(targetRow, targetCol);
    char targetPiece = board[targetRow][targetCol];
    if (piecesSet[turn].contains(targetPiece))
    {
        return true;
    }
    else if (piecesSet[1-turn].contains(targetPiece))
    {
        addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
        return true;
    }
    addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
    return false;
}

void ChessLogic::addLegalMoveIfNotPinned(QPair<int, int> targetCoord, int targetRow, int targetCol, char targetPiece)
{
    board[targetRow][targetCol] = sourcePiece;
    board[sourceRow][sourceCol] = '-';
    if (!kingIsChecked())
    {
        qDebug() << "LOL";
        legalMoves.insert(targetCoord);
    }
    board[targetRow][targetCol] = targetPiece;
    board[sourceRow][sourceCol] = sourcePiece;
}

void ChessLogic::getLegalPawnMovement()
{
    QPair<int, int> forwardOnce = qMakePair(sourceRow+pawnDirections[turn], sourceCol);
    QPair<int, int> forwardTwice = qMakePair(sourceRow+2*pawnDirections[turn], sourceCol);
    QPair<int, int> diagonalLeft = qMakePair(sourceRow+pawnDirections[turn], sourceCol-1);
    QPair<int, int> diagonalRight = qMakePair(sourceRow+pawnDirections[turn], sourceCol+1);
    QPair<int, int> straightLeft = qMakePair(sourceRow, sourceCol-1);
    QPair<int, int> straightRight = qMakePair(sourceRow, sourceCol+1);

    // Can move forward if no piece in front
    if (forwardOnce.first >= 0 && forwardOnce.first <= 7 && board[forwardOnce.first][forwardOnce.second] == '-')
    {
        addLegalMoveIfNotPinned(forwardOnce, forwardOnce.first, forwardOnce.second, board[forwardOnce.first][forwardOnce.second]);
    }
    // Home square can move one extra
    if (sourceRow == pawnHomeRows[turn] && board[forwardTwice.first][forwardTwice.second] == '-')
    {
        qDebug() << sourceCoord;
        qDebug() << forwardTwice;
        addLegalMoveIfNotPinned(forwardTwice, forwardTwice.first, forwardTwice.second, board[forwardTwice.first][forwardTwice.second]);
    }
    // Capture diagonally left
    if (diagonalLeft.second >= 0 && piecesSet[1-turn].contains(board[diagonalLeft.first][diagonalLeft.second]))
    {
        addLegalMoveIfNotPinned(diagonalLeft, diagonalLeft.first, diagonalLeft.second, board[diagonalLeft.first][diagonalLeft.second]);
    }
    // Capture diagonally right
    if (diagonalRight.second <= 7 && piecesSet[1-turn].contains(board[diagonalRight.first][diagonalRight.second]))
    {
        addLegalMoveIfNotPinned(diagonalRight, diagonalRight.first, diagonalRight.second, board[diagonalRight.first][diagonalRight.second]);
    }
    // En passant left
    if (straightLeft.second >= 0 && board[straightLeft.first][straightLeft.second] == pawnPieces[1-turn] && straightLeft == enPassantCoord)
    {
        board[straightLeft.first][straightLeft.second] = '-';
        addLegalMoveIfNotPinned(diagonalLeft, diagonalLeft.first, diagonalLeft.second, board[diagonalLeft.first][diagonalLeft.second]);
        board[straightLeft.first][straightLeft.second] = pawnPieces[1-turn];
    }
    // En passant right
    if (straightRight.second <= 7 && board[straightRight.first][straightRight.second] == pawnPieces[1-turn] && straightRight == enPassantCoord)
    {
        board[straightRight.first][straightRight.second] = '-';
        addLegalMoveIfNotPinned(diagonalRight, diagonalRight.first, diagonalRight.second, board[diagonalRight.first][diagonalRight.second]);
        board[straightRight.first][straightRight.second] = pawnPieces[1-turn];
    }
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
        char targetPiece = board[targetRow][targetCol];
        if (piecesSet[turn].contains(targetPiece))
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

        char targetPiece = board[targetRow][targetCol];
        if (piecesSet[turn].contains(targetPiece))
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

        kingCoord = qMakePair(targetRow, targetCol);
        kingRow = targetRow;
        kingCol = targetCol;
        addLegalMoveIfNotPinned(targetCoord, targetRow, targetCol, targetPiece);
        kingCoord = qMakePair(sourceRow, sourceCol);
        kingRow = sourceRow;
        kingCol = sourceCol;
    }

    if (kingHasMoved[turn] || rookHasMoved[turn])
    {
        return;
    }

    QPair<int, int> leftCastle = qMakePair(0, -2);
    QPair<int, int> rightCastle = qMakePair(0, 2);


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
    char targetPiece = board[targetCoord.first][targetCoord.second];
    qDebug() << "HERE IT IS" << targetCoord;
    qDebug() << targetPiece;
    if (targetPiece == rookPieces[1-turn] || targetPiece == queenPieces[1-turn])
    {
        enemyRookPool.push_back(targetCoord);
        return true;
    }
    else if (piecesSet[turn].contains(targetPiece) || piecesSet[1-turn].contains(targetPiece))
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
        char targetPiece = board[targetRow][targetCol];
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
    char targetPiece = board[targetCoord.first][targetCoord.second];
    if (targetPiece == bishopPieces[1-turn] || targetPiece == queenPieces[1-turn])
    {
        enemyBishopPool.push_back(targetCoord);
        return true;
    }
    else if (piecesSet[turn].contains(targetPiece) || piecesSet[1-turn].contains(targetPiece))
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

    qDebug() << enemyQueenPool;

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
