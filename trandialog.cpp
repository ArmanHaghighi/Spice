#include "trandialog.h"
#include "ui_trandialog.h"

TranDialog::TranDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TranDialog)
{
    ui->setupUi(this);
    connect(ui->okButton,&QPushButton::clicked,this,&TranDialog::accepted);
    connect(ui->cancelButton,&QPushButton::clicked,this,&TranDialog::rejected);
}
TranDialog::~TranDialog()
{
    delete ui;
}
