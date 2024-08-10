#include "chess.h"
#include "ui_chess.h"
#include "chess_ai.h"
#include "chess_logic.h"
#include "QMimeData"
#include "QDragEnterEvent"
#include "QDropEvent"
#include "QPushButton"
#include "QVBoxLayout"
#include "QScrollBar"
#include "QRandomGenerator"

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , floatingIconLabel(new QLabel(this))
    , ui(new Ui::Chess)
{
    auto start = std::chrono::high_resolution_clock::now();

    ui->setupUi(this);
    variableSetup();
    launchSetup();
    setAcceptDrops(true);

    auto end = std::chrono::high_resolution_clock::now();
    timeTakenToLoad = end-start;
    qDebug() << "Time taken: " << timeTakenToLoad;
}

Chess::~Chess()
{
    delete ui;
    delete ai;
}

void Chess::variableSetup()
{
    logic = new ChessLogic(this);
    ai = new ChessAI(this);

    coordinateButtonMap = {}; // example: (0,0): ChessButton named "a8", (0,1): ChessButton named "b8"
    notationCoordinateMap = {}; // example: "a8": (0,0), "b8": (0,1)
    coordinateNotationMap = {}; // example: (0,0): "a8"
    coordinatePieceMap = {}; // example: (0,0): 'r', (0,1): 'n'
    pieceImageMap = {}; // example: 'r': "RookBlack"

    floatingIconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    floatingIconLabel->setVisible(false);
    //floatingIconLabel->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //floatingIconLabel->setAttribute(Qt::WA_NoSystemBackground, true);
    //floatingIconLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    //floatingIconLabel->setAttribute(Qt::WA_ShowWithoutActivating, true);
    floatingIconLabel->raise();

    board = {};

    pieceImagePath = ":/Pieces/Neo/";
    boardImagePath = ":/Board/Brown/";
    chessSoundPath = ":/Sound/Default/";
    backgroundPath = ":/Background/Default/";
    iconsImagePath = ":/Icons/";

    buttonStyleSheet = "QPushButton {background-image: url(" + backgroundPath + "button.png); border: 0; color: white;}"
                       "QPushButton:hover {background-image: url(" + backgroundPath + "buttonHover.png);}"
                       "QPushButton:pressed {background-image: url(" + backgroundPath + "button.png);}";
    buttonStyleSheetShadow = "background-image: url(" + backgroundPath + "buttonShadow.png)";
    buttonStyleSheetDisabled = "QPushButton {background-image: url(" + backgroundPath + "button.png); border: 0; color: grey;}"
                               "QPushButton:hover {background-image: url(" + backgroundPath + "buttonHover.png);}"
                               "QPushButton:pressed {background-image: url(" + backgroundPath + "button.png);}";

    buttonStyleSheetDifficulty = "QPushButton {background-image: url(" + backgroundPath + "buttonDifficulty.png); border: 0; color: white;}"
                                 "QPushButton:hover {background-image: url(" + backgroundPath + "buttonDifficultyHover.png);}"
                                 "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonDifficultySelected.png);}";
    buttonStyleSheetDifficultySelected = "QPushButton {background-image: url(" + backgroundPath + "buttonDifficultySelected.png); border: 0; color: white;}"
                                         "QPushButton:hover {background-image: url(" + backgroundPath + "buttonDifficultySelectedHover.png);}"
                                         "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonDifficultySelected.png);}";
    buttonStyleSheetDifficultyShadow = "background-image: url(" + backgroundPath + "buttonDifficultyShadow.png)";

    buttonStyleSheetGame = "QPushButton {background-image: url(" + backgroundPath + "buttonGame.png); border: 0; color: white;}"
                           "QPushButton:hover {background-image: url(" + backgroundPath + "buttonGameHover.png);}"
                           "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonGame.png);}";
    buttonStyleSheetGameShadow = "background-image: url(" + backgroundPath + "buttonGameShadow.png)";

    buttonStyleSheetEndScreen = "QPushButton {background-image: url(" + backgroundPath + "buttonEndScreen.png); border: 0; color: white;}"
                                "QPushButton:hover {background-image: url(" + backgroundPath + "buttonEndScreenHover.png);}"
                                "QPushButton:pressed {background-image: url(" + backgroundPath + "buttonEndScreen.png);}";;
    buttonStyleSheetEndScreenShadow = "background-image: url(" + backgroundPath + "buttonEndScreenShadow.png)";

    playerNames = {};
    playerScores = {0, 0};
    chosenFirst = false;
    randomTurn = false;
    alternateTurns = false;
    computerDifficulty = 0;
    gameStarted = false;
    gameNumber = 0;
    computerTurn = 0;
    turn = 0;

    moveNumber = 1;
    moveLabels = {};
    legalMoves = {};

    prevMovedSourceButton = nullptr;
    prevMovedTargetButton = nullptr;
    prevClickedSourceButton = nullptr;
    sourceButtonDrops = 0;

    promotionSourceCoord = {};
    promotionTargetCoord = {};
    promotionMove = "";

    uiBoardTopLeft = ui->uiBoard->geometry().topLeft();
}

void Chess::launchSetup()
{
    setDefaultBoard();
    setCoordinateButtonMap();
    setCoordinatePieceMap();
    setPieceImageMap();
    setChessBoard();
    setPromotionUI();
    setMenu();
}

void Chess::setDefaultBoard()
{
    board[0] = {'r','n','b','q','k','b','n','r'};
    board[1] = {'p','p','p','p','p','p','p','p'};
    board[2] = {'-','-','-','-','-','-','-','-'};
    board[3] = {'-','-','-','-','-','-','-','-'};
    board[4] = {'-','-','-','-','-','-','-','-'};
    board[5] = {'-','-','-','-','-','-','-','-'};
    board[6] = {'P','P','P','P','P','P','P','P'};
    board[7] = {'R','N','B','Q','K','B','N','R'};

    // board[0] = {'-','-','-','-','k','-','-','-'};
    // board[1] = {'-','-','-','-','-','-','-','-'};
    // board[2] = {'-','-','-','-','b','-','-','-'};
    // board[3] = {'-','-','-','-','-','-','-','-'};
    // board[4] = {'-','-','-','-','-','-','-','-'};
    // board[5] = {'-','-','-','-','-','-','-','-'};
    // board[6] = {'-','-','-','-','-','-','-','-'};
    // board[7] = {'-','-','-','Q','K','-','-','-'};
}

void Chess::setCoordinateButtonMap()
{
    std::array<char, 8> alphabetPosition = {'a','b','c','d','e','f','g','h'};
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            QString notation = QString("%1%2").arg(alphabetPosition[col]).arg(8-row);
            ChessButton *button = findChild<ChessButton*>(notation);
            QPair<int, int> coord = qMakePair(row, col);
            coordinateButtonMap[coord] = button;
            notationCoordinateMap[notation] = coord;
            coordinateNotationMap[coord] = notation;
        }
    }
}

void Chess::setCoordinatePieceMap()
{
    coordinatePieceMap = {};

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col] != '-')
            {
                coordinatePieceMap[qMakePair(row, col)] = board[row][col];
            }
        }
    }
}

void Chess::setPieceImageMap()
{
    // black
    pieceImageMap['r'] = "RookBlack";
    pieceImageMap['n'] = "KnightBlack";
    pieceImageMap['b'] = "BishopBlack";
    pieceImageMap['q'] = "QueenBlack";
    pieceImageMap['k'] = "KingBlack";
    pieceImageMap['p'] = "PawnBlack";
    // white
    pieceImageMap['R'] = "RookWhite";
    pieceImageMap['N'] = "KnightWhite";
    pieceImageMap['B'] = "BishopWhite";
    pieceImageMap['Q'] = "QueenWhite";
    pieceImageMap['K'] = "KingWhite";
    pieceImageMap['P'] = "PawnWhite";
}

void Chess::setButtonIcon(QPushButton *button, const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(QSize(90, 90));
}

void Chess::setButtonStyleSheet(QPushButton *button, const QString &imagePath)
{
    button->setStyleSheet("background-image: url(" + imagePath + "); border: 0");
}

void Chess::setChessBoard()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            ChessButton *button = coordinateButtonMap[{row, col}];
            if ((row+col)%2 == 0)
            {
                setButtonStyleSheet(button, boardImagePath + "BoardWhite.png");
            }
            else if ((row+col)%2 == 1)
            {
                setButtonStyleSheet(button, boardImagePath + "BoardBlack.png");
            }
            if (coordinatePieceMap.contains(qMakePair(row, col)))
            {
                setButtonIcon(button, pieceImagePath + pieceImageMap[coordinatePieceMap[qMakePair(row, col)]] + ".png");
            }
            else
            {
                button->setIcon(QIcon());
            }
        }
    }
}

void Chess::setPromotionUI()
{
    std::array<ChessPromotionButton*, 8> buttonArray = {ui->queen0, ui->queen1, ui->knight0, ui->knight1, ui->rook0, ui->rook1, ui->bishop0, ui->bishop1};
    std::array<char, 8> pieceArray = {'Q', 'q', 'N', 'n', 'R', 'r', 'B', 'b'};

    choosingPromotedPiece = false;

    for (size_t i = 0; i < buttonArray.size(); i++)
    {
        buttonArray[i]->chessPiece = pieceArray[i];
        buttonArray[i]->setStyleSheet("background: transparent;");
        setButtonIcon(buttonArray[i], pieceImagePath + pieceImageMap[pieceArray[i]] + ".png");
    }

    std::array<ChessPromotionButton*, 2> closeArray = {ui->close0, ui->close1};

    for (size_t i = 0; i < closeArray.size(); i++)
    {
        closeArray[i]->chessPiece = '-';
        closeArray[i]->setStyleSheet("background: transparent;");
    }

    ui->uiPromotion->setStyleSheet("background: transparent;");
    ui->turn0->setStyleSheet("background-image: url(" + backgroundPath + "promoteBackground.png); border: 0");
    ui->turn1->setStyleSheet("background-image: url(" + backgroundPath + "promoteBackgroundReversed.png); border: 0");

    ui->uiPromotion->lower();
}

void Chess::setMenu()
{
    ui->uiMenu->setCurrentIndex(0);

    // background
    ui->centralwidget->setStyleSheet("background-image: url(" + backgroundPath + "background.png); border: 0");
    ui->uiMenu->setStyleSheet("background-image: url(" + backgroundPath + "menu.png); border: 0");
    ui->uiEndScreen->setStyleSheet("background-image: url(" + backgroundPath + "endScreen.png); border: 0");

    // text
    ui->txtWelcome->setStyleSheet("color: white");
    ui->txtComputer->setStyleSheet("color: white");
    ui->txtGoesFirst->setStyleSheet("color: white");
    ui->txtFriend->setStyleSheet("color: white");
    ui->txtP1Name->setStyleSheet("color: white");
    ui->txtP2Name->setStyleSheet("color: white");
    ui->txtSettings->setStyleSheet("color: white");
    ui->txtChess->setStyleSheet("color: white");
    ui->botProfile0Name->setStyleSheet("color: white");
    ui->botProfile0Wins->setStyleSheet("color: white");
    ui->topProfile1Name->setStyleSheet("color: white");
    ui->topProfile1Wins->setStyleSheet("color: white");
    ui->botProfile0Time->setStyleSheet("color: #262421; background: transparent");
    ui->topProfile1Time->setStyleSheet("color: white; background: transparent");
    ui->uiForfeitGameHeader->setStyleSheet("color: white; background: transparent");
    ui->uiQuitGameHeader->setStyleSheet("color: white; background: transparent");
    ui->uiNewGameHeader->setStyleSheet("color: white; background: transparent");
    ui->uiWinnerHeader->setStyleSheet("color: white; background: transparent");
    ui->uiForfeitGameClose->setStyleSheet("color: white; background: transparent");
    ui->uiQuitGameClose->setStyleSheet("color: white; background: transparent");
    ui->uiNewGameClose->setStyleSheet("color: white; background: transparent");
    ui->uiWinnerClose->setStyleSheet("color: white; background: transparent");
    ui->uiWinnerName->setStyleSheet("color: white; background: transparent");

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

    ui->buttonChessNew->setStyleSheet(buttonStyleSheetGame);
    ui->buttonChessNewShadow->setStyleSheet(buttonStyleSheetGameShadow);
    ui->buttonChessLeft->setStyleSheet(buttonStyleSheetGame);
    ui->buttonChessLeftShadow->setStyleSheet(buttonStyleSheetGameShadow);
    ui->buttonChessRight->setStyleSheet(buttonStyleSheetGame);
    ui->buttonChessRightShadow->setStyleSheet(buttonStyleSheetGameShadow);
    ui->buttonChessForfeit->setStyleSheet(buttonStyleSheetGame);
    ui->buttonChessForfeitShadow->setStyleSheet(buttonStyleSheetGameShadow);
    ui->buttonChessQuit->setStyleSheet(buttonStyleSheetGame);
    ui->buttonChessQuitShadow->setStyleSheet(buttonStyleSheetGameShadow);

    ui->uiQuitGameYes->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiQuitGameYesShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiQuitGameNo->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiQuitGameNoShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiForfeitGameYes->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiForfeitGameYesShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiForfeitGameNo->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiForfeitGameNoShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiNewGameYes->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiNewGameYesShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiNewGameNo->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiNewGameNoShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiWinnerNewGame->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiWinnerNewGameShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiWinnerQuitGame->setStyleSheet(buttonStyleSheetEndScreen);
    ui->uiWinnerQuitGameShadow->setStyleSheet(buttonStyleSheetEndScreenShadow);
    ui->uiEndScreen->lower();

    // line edit
    ui->lineP1Name->setStyleSheet("background-image: url(" + backgroundPath + "lineEdit.png); border: 0; color: white");
    ui->lineP2Name->setStyleSheet("background-image: url(" + backgroundPath + "lineEdit.png); border: 0; color: white");

    // scroll
    ui->scrollMovesPlayed->setStyleSheet("background-image: url(" + backgroundPath + "movesPlayed.png); border: 0; color: white");

    // icons
    QIcon *bP0Image = new QIcon(iconsImagePath + "WhiteKnight_0.png");
    QPixmap bP0ImagePix = bP0Image->pixmap(QSize(60, 60));
    ui->botProfile0Image->setText("");
    ui->botProfile0Image->setPixmap(bP0ImagePix);
    QIcon *tP1Image = new QIcon(iconsImagePath + "BlackKnight_0.png");
    QPixmap tP1ImagePix = tP1Image->pixmap(QSize(60, 60));
    ui->topProfile1Image->setText("");
    ui->topProfile1Image->setPixmap(tP1ImagePix);

    // clock
    QIcon *bP0Clock = new QIcon(backgroundPath + "clockWhite.png");
    QPixmap bP0ClockPix = bP0Clock->pixmap(QSize(130, 60));
    ui->botProfile0TimeBackground->setText("");
    ui->botProfile0TimeBackground->setPixmap(bP0ClockPix);
    QIcon *tP1Clock = new QIcon(backgroundPath + "clockBlack.png");
    QPixmap tP1ClockPix = tP1Clock->pixmap(QSize(130, 60));
    ui->topProfile1TimeBackground->setText("");
    ui->topProfile1TimeBackground->setPixmap(tP1ClockPix);
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

void Chess::on_buttonPlay_clicked()
{
    auto start = std::chrono::high_resolution_clock::now();

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
        computerTurn = 1 - turn;
        ai->setDifficulty(computerDifficulty);
    }

    playerScores = {0, 0};

    newGame();

    ui->botProfile0Name->setText(playerNames[0]);
    ui->topProfile1Name->setText(playerNames[1]);

    ui->uiMenu->setCurrentIndex(5);

    qDebug();
    for (const std::array<char, 8> &row : board)
    {
        QDebug dbg = qDebug();
        for (char piece : row)
        {
            dbg.noquote() << piece;
        }
    }
    qDebug();

    auto end = std::chrono::high_resolution_clock::now();
    timeTakenToLoad = end-start;

    qDebug() << "Time taken: " << timeTakenToLoad;
}

void Chess::newGame()
{
    gameStarted = true;
    gameNumber++;
    turn = 0;
    moveNumber = 1;
    moveLabels = {};

    if (alternateTurns && gameNumber != 1)
    {
        QString tempP2Name = playerNames[1];
        playerNames[1] = playerNames[0];
        playerNames[0] = tempP2Name;

        if (computerDifficulty != 0)
        {
            computerTurn = 1 - computerTurn;
            ai->setTurn(computerTurn);
        }
    }

    prevMovedSourceButton = nullptr;
    prevMovedTargetButton = nullptr;
    prevClickedSourceButton = nullptr;
    sourceButtonDrops = 0;
    clickedSameButton = false;

    setDefaultBoard();
    setCoordinatePieceMap();
    setChessBoard();

    logic->resetGame(board);

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
    if (1-turn == 0)
    {
        label = new QLabel(QString("%1. %2").arg(moveNumber).arg(move), this);
        label->setFont(font);
        scrollLayout->insertWidget(scrollLayout->count() - 1, label); // Insert before the spacer
        moveNumber++;
        moveLabels.append(label);
    }
    else if (1-turn == 1)
    {
        label = moveLabels.last();
        label->setText(label->text() + " " + move);
    }
    autoScroll();
}

void Chess::showLegalMoveImages()
{
    for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it)
    {
        QPair<int, int> coord = *it;
        char piece = board[coord.first][coord.second];
        ChessButton *button = coordinateButtonMap[coord];

        if (piece == '-')
        {
            setButtonIcon(button, pieceImagePath + "LegalMove.png");
        }
        else
        {
            setButtonIcon(button, pieceImagePath + pieceImageMap[piece] + "Capture.png");
        }
    }
}

void Chess::hideLegalMoveImages()
{
    for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it)
    {
        QPair<int, int> coord = *it;
        char piece = board[coord.first][coord.second];
        ChessButton *button = coordinateButtonMap[coord];

        if (piece == '-')
        {
            coordinateButtonMap[coord]->setIcon(QIcon());
        }
        else
        {
            setButtonIcon(button, pieceImagePath + pieceImageMap[piece] + ".png");
        }
    }
}

void Chess::resetButtonStyleSheet(ChessButton *button)
{
    QPair<int, int> coordinate = notationCoordinateMap[button->objectName()];
    int row = coordinate.first;
    int col = coordinate.second;
    if ((row+col)%2 == 0)
    {
        setButtonStyleSheet(button, boardImagePath + "BoardWhite.png");
    }
    else if ((row+col)%2 == 1)
    {
        setButtonStyleSheet(button, boardImagePath + "BoardBlack.png");
    }
}

void Chess::showLegalMoves(ChessButton *sourceButton)
{
    if (!sourceButton)
    {
        return;
    }

    // clicked on previously moved source or target button
    if ((prevMovedSourceButton && prevMovedSourceButton == sourceButton) ||
        (prevMovedTargetButton && prevMovedTargetButton == sourceButton))
    {
        hideLegalMoveImages();
        legalMoves = {};

        if (prevClickedSourceButton)
        {
            resetButtonStyleSheet(prevClickedSourceButton);
            prevClickedSourceButton = nullptr;
        }
    }
    // not clicked before
    else if (!prevClickedSourceButton)
    {
        sourceButtonDrops = 0;
        clickedSameButton = false;

        legalMoves = logic->getLegalMoves(board, notationCoordinateMap[sourceButton->objectName()], turn);
        showLegalMoveImages();

        setButtonStyleSheet(sourceButton, boardImagePath + "SelectedPiece.png");
        prevClickedSourceButton = sourceButton;
    }
    // has clicked before, clicked on same button
    else if (prevClickedSourceButton == sourceButton)
    {
        clickedSameButton = true;
    }
    // has clicked before, clicked on different button
    else if (prevClickedSourceButton != sourceButton)
    {
        sourceButtonDrops = 0;
        clickedSameButton = false;

        hideLegalMoveImages();
        legalMoves = logic->getLegalMoves(board, notationCoordinateMap[sourceButton->objectName()], turn);
        showLegalMoveImages();

        resetButtonStyleSheet(prevClickedSourceButton);
        setButtonStyleSheet(sourceButton, boardImagePath + "SelectedPiece.png");
        prevClickedSourceButton = sourceButton;
    }
}

void Chess::makeMove(ChessButton *targetButton)
{
    QPixmap pixmap = prevClickedSourceButton->icon().pixmap(prevClickedSourceButton->iconSize());
    floatingIconLabel->setPixmap(pixmap);
    floatingIconLabel->setFixedSize(pixmap.size());
    floatingIconLabel->raise();
    floatingIconLabel->setVisible(false);
    prevClickedSourceButton->setIcon(QIcon());
    prevClickedSourceButton->setIconSize(QSize(90, 90));
    makeMove(prevClickedSourceButton, targetButton);
}

void Chess::makeMove(ChessButton *sourceButton, ChessButton *targetButton)
{
    if (!sourceButton || !targetButton)
    {
        return;
    }

    QPair<int, int> sourceCoord = notationCoordinateMap[sourceButton->objectName()];
    QPair<int, int> targetCoord = notationCoordinateMap[targetButton->objectName()];

    if (sourceCoord == targetCoord)
    {
        if (sourceButtonDrops == 0)
        {
            sourceButtonDrops = 1;
        }
        else if (sourceButtonDrops == 1 && clickedSameButton)
        {
            clickedSameButton = false;
            prevClickedSourceButton = nullptr;

            if (sourceButton != prevMovedTargetButton && sourceButton != prevMovedSourceButton)
            {
                resetButtonStyleSheet(sourceButton);
            }

            hideLegalMoveImages();
            legalMoves = {};

            sourceButtonDrops = 0;
        }
        sourceButton->setIcon(floatingIconLabel->pixmap(Qt::ReturnByValue));
        sourceButton->setIconSize(QSize(90, 90));
        return;
    }
    else if (!legalMoves.contains(targetCoord))
    {
        if (sourceButtonDrops == 0)
        {
            sourceButtonDrops = 1;
        }
        sourceButton->setIcon(floatingIconLabel->pixmap(Qt::ReturnByValue));
        sourceButton->setIconSize(QSize(90, 90));
        return;
    }

    QString move = logic->makeLegalMove(board, coordinatePieceMap, targetCoord, turn, true);
    // choosing promotion
    if (move == "")
    {
        return;
    }

    hideLegalMoveImages();
    legalMoves = {};

    if (prevMovedSourceButton && prevMovedTargetButton)
    {
        resetButtonStyleSheet(prevMovedSourceButton);
        resetButtonStyleSheet(prevMovedTargetButton);
    }

    prevMovedSourceButton = sourceButton;
    prevMovedTargetButton = targetButton;
    prevClickedSourceButton = nullptr;

    setButtonStyleSheet(targetButton, boardImagePath + "SelectedPiece.png");
    targetButton->setIcon(floatingIconLabel->pixmap(Qt::ReturnByValue));
    targetButton->setIconSize(QSize(90, 90));

    QString gameState;

    if (move.contains(" "))
    {
        QStringList moveSplit = move.split(" ");
        move = moveSplit[0];
        gameState = moveSplit[1];
    }

    addMove(move);

    if (gameState == "Draw")
    {
        gameStarted = false;
        playerScores[0] += 0.5;
        playerScores[1] += 0.5;
        ui->botProfile0Wins->setText("Scores: " + QString::number(playerScores[0]));
        ui->topProfile1Wins->setText("Scores: " + QString::number(playerScores[1]));
        ui->uiWinnerHeader->setText("It's a");
        ui->uiWinnerName->setText("Draw!");
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }
    else if (gameState == "White")
    {
        gameStarted = false;
        playerScores[0]++;
        ui->botProfile0Wins->setText("Scores: " + QString::number(playerScores[0]));
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[0]);
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }
    else if (gameState == "Black")
    {
        gameStarted = false;
        playerScores[1]++;
        ui->topProfile1Wins->setText("Scores: " + QString::number(playerScores[1]));
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[1]);
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }

    qDebug();
    for (const std::array<char, 8> &row : board)
    {
        QDebug dbg = qDebug();
        for (char piece : row)
        {
            dbg.noquote() << piece;
        }
    }
    qDebug();
    qDebug() << "Time taken: " << timeTakenToMove;
}

void Chess::makePromotionMove(QString move)
{
    ChessButton *sourceButton = coordinateButtonMap[promotionSourceCoord];
    ChessButton *targetButton = coordinateButtonMap[promotionTargetCoord];

    hideLegalMoveImages();
    legalMoves = {};

    if (prevMovedSourceButton && prevMovedTargetButton)
    {
        resetButtonStyleSheet(prevMovedSourceButton);
        resetButtonStyleSheet(prevMovedTargetButton);
    }

    prevMovedSourceButton = sourceButton;
    prevMovedTargetButton = targetButton;
    prevClickedSourceButton = nullptr;

    setButtonStyleSheet(targetButton, boardImagePath + "SelectedPiece.png");
    setButtonIcon(targetButton, pieceImagePath + pieceImageMap[board[promotionTargetCoord.first][promotionTargetCoord.second]]);

    QString gameState;

    if (move.contains(" "))
    {
        QStringList moveSplit = move.split(" ");
        move = moveSplit[0];
        gameState = moveSplit[1];
    }

    addMove(move);

    if (gameState == "Draw")
    {
        gameStarted = false;
        playerScores[0] += 0.5;
        playerScores[1] += 0.5;
        ui->uiWinnerHeader->setText("It's a");
        ui->uiWinnerName->setText("Draw!");
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }
    else if (gameState == "White")
    {
        gameStarted = false;
        playerScores[0]++;
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[0]);
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }
    else if (gameState == "Black")
    {
        gameStarted = false;
        playerScores[1]++;
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[1]);
        ui->uiEndScreen->setCurrentIndex(0);
        ui->uiEndScreen->raise();
    }

    qDebug();
    for (const std::array<char, 8> &row : board)
    {
        QDebug dbg = qDebug();
        for (char piece : row)
        {
            dbg.noquote() << piece;
        }
    }
    qDebug();
    qDebug() << "Time taken: " << timeTakenToMove;
}

void Chess::chosenPromotionPiece(char chessPiece)
{
    if (chessPiece != '-')
    {
        makePromotionMove(logic->makeLegalPromotionMove(board, coordinatePieceMap, promotionTargetCoord, turn, chessPiece, promotionMove));
        choosingPromotedPiece = false;
        ui->uiPromotion->lower();
    }
    else
    {
        deselectButton(prevClickedSourceButton);
    }
}

void Chess::showPromotionUI(QPair<int, int> sourceCoord, QPair<int, int> targetCoord, QString move)
{
    choosingPromotedPiece = true;

    promotionSourceCoord = sourceCoord;
    promotionTargetCoord = targetCoord;
    promotionMove = move;

    int targetCol = targetCoord.second;
    QRect currentGeometry = ui->uiPromotion->geometry();

    if (turn == 0)
    {
        ui->uiPromotion->setCurrentIndex(0);
        ui->uiPromotion->setGeometry(5 + targetCol*90, 5, currentGeometry.width(), currentGeometry.height());
    }
    else if (turn == 1)
    {
        ui->uiPromotion->setCurrentIndex(1);
        ui->uiPromotion->setGeometry(5 + targetCol*90, 320, currentGeometry.width(), currentGeometry.height());
    }

    ui->uiPromotion->raise();
}

void Chess::deselectButton(ChessButton *button)
{
    QPair<int, int> sourceCoord = notationCoordinateMap[button->objectName()];

    choosingPromotedPiece = false;

    hideLegalMoveImages();
    legalMoves = {};

    if (prevClickedSourceButton)
    {
        QPair<int, int> prevClickedSourceCoord = notationCoordinateMap[prevClickedSourceButton->objectName()];

        resetButtonStyleSheet(prevClickedSourceButton);
        setButtonIcon(prevClickedSourceButton, pieceImagePath + pieceImageMap[board[prevClickedSourceCoord.first][prevClickedSourceCoord.second]]);
        prevClickedSourceButton = nullptr;
    }

    resetButtonStyleSheet(button);
    setButtonIcon(button, pieceImagePath + pieceImageMap[board[sourceCoord.first][sourceCoord.second]]);

    ui->uiPromotion->lower();
}

void Chess::on_buttonChessNew_clicked()
{
    ui->uiEndScreen->setCurrentIndex(1);
    ui->uiEndScreen->raise();
}

void Chess::on_buttonChessQuit_clicked()
{
    ui->uiEndScreen->setCurrentIndex(2);
    ui->uiEndScreen->raise();
}


void Chess::on_buttonChessForfeit_clicked()
{
    ui->uiEndScreen->setCurrentIndex(3);
    ui->uiEndScreen->raise();
}


void Chess::on_uiWinnerNewGame_clicked()
{
    newGame();
    ui->uiEndScreen->lower();
}


void Chess::on_uiWinnerQuitGame_clicked()
{
    setDefaultBoard();
    setCoordinatePieceMap();
    playerNames = {};
    playerScores = {0, 0};
    gameStarted = false;
    gameNumber = 0;
    moveLabels = {};
    setChessBoard();
    ui->botProfile0Name->setText("White Player Name");
    ui->topProfile1Name->setText("Black Player Name");
    ui->botProfile0Wins->setText("Scores: 0");
    ui->topProfile1Wins->setText("Scores: 0");
    ui->uiEndScreen->lower();
    ui->uiMenu->setCurrentIndex(4);
}

void Chess::on_uiWinnerClose_clicked()
{
    ui->uiEndScreen->lower();
}

void Chess::on_uiNewGameYes_clicked()
{
    newGame();
    ui->uiEndScreen->lower();
}

void Chess::on_uiNewGameNo_clicked()
{
    ui->uiEndScreen->lower();
}


void Chess::on_uiNewGameClose_clicked()
{
    ui->uiEndScreen->lower();
}


void Chess::on_uiQuitGameYes_clicked()
{
    setDefaultBoard();
    setCoordinatePieceMap();
    playerNames = {};
    gameStarted = false;
    gameNumber = 0;
    moveLabels = {};
    setChessBoard();
    ui->botProfile0Name->setText("White Player Name");
    ui->topProfile1Name->setText("Black Player Name");
    ui->botProfile0Wins->setText("Scores: 0");
    ui->topProfile1Wins->setText("Scores: 0");
    ui->uiEndScreen->lower();
    ui->uiMenu->setCurrentIndex(4);
}


void Chess::on_uiQuitGameNo_clicked()
{
    ui->uiEndScreen->lower();
}


void Chess::on_uiQuitGameClose_clicked()
{
    ui->uiEndScreen->lower();
}


void Chess::on_uiForfeitGameYes_clicked()
{
    gameStarted = false;

    if (turn == 0)
    {
        playerScores[1]++;
        ui->topProfile1Wins->setText("Scores: " + QString::number(playerScores[1]));
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[1]);
    }
    else if (turn == 1)
    {
        playerScores[0]++;
        ui->botProfile0Wins->setText("Scores: " + QString::number(playerScores[0]));
        ui->uiWinnerHeader->setText("Winner");
        ui->uiWinnerName->setText(playerNames[0]);
    }

    ui->uiEndScreen->setCurrentIndex(0);
    ui->uiEndScreen->raise();
}


void Chess::on_uiForfeitGameNo_clicked()
{
    ui->uiEndScreen->lower();
}


void Chess::on_uiForfeitGameClose_clicked()
{
    ui->uiEndScreen->lower();
}

