#include "tictactoe.h"
#include "ui_tictactoe.h"
#include "QRandomGenerator"

QStringList pieces;
QStringList playerNames;

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    pieces = {"X", "O"};
    ui->setupUi(this);
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
    int turn = ui->comboFriendFirst->currentIndex();
    QString player1Name = ui->txtP1Name->text();
    QString player2Name = ui->txtP2Name->text();
    playerNames << player1Name << player2Name;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
    player1Name += ": " + pieces[turn];
    player2Name += ": " + pieces[1-turn];
    ui->txtP1Tile->setText(player1Name);
    ui->txtP2Tile->setText(player2Name);
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    ui->stackedWidget->setCurrentIndex(2);
}

void TicTacToe::on_buttonGameBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    playerNames = {};
}

void TicTacToe::on_buttonPlayAI_clicked()
{
    int turn = ui->comboAIFirst->currentIndex();
    QString playerName = ui->txtPName->text();
    QString AIName = ui->txtAIName->text();
    playerNames << playerName << AIName;
    if (turn == 2) {
        turn = QRandomGenerator::global()->bounded(2);
    }
    playerName += ": " + pieces[turn];
    AIName += ": " + pieces[1-turn];
    ui->txtP1Tile->setText(playerName);
    ui->txtP2Tile->setText(AIName);
    ui->txtCurrentTurn->setText("It's " + playerNames[turn] + "'s turn!");
    ui->stackedWidget->setCurrentIndex(2);
}

void TicTacToe::startGame()
{

}

void TicTacToe::checkValid()
{

}
