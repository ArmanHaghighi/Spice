/********************************************************************************
** Form generated from reading UI file 'trandialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
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
    QHBoxLayout *horizontalLayout;
    QLabel *startTime;
    QLineEdit *inputStart;
    QHBoxLayout *horizontalLayout_3;
    QLabel *maxTime;
    QLineEdit *inputStep;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *stopTime;
    QLineEdit *inputStop;

    void setupUi(QDialog *TranDialog)
    {
        if (TranDialog->objectName().isEmpty())
            TranDialog->setObjectName(QString::fromUtf8("TranDialog"));
        TranDialog->resize(600, 414);
        gridLayout = new QGridLayout(TranDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        startTime = new QLabel(TranDialog);
        startTime->setObjectName(QString::fromUtf8("startTime"));

        horizontalLayout->addWidget(startTime);

        inputStart = new QLineEdit(TranDialog);
        inputStart->setObjectName(QString::fromUtf8("inputStart"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputStart->sizePolicy().hasHeightForWidth());
        inputStart->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(inputStart);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        maxTime = new QLabel(TranDialog);
        maxTime->setObjectName(QString::fromUtf8("maxTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(maxTime->sizePolicy().hasHeightForWidth());
        maxTime->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(maxTime);

        inputStep = new QLineEdit(TranDialog);
        inputStep->setObjectName(QString::fromUtf8("inputStep"));
        sizePolicy.setHeightForWidth(inputStep->sizePolicy().hasHeightForWidth());
        inputStep->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(inputStep);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(239, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        okButton = new QPushButton(TranDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_4->addWidget(okButton);

        cancelButton = new QPushButton(TranDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_4->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout_4, 3, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        stopTime = new QLabel(TranDialog);
        stopTime->setObjectName(QString::fromUtf8("stopTime"));

        horizontalLayout_2->addWidget(stopTime);

        inputStop = new QLineEdit(TranDialog);
        inputStop->setObjectName(QString::fromUtf8("inputStop"));
        sizePolicy.setHeightForWidth(inputStop->sizePolicy().hasHeightForWidth());
        inputStop->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(inputStop);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);


        retranslateUi(TranDialog);

        QMetaObject::connectSlotsByName(TranDialog);
    } // setupUi

    void retranslateUi(QDialog *TranDialog)
    {
        TranDialog->setWindowTitle(QCoreApplication::translate("TranDialog", "Dialog", nullptr));
        startTime->setText(QCoreApplication::translate("TranDialog", "Time to start saving data:", nullptr));
        maxTime->setText(QCoreApplication::translate("TranDialog", "Maximum timestep:", nullptr));
        okButton->setText(QCoreApplication::translate("TranDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("TranDialog", "Cancel", nullptr));
        stopTime->setText(QCoreApplication::translate("TranDialog", "Stop Time:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TranDialog: public Ui_TranDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANDIALOG_H
