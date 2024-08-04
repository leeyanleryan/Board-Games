#include "chess_button.h"
#include "chess.h"

ChessButton::ChessButton(QWidget *parent)
    : QPushButton(parent)
{
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
    if (event->button() == Qt::LeftButton && !icon().isNull())
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
        if (!chess || !chess->gameStarted)
        {
            return;
        }

        chess->sourceButton = this;
        isDragging = true;
        QPixmap pixmap = icon().pixmap(iconSize());
        chess->floatingIconLabel->setPixmap(pixmap);
        chess->floatingIconLabel->setFixedSize(pixmap.size());
        QPoint topLeft = chess->sourceButton->geometry().topLeft();
        QPoint eventPos = event->position().toPoint();
        int x = topLeft.x() + eventPos.x() - 35;
        int y = topLeft.y() + eventPos.y() - 35;
        chess->floatingIconLabel->move(x, y);
        chess->floatingIconLabel->raise();
        chess->floatingIconLabel->setVisible(true);
        setIcon(QIcon());

        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
    }
}

void ChessButton::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
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
        if (!chess || !chess->gameStarted)
        {
            return;
        }

        if (chess->floatingIconLabel->isVisible() && chess->sourceButton)
        {
            QPoint topLeft = chess->sourceButton->geometry().topLeft();
            QPoint eventPos = event->position().toPoint();
            int x = topLeft.x() + eventPos.x() - 35;
            int y = topLeft.y() + eventPos.y() - 35;
            chess->floatingIconLabel->move(x, y);
        }
    }
}

void ChessButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
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
        if (!chess || !chess->gameStarted)
        {
            return;
        }

        isDragging = false;

        chess->floatingIconLabel->setVisible(false);
        QApplication::restoreOverrideCursor();

        QPoint topLeft = chess->sourceButton->geometry().topLeft();
        QPoint eventPos = event->position().toPoint();
        int x, y;
        if (eventPos.x() >= 0)
        {
            x = topLeft.x() + 90*(eventPos.x()/90) + 45;
        }
        else
        {
            x = topLeft.x() + 90*(-1 + eventPos.x()/90) + 45;
        }
        if (eventPos.y() >= 0)
        {
            y = topLeft.y() + 90*(eventPos.y()/90) + 45;
        }
        else
        {
            y = topLeft.y() + 90*(-1 + eventPos.y()/90) + 45;
        }

        QPoint targetPoint(x,y);

        //qDebug() << topLeft;
        //qDebug() << eventPos;
        //qDebug() << x << y;

        ChessButton *targetButton = qobject_cast<ChessButton*>(chess->childAt(targetPoint));
        if (targetButton && targetButton != chess->sourceButton)
        {
            targetButton->setIcon(chess->floatingIconLabel->pixmap(Qt::ReturnByValue));
            targetButton->setIconSize(QSize(90, 90));
        }
        else
        {
            chess->sourceButton->setIcon(chess->floatingIconLabel->pixmap(Qt::ReturnByValue));
            chess->sourceButton->setIconSize(QSize(90, 90));
        }

        chess->sourceButton = nullptr;
    }
}
