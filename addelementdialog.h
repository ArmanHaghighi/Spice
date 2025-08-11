#ifndef ADDELEMENTDIALOG_H
#define ADDELEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddElementDialog;
}

class AddElementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddElementDialog(QWidget *parent = nullptr);
    ~AddElementDialog();

private:
    Ui::AddElementDialog *ui;
};

#endif // ADDELEMENTDIALOG_H
