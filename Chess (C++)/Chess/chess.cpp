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
QString backgroundPath;
QString buttonStyleSheet;
QString buttonStyleSheetDisabled;
QString buttonStyleSheetShadow;
int turn;

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    // variable setup
    pieceImagePath = ":/Pieces/Neo/";
    boardImagePath = ":/Board/Brown/";
    chessSoundPath = ":/Sound/Default/";
    backgroundPath = ":/Background/Default/";
    buttonStyleSheet = "QPushButton {background-image: url(" + backgroundPath + "button.png); border: 0; color: white;}"
                       "QPushButton:hover {background-image: url(" + backgroundPath + "buttonHover.png);}"
                       "QPushButton:pressed {background-image: url(" + backgroundPath + "button.png);}";
    buttonStyleSheetDisabled = "QPushButton {background-image: url(" + backgroundPath + "button.png); border: 0; color: grey;}"
                               "QPushButton:hover {background-image: url(" + backgroundPath + "buttonHover.png);}"
                               "QPushButton:pressed {background-image: url(" + backgroundPath + "button.png);}";
    buttonStyleSheetShadow = "background-image: url(" + backgroundPath + "buttonShadow.png)";
    turn = 0;

    // ui setup
    ui->setupUi(this);
    launchSetup();
}

Chess::~Chess()
{
    delete ui;
}

void Chess::launchSetup()
{
    setDefaultBoard();
    setButtonPositionMap();
    setPiecePositionMap();
    setPieceImageMap();
    setChessBoard();
    setMenu();
}

void Chess::setDefaultBoard()
{
    board.push_back({"r","n","b","q","k","b","n","r"});
    board.push_back({"p","p","p","p","p","p","p","p"});
    board.push_back({"-","-","-","-","-","-","-","-"});
    board.push_back({"-","-","-","-","-","-","-","-"});
    board.push_back({"-","-","-","-","-","-","-","-"});
    board.push_back({"-","-","-","-","-","-","-","-"});
    board.push_back({"P","P","P","P","P","P","P","P"});
    board.push_back({"R","N","B","Q","K","B","N","R"});
}

void Chess::setButtonPositionMap()
{
    std::vector<QString> positionAlphabet = {"a","b","c","d","e","f","g","h"};
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString buttonName = QString("%1%2").arg(positionAlphabet[col]).arg(8-row);
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
            if (board[row][col] != "-")
            {
                piecePositionMap[qMakePair(row, col)] = board[row][col];
            }
        }
    }
}

void Chess::setPieceImageMap()
{
    // black
    pieceImageMap["r"] = "RookBlack.png";
    pieceImageMap["n"] = "KnightBlack.png";
    pieceImageMap["b"] = "BishopBlack.png";
    pieceImageMap["q"] = "QueenBlack.png";
    pieceImageMap["k"] = "KingBlack.png";
    pieceImageMap["p"] = "PawnBlack.png";
    // white
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

void Chess::setMenu()
{
    ui->uiMenu->setCurrentIndex(0);

    // background
    ui->centralwidget->setStyleSheet("background-image: url(" + backgroundPath + "background.png); border: 0");
    ui->uiMenu->setStyleSheet("background-image: url(" + backgroundPath + "menu.png); border: 0");

    // text
    ui->txtWelcome->setStyleSheet("color: white");
    ui->txtComputer->setStyleSheet("color: white");

    // buttons
    ui->buttonPlayComputer->setStyleSheet(buttonStyleSheet);
    ui->buttonPlayComputerShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonPlayFriend->setStyleSheet(buttonStyleSheet);
    ui->buttonPlayFriendShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonSettings->setStyleSheet(buttonStyleSheet);
    ui->buttonSettingsShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonExit->setStyleSheet(buttonStyleSheet);
    ui->buttonExitShadow->setStyleSheet(buttonStyleSheetShadow);

    ui->buttonComputerNext->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerNextShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonComputerBack->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerBackShadow->setStyleSheet(buttonStyleSheetShadow);
}

void Chess::on_buttonPlayComputer_clicked()
{
    ui->buttonComputerNext->setEnabled(false);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheetDisabled);

    ui->uiMenu->setCurrentIndex(1);
}

void Chess::on_buttonComputerNext_clicked()
{
    ui->uiMenu->setCurrentIndex(4);
}


void Chess::on_buttonComputerBack_clicked()
{
    ui->uiMenu->setCurrentIndex(0);
}

void Chess::on_buttonGoesFirstBack_clicked()
{
    ui->uiMenu->setCurrentIndex(1);
}



