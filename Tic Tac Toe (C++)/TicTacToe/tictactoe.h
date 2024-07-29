#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToe; }
QT_END_NAMESPACE

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    void on_playAI_clicked();

    void on_playFriend_clicked();

    void on_buttonFriendBack_clicked();

    void on_buttonAIBack_clicked();

    void on_buttonPlayFriend_clicked();

    void on_buttonGameBack_clicked();

    void on_buttonPlayAI_clicked();

    int checkWin();

    void clearBoard();

    void setBoardEnabled(bool arg);

    void clearWins();

    void makeMoveAI();

    void gridButtonClicked();

    void on_buttonTTT1_clicked();

    void on_buttonTTT2_clicked();

    void on_buttonTTT3_clicked();

    void on_buttonTTT4_clicked();

    void on_buttonTTT5_clicked();

    void on_buttonTTT6_clicked();

    void on_buttonTTT7_clicked();

    void on_buttonTTT8_clicked();

    void on_buttonTTT9_clicked();

    void on_buttonNewGame_clicked();

private:
    Ui::TicTacToe *ui;
};
#endif // TICTACTOE_H
