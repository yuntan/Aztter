#ifndef AZTTER_H
#define AZTTER_H
#include <QObject>

namespace Ui {
class Aztter;
}

class Aztter : public QObject
{
Q_OBJECT

public:
    explicit Aztter(QWidget *parent = 0);
    ~Aztter();

private slots:
    void on_button_pressed();

private:
    Ui::Aztter *ui;
    QObject root, label;
};

#endif // AZTTER_H
