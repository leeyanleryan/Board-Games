#include "chess.h"
#include "ui_chess.h"
#include "QPushButton"

QMap<QPair<int, int>, QPushButton*> buttonPositionMap;
QMap<QPair<int, int>, QString> piecePositionMap;
QMap<QString, QString> pieceImageMap;
std::vector<std::vector<QString>> board;
QString pieceImagePath;
QString boardImagePath;
QString chessSoundPath;
int turn;

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    // variable setup
    pieceImagePath = ":/Pieces/Neo/";
    boardImagePath = ":/Board/Brown/";
    chessSoundPath = ":/Sound/Default/";

    // ui setup
    ui->setupUi(this);
    setDefaultBoard();
    setButtonPositionMap();
    setPiecePositionMap();
    setPieceImageMap();
    setChessBoard();
}

Chess::~Chess()
{
    delete ui;
}

void Chess::setDefaultBoard()
{
    board.push_back({"r", "n", "b", "q", "k", "b", "n", "r"});
    board.push_back({"p", "p", "p", "p", "p", "p", "p", "p"});
    for (int i = 0; i < 4; i++)
    {
        board.push_back({"-", "-", "-", "-", "-", "-", "-", "-"});
    }
    board.push_back({"P", "P", "P", "P", "P", "P", "P", "P"});
    board.push_back({"R", "N", "B", "Q", "K", "B", "N", "R"});
}

void Chess::setButtonPositionMap()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString buttonName = QString("pushButton_%1").arg(row*8 + col+1);
            QPushButton *button = findChild<QPushButton*>(buttonName);
            buttonPositionMap[qMakePair(row, col)] = button;
        }
    }
}

void Chess::setPiecePositionMap()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col] == "-")
            {
                continue;
            }
            piecePositionMap[qMakePair(row, col)] = board[row][col];
        }
    }
}

void Chess::setPieceImageMap()
{
    pieceImageMap["r"] = "RookBlack.png";
    pieceImageMap["n"] = "KnightBlack.png";
    pieceImageMap["b"] = "BishopBlack.png";
    pieceImageMap["q"] = "QueenBlack.png";
    pieceImageMap["k"] = "KingBlack.png";
    pieceImageMap["p"] = "PawnBlack.png";

    pieceImageMap["R"] = "RookWhite.png";
    pieceImageMap["N"] = "KnightWhite.png";
    pieceImageMap["B"] = "BishopWhite.png";
    pieceImageMap["Q"] = "QueenWhite.png";
    pieceImageMap["K"] = "KingWhite.png";
    pieceImageMap["P"] = "PawnWhite.png";
}

void Chess::setButtonPiece(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(QSize(90, 90));
}

void Chess::setButtonBoard(QPushButton *button, const QString &imagePath)
{
    button->setStyleSheet("background-image: url(" + imagePath + "); border: 0");
}

void Chess::setChessBoard()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QPushButton *button = buttonPositionMap[{row, col}];
            if ((row+col)%2 == 0)
            {
                setButtonBoard(button, boardImagePath + "BoardWhite.png");
            }
            else if ((row+col)%2 == 1)
            {
                setButtonBoard(button, boardImagePath + "BoardBlack.png");
            }
            if (piecePositionMap.contains(qMakePair(row, col)))
            {
                setButtonPiece(button, pieceImagePath + pieceImageMap[piecePositionMap[qMakePair(row, col)]]);
            }
        }
    }
}

