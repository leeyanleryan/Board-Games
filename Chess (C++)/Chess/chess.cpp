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
QString buttonStyleSheetDifficulty;
QString buttonStyleSheetDifficultySelected;
QString buttonStyleSheetDisabled;
QString buttonStyleSheetShadow;
QString buttonStyleSheetDifficultyShadow;
bool chosenFirst;
bool alternateTurns;
int turn;
int computerDifficulty;

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
    buttonStyleSheetDifficulty = "QPushButton {background-image: url(" + backgroundPath + "buttonDifficulty.png); border: 0; color: white;}"
                                 "QPushButton:hover {background-image: url(" + backgroundPath + "buttonDifficultyHover.png);}"
                                 "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonDifficultySelected.png);}";
    buttonStyleSheetDifficultySelected = "QPushButton {background-image: url(" + backgroundPath + "buttonDifficultySelected.png); border: 0; color: white;}"
                                         "QPushButton:hover {background-image: url(" + backgroundPath + "buttonDifficultySelectedHover.png);}"
                                         "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonDifficultySelected.png);}";
    buttonStyleSheetDisabled = "QPushButton {background-image: url(" + backgroundPath + "button.png); border: 0; color: grey;}"
                               "QPushButton:hover {background-image: url(" + backgroundPath + "buttonHover.png);}"
                               "QPushButton:pressed {background-image: url(" + backgroundPath + "button.png);}";
    buttonStyleSheetShadow = "background-image: url(" + backgroundPath + "buttonShadow.png)";
    buttonStyleSheetDifficultyShadow = "background-image: url(" + backgroundPath + "buttonDifficultyShadow.png)";
    turn = 0;
    computerDifficulty = 0;

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
    ui->txtGoesFirst->setStyleSheet("color: white");
    ui->txtFriend->setStyleSheet("color: white");

    // buttons
    ui->buttonPlayComputer->setStyleSheet(buttonStyleSheet);
    ui->buttonPlayComputerShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonPlayFriend->setStyleSheet(buttonStyleSheet);
    ui->buttonPlayFriendShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonSettings->setStyleSheet(buttonStyleSheet);
    ui->buttonSettingsShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonExit->setStyleSheet(buttonStyleSheet);
    ui->buttonExitShadow->setStyleSheet(buttonStyleSheetShadow);

    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerEasyShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerMediumShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerHardShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerImpossibleShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheetDisabled);
    ui->buttonComputerNextShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonComputerBack->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerBackShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonComputerNext->setEnabled(false);

    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP1FirstShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2FirstShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirstShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonAlternateFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonAlternateFirstShadow->setStyleSheet(buttonStyleSheetDifficultyShadow);
    ui->buttonPlay->setStyleSheet(buttonStyleSheetDisabled);
    ui->buttonPlayShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonGoesFirstBack->setStyleSheet(buttonStyleSheet);
    ui->buttonGoesFirstBackShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonPlay->setEnabled(false);

    ui->buttonFriendNext->setStyleSheet(buttonStyleSheetDisabled);
    ui->buttonFriendNextShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonFriendBack->setStyleSheet(buttonStyleSheet);
    ui->buttonFriendBackShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonFriendNext->setEnabled(false);
}

void Chess::on_buttonPlayComputer_clicked()
{
    ui->uiMenu->setCurrentIndex(1);
}

void Chess::on_buttonComputerEasy_clicked()
{
    if (computerDifficulty == 1)
    {
        return;
    }
    computerDifficulty = 1;
    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerNext->setEnabled(true);
}

void Chess::on_buttonComputerMedium_clicked()
{
    if (computerDifficulty == 2)
    {
        return;
    }
    computerDifficulty = 2;
    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerNext->setEnabled(true);
}

void Chess::on_buttonComputerHard_clicked()
{
    if (computerDifficulty == 3)
    {
        return;
    }
    computerDifficulty = 3;
    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerNext->setEnabled(true);
}

void Chess::on_buttonComputerImpossible_clicked()
{
    if (computerDifficulty == 4)
    {
        return;
    }
    computerDifficulty = 4;
    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheet);
    ui->buttonComputerNext->setEnabled(true);
}

void Chess::on_buttonComputerNext_clicked()
{
    ui->uiMenu->setCurrentIndex(4);
}

void Chess::on_buttonComputerBack_clicked()
{
    computerDifficulty = 0;
    ui->buttonComputerEasy->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerMedium->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerHard->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerImpossible->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonComputerNext->setStyleSheet(buttonStyleSheetDisabled);
    ui->buttonComputerNext->setEnabled(false);
    ui->uiMenu->setCurrentIndex(0);
}

void Chess::on_buttonP1First_clicked()
{
    if (chosenFirst && turn == 0)
    {
        return;
    }
    chosenFirst = true;
    turn = 0;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonP2First_clicked()
{
    if (chosenFirst && turn == 1)
    {
        return;
    }
    chosenFirst = true;
    turn = 1;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonRandomFirst_clicked()
{
    if (chosenFirst && turn == 2)
    {
        return;
    }
    chosenFirst = true;
    turn = 2;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonAlternateFirst_clicked()
{
    if (alternateTurns)
    {
        alternateTurns = false;
        ui->buttonAlternateFirst->setStyleSheet(buttonStyleSheetDifficulty);
    }
    else if (!alternateTurns)
    {
        alternateTurns = true;
        ui->buttonAlternateFirst->setStyleSheet(buttonStyleSheetDifficultySelected);
    }
}

void Chess::on_buttonPlay_clicked()
{

}

void Chess::on_buttonGoesFirstBack_clicked()
{
    chosenFirst = false;
    turn = 0;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonAlternateFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonPlay->setStyleSheet(buttonStyleSheetDisabled);
    ui->buttonPlay->setEnabled(false);
    if (computerDifficulty != 0)
    {
        ui->uiMenu->setCurrentIndex(1);
    }
    else
    {
        ui->uiMenu->setCurrentIndex(2);
    }
}

void Chess::on_buttonPlayFriend_clicked()
{
    ui->uiMenu->setCurrentIndex(2);
}

