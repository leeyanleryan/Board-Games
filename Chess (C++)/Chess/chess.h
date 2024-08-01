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
    void setDefaultBoard();

    void setButtonPositionMap();

    void setPiecePositionMap();

    void setPieceImageMap();

    void setButtonPiece(QPushButton *button, const QString &imagePath);

    void setButtonBoard(QPushButton *button, const QString &imagePath);

    void setChessBoard();

private:
    Ui::Chess *ui;
};
#endif // CHESS_H
