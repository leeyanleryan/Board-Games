#ifndef CHESS_BUTTON_H
#define CHESS_BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

class ChessButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ChessButton(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPosition;

    bool isDragging;
};

#endif // CHESS_BUTTON_H
