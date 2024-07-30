#include "chess.h"
#include "ui_chess.h"
#include "QPushButton"

QMap<QPair<int, int>, QPushButton*> buttonMap;
QString piecesPath;
QString boardPath;
QString soundPath;
int turn;

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
    // default
    piecesPath = "Pieces/Neo/";
    boardPath = "Board/Brown/";
    soundPath = "Sound/Default/";
    setupButtonMap();
}

Chess::~Chess()
{
    delete ui;
}

void Chess::setButtonIcon(QPushButton *button, const QString &imagePath)
{
    if (!button) {
        qDebug() << "Button is nullptr";
        return;
    }

    if (imagePath.isEmpty()) {
        qDebug() << "Image path is empty";
        return;
    }
    qDebug() << button->objectName();
    QIcon icon(imagePath);
    button->setIcon(icon);
    button->setIconSize(button->size()); // Adjust the icon size to the button size
}

void Chess::setupButtonMap() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QString buttonName = QString("pushButton_%1").arg(row * 8 + col + 1);
            QPushButton *button = findChild<QPushButton*>(buttonName);
            if (button) {
                buttonMap[qMakePair(row, col)] = button;
            }
        }
    }
}

void Chess::on_test_clicked()
{
    setButtonIcon(buttonMap[{0, 0}], piecesPath + "KingWhite.png");
}

