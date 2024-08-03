#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "chess_ai.h"

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
    void variableSetup();

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

    void on_buttonComputerEasy_pressed();

    void on_buttonComputerMedium_pressed();

    void on_buttonComputerHard_pressed();

    void on_buttonComputerImpossible_pressed();

    void on_buttonComputerNext_clicked();

    void on_buttonComputerBack_clicked();

    void on_buttonP1First_pressed();

    void on_buttonP2First_pressed();

    void on_buttonRandomFirst_pressed();

    void on_buttonAlternateFirst_pressed();

    void on_buttonGoesFirstBack_clicked();

    void on_buttonPlayFriend_clicked();

    void on_lineP1Name_editingFinished();

    void on_lineP2Name_editingFinished();

    void on_buttonFriendNext_clicked();

    void on_buttonFriendBack_clicked();

    void on_buttonSettings_clicked();

    void on_buttonSettingsBack_clicked();

    void on_buttonExit_clicked();

    void on_buttonChessQuit_clicked();

    void on_buttonPlay_clicked();

    void newGame();

    void autoScroll();

    void addMove(const QString &move);

    void on_a1_clicked();

    void on_b1_clicked();

    void on_c1_clicked();

private:
    Ui::Chess *ui;
    ChessAI *ai;

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
    std::vector<QString> playerNames;
    bool chosenFirst;
    bool randomTurn;
    bool alternateTurns;
    int computerDifficulty;
    bool gameStarted;
    int gameNumber;
    int turn;
    int moveNumber;
    QList<QLabel*> moveLabels;
    QVBoxLayout *scrollLayout;
};

#endif // CHESS_H
