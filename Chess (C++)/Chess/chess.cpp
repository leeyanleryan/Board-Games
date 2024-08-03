#include "chess.h"
#include "ui_chess.h"
#include "chess_ai.h"
#include "QMimeData"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QPushButton"
#include "QVBoxLayout"
#include "QScrollBar"
#include "QRandomGenerator"

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
    , ai(new ChessAI(this))
{
    ui->setupUi(this);
    variableSetup();
    launchSetup();
}

Chess::~Chess()
{
    delete ui;
    delete ai;
}

void Chess::variableSetup()
{
    buttonPositionMap = {};
    piecePositionMap = {};
    pieceImageMap = {};
    board = {};
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
    playerNames = {};
    chosenFirst = false;
    randomTurn = false;
    alternateTurns = false;
    computerDifficulty = 0;
    gameStarted = false;
    gameNumber = 0;
    aiTurn = 0;
    turn = 0;
    moveNumber = 1;
    moveLabels = {};
    legalMoves = {};
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
            ChessButton *button = findChild<ChessButton*>(buttonName);
            buttonPositionMap[qMakePair(row, col)] = button;

            connect(button, &ChessButton::clicked, [this, row, col, button]()
            {
                handleDrop(button, button);
            });
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
    ui->txtP1Name->setStyleSheet("color: white");
    ui->txtP2Name->setStyleSheet("color: white");
    ui->txtSettings->setStyleSheet("color: white");
    ui->txtChess->setStyleSheet("color: white");

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

    ui->buttonFriendNext->setStyleSheet(buttonStyleSheet);
    ui->buttonFriendNextShadow->setStyleSheet(buttonStyleSheetShadow);
    ui->buttonFriendBack->setStyleSheet(buttonStyleSheet);
    ui->buttonFriendBackShadow->setStyleSheet(buttonStyleSheetShadow);

    ui->buttonSettingsBack->setStyleSheet(buttonStyleSheet);
    ui->buttonSettingsBackShadow->setStyleSheet(buttonStyleSheetShadow);

    ui->buttonChessQuit->setStyleSheet(buttonStyleSheet);
    ui->buttonChessQuitShadow->setStyleSheet(buttonStyleSheetShadow);

    // line edit
    ui->lineP1Name->setStyleSheet("background-image: url(" + backgroundPath + "lineEdit.png); border: 0; color: white");
    ui->lineP2Name->setStyleSheet("background-image: url(" + backgroundPath + "lineEdit.png); border: 0; color: white");

    // scroll
    ui->scrollMovesPlayed->setStyleSheet("background-image: url(" + backgroundPath + "movesPlayed.png); border: 0; color: white");
}

void Chess::on_buttonPlayComputer_clicked()
{
    ui->uiMenu->setCurrentIndex(1);
}

void Chess::on_buttonComputerEasy_pressed()
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

void Chess::on_buttonComputerMedium_pressed()
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

void Chess::on_buttonComputerHard_pressed()
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

void Chess::on_buttonComputerImpossible_pressed()
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
    QString p1Name = "You";
    QString p2Name;
    if (computerDifficulty == 1)
    {
        p2Name = "Easy BOT";
    }
    else if (computerDifficulty == 2)
    {
        p2Name = "Medium BOT";
    }
    else if (computerDifficulty == 3)
    {
        p2Name = "Hard BOT";
    }
    else if (computerDifficulty == 4)
    {
        p2Name = "IMPOSSIBLE BOT";
    }
    ui->buttonP1First->setText(p1Name);
    ui->buttonP2First->setText(p2Name);
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

void Chess::on_buttonP1First_pressed()
{
    if (chosenFirst && turn == 0)
    {
        return;
    }
    chosenFirst = true;
    randomTurn = false;
    turn = 0;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonP2First_pressed()
{
    if (chosenFirst && turn == 1)
    {
        return;
    }
    chosenFirst = true;
    randomTurn = false;
    turn = 1;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonRandomFirst_pressed()
{
    if (chosenFirst && randomTurn)
    {
        return;
    }
    chosenFirst = true;
    randomTurn = true;
    turn = 0;
    ui->buttonP1First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonP2First->setStyleSheet(buttonStyleSheetDifficulty);
    ui->buttonRandomFirst->setStyleSheet(buttonStyleSheetDifficultySelected);
    ui->buttonPlay->setStyleSheet(buttonStyleSheet);
    ui->buttonPlay->setEnabled(true);
}

void Chess::on_buttonAlternateFirst_pressed()
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

void Chess::on_buttonGoesFirstBack_clicked()
{
    chosenFirst = false;
    randomTurn = false;
    alternateTurns = false;
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

void Chess::on_lineP1Name_editingFinished()
{
    if (ui->lineP1Name->text().isEmpty() || ui->lineP1Name->text() == ui->lineP2Name->text())
    {
        ui->buttonFriendNext->setStyleSheet(buttonStyleSheetDisabled);
        ui->buttonFriendNext->setEnabled(false);
    }
    else
    {
        ui->buttonFriendNext->setStyleSheet(buttonStyleSheet);
        ui->buttonFriendNext->setEnabled(true);
    }
}


void Chess::on_lineP2Name_editingFinished()
{
    if (ui->lineP2Name->text().isEmpty() || ui->lineP2Name->text() == ui->lineP1Name->text())
    {
        ui->buttonFriendNext->setStyleSheet(buttonStyleSheetDisabled);
        ui->buttonFriendNext->setEnabled(false);
    }
    else
    {
        ui->buttonFriendNext->setStyleSheet(buttonStyleSheet);
        ui->buttonFriendNext->setEnabled(true);
    }
}

void Chess::on_buttonFriendNext_clicked()
{
    QString p1Name = ui->lineP1Name->text();
    QString p2Name = ui->lineP2Name->text();
    ui->buttonP1First->setText(p1Name);
    ui->buttonP2First->setText(p2Name);
    ui->uiMenu->setCurrentIndex(4);
}

void Chess::on_buttonFriendBack_clicked()
{
    ui->uiMenu->setCurrentIndex(0);
}

void Chess::on_buttonSettings_clicked()
{
    ui->uiMenu->setCurrentIndex(3);
}

void Chess::on_buttonSettingsBack_clicked()
{
    ui->uiMenu->setCurrentIndex(0);
}

void Chess::on_buttonExit_clicked()
{
    qApp->exit();
}

void Chess::on_buttonChessQuit_clicked()
{
    playerNames = {};
    gameStarted = false;
    gameNumber = 0;
    moveLabels = {};
    ui->uiMenu->setCurrentIndex(4);
}

void Chess::on_buttonPlay_clicked()
{
    if (randomTurn)
    {
        turn = QRandomGenerator::global()->bounded(2);
    }
    if (turn == 0)
    {
        playerNames = {ui->buttonP1First->text(), ui->buttonP2First->text()};
    }
    else if (turn == 1)
    {
        playerNames = {ui->buttonP2First->text(), ui->buttonP1First->text()};
    }
    if (computerDifficulty != 0)
    {
        aiTurn = 1 - turn;
        ai->setDifficulty(computerDifficulty);
    }
    newGame();
    ui->uiMenu->setCurrentIndex(5);
}

void Chess::newGame()
{
    setDefaultBoard();
    gameStarted = true;
    gameNumber++;
    turn = 0;
    moveNumber = 1;
    moveLabels = {};
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayoutUI = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayoutUI);
    ui->scrollMovesPlayed->setWidget(scrollWidget);
    ui->scrollMovesPlayed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollLayoutUI->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    scrollLayout = scrollLayoutUI;
    ui->txtChess->setText("Game " + QString::number(gameNumber));
}

void Chess::autoScroll()
{
    QScrollBar *scrollBar = ui->scrollMovesPlayed->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void Chess::addMove(const QString &move)
{
    QLabel *label = new QLabel(move, this);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label->setMaximumHeight(30);
    QFont font = label->font();
    font.setPointSize(12);
    if (turn == 0)
    {
        label = new QLabel(QString("%1. %2").arg(moveNumber).arg(move), this);
        label->setFont(font);
        scrollLayout->insertWidget(scrollLayout->count() - 1, label); // Insert before the spacer
        moveNumber++;
        moveLabels.append(label);
    }
    else if (turn == 1)
    {
        label = moveLabels.last();
        label->setText(label->text() + " " + move);
    }
    autoScroll();
}

void Chess::handleDrop(ChessButton *source, ChessButton *target)
{
    QIcon pieceIcon = source->icon();
    source->setIcon(QIcon());
    target->setIcon(pieceIcon);
    target->setIconSize(QSize(90, 90));
}

void Chess::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

void Chess::dropEvent(QDropEvent *event)
{
    ChessButton *targetButton = qobject_cast<ChessButton*>(childAt(event->position().toPoint()));
    if (targetButton) {
        QIcon pieceIcon = QIcon(QPixmap::fromImage(qvariant_cast<QImage>(event->mimeData()->imageData())));
        targetButton->setIcon(pieceIcon);
    }
}

void Chess::on_a1_clicked()
{
    if (!gameStarted)
    {
        return;
    }

    addMove("e4");
    turn = 1 - turn;
}

void Chess::on_b1_clicked()
{
    if (!gameStarted)
    {
        return;
    }

    addMove("e5");
    turn = 1 - turn;
}

void Chess::on_c1_clicked()
{
    if (!gameStarted)
    {
        return;
    }

    legalMoves.push_back(qMakePair(1, 2));
    qDebug() << legalMoves;
}

