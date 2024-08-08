#ifndef CHESS_PROMOTION_BUTTON_H
#define CHESS_PROMOTION_BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>
#include <QCursor>
#include <QApplication>

class ChessPromotionButton : public QPushButton
{
    Q_OBJECT

public:
    char chessPiece;

    ChessPromotionButton(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CHESS_PROMOTION_BUTTON_H
