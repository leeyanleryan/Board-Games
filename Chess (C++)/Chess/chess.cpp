#include "chess.h"
#include "ui_chess.h"

Chess::Chess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chess)
{
    ui->setupUi(this);
}

Chess::~Chess()
{
    delete ui;
}
