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

    void startGame();

    void checkValid();

    void on_buttonPlayFriend_clicked();

    void on_buttonGameBack_clicked();

    void on_buttonPlayAI_clicked();

private:
    Ui::TicTacToe *ui;
};
#endif // TICTACTOE_H
