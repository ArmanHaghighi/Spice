/********************************************************************************
** Form generated from reading UI file 'addelementdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDELEMENTDIALOG_H
#define UI_ADDELEMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_AddElementDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddElementDialog)
    {
        if (AddElementDialog->objectName().isEmpty())
            AddElementDialog->setObjectName(QString::fromUtf8("AddElementDialog"));
        AddElementDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(AddElementDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 250, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(AddElementDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddElementDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddElementDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddElementDialog);
    } // setupUi

    void retranslateUi(QDialog *AddElementDialog)
    {
        AddElementDialog->setWindowTitle(QCoreApplication::translate("AddElementDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddElementDialog: public Ui_AddElementDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDELEMENTDIALOG_H
