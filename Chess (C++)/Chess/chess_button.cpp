#include "chess_button.h"
#include "chess.h"
#include "chess_logic.h"

Chess *chess;

ChessButton::ChessButton(QWidget *parent)
    : QPushButton(parent)
{
    chess = nullptr;
    isDragging = false;
}

void ChessButton::enterEvent(QEnterEvent *event)
{
    if (!icon().isNull())
    {
        QApplication::setOverrideCursor(Qt::OpenHandCursor);
        QPushButton::enterEvent(event);
    }
}

void ChessButton::leaveEvent(QEvent *event)
{
    QApplication::restoreOverrideCursor();
    QPushButton::leaveEvent(event);
}

void ChessButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto start = std::chrono::high_resolution_clock::now();

        chess = nullptr;
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
        if (!chess || !chess->gameStarted)
        {
            return;
        }
        if (chess->choosingPromotedPiece || icon().isNull())
        {
            chess->deselectButton(this);
            return;
        }

        QPair<int, int> sourceCoord = chess->notationCoordinateMap[objectName()];
        if (chess->legalMoves.contains(sourceCoord))
        {
            chess->makeMove(this);
            auto end = std::chrono::high_resolution_clock::now();
            chess->timeTakenToMove = (end-start);
            return;
        }

        isDragging = true;

        QPixmap pixmap = icon().pixmap(iconSize());
        chess->floatingIconLabel->setPixmap(pixmap);
        chess->floatingIconLabel->setFixedSize(pixmap.size());
        setIcon(QIcon());

        QPoint topLeft = this->geometry().topLeft();
        QPoint eventPos = event->position().toPoint();
        QPoint uiBoardTopLeft = chess->uiBoardTopLeft;
        int x = (uiBoardTopLeft.x()-10) + topLeft.x() + eventPos.x() - 35;
        int y = (uiBoardTopLeft.y()-10) + topLeft.y() + eventPos.y() - 35;
        chess->floatingIconLabel->move(x, y);
        chess->floatingIconLabel->raise();
        chess->floatingIconLabel->setVisible(true);

        chess->showLegalMoves(this);
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);

        auto end = std::chrono::high_resolution_clock::now();
        chess->timeTakenToMove = (end-start);
    }
}

void ChessButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!isDragging)
    {
        return;
    }

    if (chess->floatingIconLabel->isVisible())
    {
        QPoint topLeft = this->geometry().topLeft();
        QPoint eventPos = event->position().toPoint();
        QPoint uiBoardTopLeft = chess->uiBoardTopLeft;
        int x = (uiBoardTopLeft.x()-10) + topLeft.x() + eventPos.x() - 35;
        int y = (uiBoardTopLeft.y()-10) + topLeft.y() + eventPos.y() - 35;
        chess->floatingIconLabel->move(x, y);
    }
}

void ChessButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        if (event->button() == Qt::LeftButton)
        {
            auto start = std::chrono::high_resolution_clock::now();

            isDragging = false;

            QPoint topLeft = this->geometry().topLeft();
            QPoint eventPos = event->position().toPoint();
            QPoint uiBoardTopLeft = chess->uiBoardTopLeft;
            int x = (uiBoardTopLeft.x()-10) + topLeft.x() + 90 * (eventPos.x() >= 0 ? eventPos.x() / 90 : -1 + eventPos.x() / 90) + 45;
            int y = (uiBoardTopLeft.y()-10) + topLeft.y() + 90 * (eventPos.y() >= 0 ? eventPos.y() / 90 : -1 + eventPos.y() / 90) + 45;
            ChessButton *targetButton = qobject_cast<ChessButton*>(chess->childAt(QPoint(x, y)));

            chess->floatingIconLabel->setVisible(false);

            if (!targetButton)
            {
                this->setIcon(chess->floatingIconLabel->pixmap(Qt::ReturnByValue));
                this->setIconSize(QSize(90, 90));
                return;
            }

            chess->makeMove(this, targetButton);
            QApplication::restoreOverrideCursor();

            auto end = std::chrono::high_resolution_clock::now();
            chess->timeTakenToMove += (end-start);
        }
    }
}
