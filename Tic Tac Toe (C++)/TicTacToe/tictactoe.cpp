#include "tictactoe.h"
#include "ui_tictactoe.h"
#include "QRandomGenerator"
#include "vector"

QStringList pieces;
QStringList playerNames;
std::vector<std::vector<QString>> board;
int starting_turn;
int turn;
int piecesPlaced;
int player1WinCount;
int player2WinCount;
bool gameOver;

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    pieces = {"X", "O"};
    clearBoard();
    clearWins();
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
    starting_turn = turn;
    QString player1Name = ui->txtP1Name->text();
    QString player2Name = ui->txtP2Name->text();
    playerNames << player1Name << player2Name;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
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
    clearWins();
    playerNames = {};
    turn = 0;
}

void TicTacToe::on_buttonPlayAI_clicked()
{
    turn = ui->comboAIFirst->currentIndex();
    starting_turn = turn;
    QString playerName = ui->txtPName->text();
    QString AIName = ui->txtAIName->text();
    playerNames << playerName << AIName;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
    playerName += ": X";
    AIName += ": O";
    ui->txtP1Tile->setText(playerName);
    ui->txtP2Tile->setText(AIName);
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    ui->stackedWidget->setCurrentIndex(2);
}

int TicTacToe::checkWin()
{
    if (piecesPlaced <= 4) {
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
    if (piecesPlaced == 9) {
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

    turn = starting_turn;
    piecesPlaced = 0;
    gameOver = false;
}

void TicTacToe::clearWins()
{
    ui->txtP1Wins->setText("Wins: 0");
    ui->txtP2Wins->setText("Wins: 0");

    player1WinCount = 0;
    player2WinCount = 0;
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
    piecesPlaced++;

    int win = checkWin();
    // no win yet
    if (win == -1) {
        turn = 1 - turn;
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
}

