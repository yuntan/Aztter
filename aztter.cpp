#include "helloqt.h"

Aztter::Aztter(QWidget *parent) :
    QObject(parent), ui(new Ui::Aztter)
{
    ui->setupUi(this);
}

Aztter::~Aztter() {
    delete ui;
}

void Aztter::on_button_pressed() {
    return;
}
