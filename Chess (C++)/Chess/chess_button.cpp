#include "chess_button.h"
#include "chess.h"

ChessButton::ChessButton(QWidget *parent)
    : QPushButton(parent)
{

}

void ChessButton::mousePressEvent(QMouseEvent *event)
{
    //if (event->button() == Qt::LeftButton) {
    //    dragStartPosition = event->pos();
    //}
    //QPushButton::mousePressEvent(event);
    if (event->button() == Qt::LeftButton && !icon().isNull())
    {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        mimeData->setImageData(icon().pixmap(iconSize()).toImage());
        drag->setMimeData(mimeData);
        drag->setPixmap(icon().pixmap(iconSize()));
        QPoint center = rect().center();
        drag->setHotSpot(center);

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
        if (chess)
        {
            chess->sourceButton = this;
        }

        QIcon currentIcon = icon();
        setIcon(QIcon());

        Qt::DropAction dropAction = drag->exec(Qt::MoveAction);

        if (dropAction != Qt::MoveAction)
        {
            // If the drag operation was not successful, restore the icon
            setIcon(currentIcon);
        }
    }
}

void ChessButton::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    // Set the piece image as mime data
    mimeData->setImageData(this->icon().pixmap(this->iconSize()).toImage());
    drag->setMimeData(mimeData);

    QPixmap pixmap = this->icon().pixmap(this->iconSize());
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());

    // Start the drag
    drag->exec(Qt::MoveAction);
}
