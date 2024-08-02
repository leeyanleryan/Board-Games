#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Chess;
}
QT_END_NAMESPACE

class Chess : public QMainWindow
{
    Q_OBJECT

public:
    Chess(QWidget *parent = nullptr);
    ~Chess();

private slots:
    void launchSetup();

    void setDefaultBoard();

    void setButtonPositionMap();

    void setPiecePositionMap();

    void setPieceImageMap();

    void setButtonPiece(QPushButton *button, const QString &imagePath);

    void setButtonBoard(QPushButton *button, const QString &imagePath);

    void setChessBoard();

    void setMenu();

    void on_buttonPlayComputer_clicked();

    void on_buttonComputerEasy_clicked();

    void on_buttonComputerMedium_clicked();

    void on_buttonComputerHard_clicked();

    void on_buttonComputerImpossible_clicked();

    void on_buttonComputerNext_clicked();

    void on_buttonComputerBack_clicked();

    void on_buttonP1First_clicked();

    void on_buttonP2First_clicked();

    void on_buttonRandomFirst_clicked();

    void on_buttonAlternateFirst_clicked();

    void on_buttonPlay_clicked();

    void on_buttonGoesFirstBack_clicked();

    void on_buttonPlayFriend_clicked();

    void on_lineP1Name_editingFinished();

    void on_lineP2Name_editingFinished();

    void on_buttonFriendNext_clicked();

    void on_buttonFriendBack_clicked();

    void on_buttonSettings_clicked();

    void on_buttonSettingsBack_clicked();

private:
    Ui::Chess *ui;
};
#endif // CHESS_H
