#include "chess_button.h"
#include "chess.h"

ChessButton::ChessButton(QWidget *parent)
    : QPushButton(parent)
{

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

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        mimeData->setImageData(icon().pixmap(iconSize()).toImage());
        drag->setMimeData(mimeData);
        drag->setPixmap(icon().pixmap(iconSize()));
        drag->setHotSpot(rect().center());

        QIcon currentIcon = icon();
        setIcon(QIcon());

        Qt::DropAction dropAction = drag->exec(Qt::MoveAction);

        if (dropAction != Qt::MoveAction)
        {
            setIcon(currentIcon);
        }
    }
}
