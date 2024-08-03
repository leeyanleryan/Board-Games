#include "chess_button.h"

ChessButton::ChessButton(QWidget *parent)
    : QPushButton(parent)
{

}

void ChessButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    }
    QPushButton::mousePressEvent(event);
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
