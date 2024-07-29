#include "tictactoe.h"
#include "ui_tictactoe.h"
#include "QRandomGenerator"
#include "vector"
#include "QTime"

QStringList pieces;
QStringList playerNames;
std::vector<std::vector<QString>> board;
int startingTurn;
int turn;
int piecesPlayed;
int player1WinCount;
int player2WinCount;
int AITurn;
bool AIPlaying;
bool gameOver;
QPair<int, int> previousMove;
QMap<QPair<int, int>, QPushButton*> buttonMap;

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    pieces = {"X", "O"};
    clearBoard();
    setBoardEnabled(true);
    clearWins();
    buttonMap[qMakePair(0, 0)] = ui->buttonTTT1;
    buttonMap[qMakePair(0, 1)] = ui->buttonTTT2;
    buttonMap[qMakePair(0, 2)] = ui->buttonTTT3;
    buttonMap[qMakePair(1, 0)] = ui->buttonTTT4;
    buttonMap[qMakePair(1, 1)] = ui->buttonTTT5;
    buttonMap[qMakePair(1, 2)] = ui->buttonTTT6;
    buttonMap[qMakePair(2, 0)] = ui->buttonTTT7;
    buttonMap[qMakePair(2, 1)] = ui->buttonTTT8;
    buttonMap[qMakePair(2, 2)] = ui->buttonTTT9;
    ui->stackedWidget->setCurrentIndex(0);
}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::on_playAI_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void TicTacToe::on_playFriend_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void TicTacToe::on_buttonFriendBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TicTacToe::on_buttonAIBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TicTacToe::on_buttonPlayFriend_clicked()
{
    turn = ui->comboFriendFirst->currentIndex();
    AIPlaying = false;
    QString player1Name = ui->txtP1Name->text();
    QString player2Name = ui->txtP2Name->text();
    playerNames << player1Name << player2Name;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
    startingTurn = turn;
    player1Name += ": X";
    player2Name += ": O";
    ui->txtP1Tile->setText(player1Name);
    ui->txtP2Tile->setText(player2Name);
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    ui->stackedWidget->setCurrentIndex(2);
}

void TicTacToe::on_buttonGameBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clearBoard();
    setBoardEnabled(true);
    clearWins();
    playerNames = {};
    turn = 0;
}

void TicTacToe::on_buttonPlayAI_clicked()
{
    turn = ui->comboAIFirst->currentIndex();
    AIPlaying = true;
    QString playerName = ui->txtPName->text();
    QString AIName = ui->txtAIName->text();
    playerNames << playerName << AIName;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
    startingTurn = turn;
    playerName += ": X";
    AIName += ": O";
    ui->txtP1Tile->setText(playerName);
    ui->txtP2Tile->setText(AIName);
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    ui->stackedWidget->setCurrentIndex(2);
    if (turn == 1) {
        setBoardEnabled(false);
        makeMoveAI();
    }
}

int TicTacToe::checkWin()
{
    if (piecesPlayed <= 4) {
        return -1;
    }
    // horizontal and vertical check
    for (size_t i = 0; i < board.size(); i++) {
        if (board[i][0] != "-" && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
        if (board[0][i] != "-" && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }
    // diagonal check
    if (board[0][0] != "-" && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] != "-" && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }
    if (piecesPlayed == 9) {
        return 0;
    }
    return -1;
}

void TicTacToe::clearBoard() {
    ui->buttonTTT1->setText("");
    ui->buttonTTT2->setText("");
    ui->buttonTTT3->setText("");
    ui->buttonTTT4->setText("");
    ui->buttonTTT5->setText("");
    ui->buttonTTT6->setText("");
    ui->buttonTTT7->setText("");
    ui->buttonTTT8->setText("");
    ui->buttonTTT9->setText("");

    board = {{"-", "-", "-"},
             {"-", "-", "-"},
             {"-", "-", "-"}};
    turn = startingTurn;
    piecesPlayed = 0;
    gameOver = false;
}

void TicTacToe::setBoardEnabled(bool arg) {
    ui->buttonTTT1->setEnabled(arg);
    ui->buttonTTT2->setEnabled(arg);
    ui->buttonTTT3->setEnabled(arg);
    ui->buttonTTT4->setEnabled(arg);
    ui->buttonTTT5->setEnabled(arg);
    ui->buttonTTT6->setEnabled(arg);
    ui->buttonTTT7->setEnabled(arg);
    ui->buttonTTT8->setEnabled(arg);
    ui->buttonTTT9->setEnabled(arg);
}

void TicTacToe::clearWins()
{
    ui->txtP1Wins->setText("Wins: 0");
    ui->txtP2Wins->setText("Wins: 0");

    AIPlaying = false;
    player1WinCount = 0;
    player2WinCount = 0;
}

void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

std::vector<QPair<int, int>> corners = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
std::vector<QPair<int, int>> edges = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

void TicTacToe::makeMoveAI()
{
    delay(500);
    QPair<int, int> coordinate = {-1, -1};
    // no pieces played, AI goes first, will place on either 4 corners
    if (piecesPlayed == 0) {
        coordinate = corners[QRandomGenerator::global()->bounded(4)];
    }
    // 1 piece played, AI goes second, will choose center if player placed anywhere else, otherwise corner
    else if (piecesPlayed == 1) {
        if (previousMove != qMakePair(1, 1)) {
            coordinate = {1, 1};
        }
        else if (previousMove == qMakePair(1, 1)) {
            coordinate = corners[QRandomGenerator::global()->bounded(4)];
        }
    }

    if (coordinate != qMakePair(-1, -1)) {
        board[coordinate.first][coordinate.second] = pieces[turn];
        buttonMap[coordinate]->setText(pieces[turn]);
        piecesPlayed++;
    }

    int win = checkWin();
    // no win yet
    if (win == -1) {
        turn = 1 - turn;
        setBoardEnabled(true);
        QString newPlayer = playerNames[turn];
        ui->txtCurrentTurn->setText("It's " + newPlayer + "'s turn!");
        return;
    }
    // draw
    else if (win == 0) {
        gameOver = true;
        ui->txtCurrentTurn->setText("It's a draw!");
        return;
    }
    // winner
    else if (win == 1) {
        gameOver = true;
        QString winner = playerNames[turn];
        ui->txtCurrentTurn->setText(winner + " wins!");
        if (turn == 0) {
            player1WinCount++;
            ui->txtP1Wins->setText("Wins: " + QString::number(player1WinCount));
        }
        else if (turn == 1) {
            player2WinCount++;
            ui->txtP2Wins->setText("Wins: " + QString::number(player2WinCount));
        }
        return;
    }
}

void TicTacToe::gridButtonClicked()
{
    if (gameOver) {
        return;
    }

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int buttonNum = button->objectName().back().digitValue();
    int row = (buttonNum-1)/3;
    int col = (buttonNum-1)%3;
    if (board[row][col] != "-") {
        return;
    }

    QString piece = pieces[turn];
    board[row][col] = piece;
    button->setText(piece);
    previousMove = qMakePair(row, col);
    piecesPlayed++;

    int win = checkWin();
    // no win yet
    if (win == -1) {
        turn = 1 - turn;
        QString newPlayer = playerNames[turn];
        ui->txtCurrentTurn->setText("It's " + newPlayer + "'s turn!");
        if (AIPlaying && turn == 1) {
            setBoardEnabled(false);
            makeMoveAI();
        }
        return;
    }
    // draw
    else if (win == 0) {
        gameOver = true;
        ui->txtCurrentTurn->setText("It's a draw!");
        return;
    }
    // winner
    else if (win == 1) {
        gameOver = true;
        QString winner = playerNames[turn];
        ui->txtCurrentTurn->setText(winner + " wins!");
        if (turn == 0) {
            player1WinCount++;
            ui->txtP1Wins->setText("Wins: " + QString::number(player1WinCount));
        }
        else if (turn == 1) {
            player2WinCount++;
            ui->txtP2Wins->setText("Wins: " + QString::number(player2WinCount));
        }
        return;
    }
}

void TicTacToe::on_buttonTTT1_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT2_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT3_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT4_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT5_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT6_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT7_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT8_clicked()
{
    gridButtonClicked();
}

void TicTacToe::on_buttonTTT9_clicked()
{
    gridButtonClicked();
}


void TicTacToe::on_buttonNewGame_clicked()
{
    clearBoard();
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    if (AIPlaying && turn == 0) {
        setBoardEnabled(true);
    }
    else if (AIPlaying && turn == 1) {
        setBoardEnabled(false);
        makeMoveAI();
    }
}

