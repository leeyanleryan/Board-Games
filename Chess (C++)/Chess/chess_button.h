#ifndef CHESS_BUTTON_H
#define CHESS_BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>
#include <QCursor>
#include <QApplication>

class ChessButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ChessButton(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    bool isDragging;
};

#endif // CHESS_BUTTON_H
