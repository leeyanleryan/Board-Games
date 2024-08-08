#include "chess_promotion_button.h"
#include "chess.h"

//Chess *chess;

ChessPromotionButton::ChessPromotionButton(QWidget *parent)
    : QPushButton(parent)
{
    //chess = nullptr;
}

void ChessPromotionButton::enterEvent(QEnterEvent *event)
{
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    QPushButton::enterEvent(event);
}

void ChessPromotionButton::leaveEvent(QEvent *event)
{
    QApplication::restoreOverrideCursor();
    QPushButton::leaveEvent(event);
}

void ChessPromotionButton::mousePressEvent(QMouseEvent *event)
{
    Chess *chess = nullptr;
    QWidget *pw = parentWidget();
    while (pw)
    {
        chess = qobject_cast<Chess*>(pw);
        if (chess)
        {
            break;
        }
        pw = pw->parentWidget();
    }
    if (!chess || !chess->gameStarted || !chess->choosingPromotedPiece)
    {
        return;
    }

    chess->chosenPromotionPiece(chessPiece);
}
