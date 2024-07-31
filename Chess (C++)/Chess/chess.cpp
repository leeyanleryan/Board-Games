#include "chess.h"
#include "ui_chess.h"
#include "QPushButton"

QMap<QPair<int, int>, QPushButton*> buttonMap;
QMap<QPair<int, int>, QString> pieceMap;
int turn;

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    setButtonMap();
    setPieceMap();
    setChessBoard(":/Pieces/Neo/", ":/Board/Brown/", ":/Sound/Default/");
}

Chess::~Chess()
{
    delete ui;
}

void Chess::setButtonMap()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString buttonName = QString("pushButton_%1").arg(row*8 + col+1);
            QPushButton *button = findChild<QPushButton*>(buttonName);
            buttonMap[qMakePair(row, col)] = button;
        }
    }
}

void Chess::setButtonPiece(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    // button->setIconSize(pixmap.rect().size());
    button->setIconSize(QSize(90, 90));
}

void Chess::setButtonBoard(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon ButtonIcon(pixmap);
    button->setStyleSheet("background-image: url(" + imagePath + "); border: 0");
}

void Chess::setPieceMap()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {

        }
    }
}

void Chess::setChessBoard(QString piecesPath, QString boardPath, QString soundPath)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QPushButton *button = buttonMap[{row, col}];
            if ((row+col)%2 == 0)
            {
                setButtonBoard(button, boardPath + "BoardBlack.png");
            }
            else if ((row+col)%2 == 1)
            {
                setButtonBoard(button, boardPath + "BoardWhite.png");
            }
        }
    }
}

