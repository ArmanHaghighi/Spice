/********************************************************************************
** Form generated from reading UI file 'trandialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANDIALOG_H
#define UI_TRANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_TranDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *TranDialog)
    {
        if (TranDialog->objectName().isEmpty())
            TranDialog->setObjectName("TranDialog");
        TranDialog->resize(306, 165);
        gridLayout = new QGridLayout(TranDialog);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(TranDialog);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(TranDialog);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(TranDialog);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(TranDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);


        retranslateUi(TranDialog);

        QMetaObject::connectSlotsByName(TranDialog);
    } // setupUi

    void retranslateUi(QDialog *TranDialog)
    {
        TranDialog->setWindowTitle(QCoreApplication::translate("TranDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("TranDialog", "TextLabel", nullptr));
        okButton->setText(QCoreApplication::translate("TranDialog", "PushButton", nullptr));
        cancelButton->setText(QCoreApplication::translate("TranDialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TranDialog: public Ui_TranDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANDIALOG_H
