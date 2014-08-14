#include "options.h"
#include "ui_options.h"

extern int tsize;

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    ui->spinBox->setRange(8,20);
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_clicked()
{
    this->close();
    return;
}

void Options::on_pushButton_2_clicked()
{
    tsize=ui->spinBox->value();
    this->close();
}
