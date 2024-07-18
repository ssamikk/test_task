#include "delegate.h"
#include "ui_delegate.h"

Delegate::Delegate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Delegate)
{
    ui->setupUi(this);
    ui->pushButton->setFocus();
}

Delegate::~Delegate()
{
    delete ui;
}

void Delegate::on_pushButton_clicked()
{
    value = !value;
    ui->pushButton->setIcon(QIcon(value ? ":/img/visible.png" : ":/img/unvisible.png"));
}

bool Delegate::getValue() const
{
    return value;
}

void Delegate::setValue(bool value)
{
    this->value = value;
    ui->pushButton->setIcon(QIcon(this->value ? ":/img/visible.png" : ":/img/unvisible.png"));
}
