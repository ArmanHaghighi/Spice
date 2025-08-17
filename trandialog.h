#ifndef TRANDIALOG_H
#define TRANDIALOG_H

#include <QDialog>
namespace Ui {
class TranDialog;
}

class TranDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TranDialog(QWidget *parent = nullptr);
    ~TranDialog();

    Ui::TranDialog *ui;
};

#endif // TRANDIALOG_H
