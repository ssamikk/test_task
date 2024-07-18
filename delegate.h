#ifndef DELEGATE_H
#define DELEGATE_H

#include <QWidget>

namespace Ui {
class Delegate;
}

class Delegate : public QWidget
{
    Q_OBJECT

public:
    explicit Delegate(QWidget *parent = 0);
    ~Delegate();

    bool getValue() const;
    void setValue(bool value);

private slots:
    void on_pushButton_clicked();
private:
    Ui::Delegate *ui;
    bool value;
};

#endif // DELEGATE_H
