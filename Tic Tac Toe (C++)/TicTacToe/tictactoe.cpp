#include "tictactoe.h"
#include "ui_tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
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
    ui->stackedWidget->setCurrentIndex(2);
}

void TicTacToe::on_buttonGameBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void TicTacToe::on_buttonPlayAI_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void TicTacToe::startGame()
{

}

void TicTacToe::checkValid()
{

}
