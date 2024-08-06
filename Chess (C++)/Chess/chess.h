#ifndef CHESS_H
#define CHESS_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSet>
#include "chess_ai.h"
#include "chess_button.h"
#include "chess_logic.h"

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

    ChessLogic *logic;

    QMap<QString, QPair<int, int>> coordinatePositionMap;
    QLabel *floatingIconLabel;
    bool gameStarted;
    QSet<QPair<int, int>> legalMoves;

    void showLegalMoves(ChessButton *sourceButton);

    void makeMove(ChessButton *targetButton);

    void makeMove(ChessButton *sourceButton, ChessButton *targetButton);

private slots:
    void variableSetup();

    void launchSetup();

    void setDefaultBoard();

    void setButtonPositionMap();

    void setPiecePositionMap();

    void setPieceImageMap();

    void setButtonIcon(QPushButton *button, const QString &imagePath);

    void setButtonStyleSheet(QPushButton *button, const QString &imagePath);

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

    void showLegalMoveImages();

    void hideLegalMoveImages();

    void resetButtonStyleSheet(ChessButton *button);

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
    std::array<QString, 2> playerNames;
    bool chosenFirst;
    bool randomTurn;
    bool alternateTurns;
    int computerDifficulty;
    int gameNumber;
    int aiTurn;
    int turn;
    int moveNumber;
    QList<QLabel*> moveLabels;
    QVBoxLayout *scrollLayout;

    ChessButton *prevMovedSourceButton;
    ChessButton *prevMovedTargetButton;
    ChessButton *prevClickedSourceButton;
    int prevSourceButtonClicks;
    bool moveIsIllegal;
};

#endif // CHESS_H
