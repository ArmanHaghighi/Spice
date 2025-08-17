/********************************************************************************
** Form generated from reading UI file 'properties.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIES_H
#define UI_PROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Properties
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Name;
    QLineEdit *NameTxt;
    QLabel *Value;
    QLineEdit *ValTxt;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Properties)
    {
        if (Properties->objectName().isEmpty())
            Properties->setObjectName(QString::fromUtf8("Properties"));
        Properties->resize(383, 171);
        verticalLayout = new QVBoxLayout(Properties);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Name = new QLabel(Properties);
        Name->setObjectName(QString::fromUtf8("Name"));

        verticalLayout->addWidget(Name);

        NameTxt = new QLineEdit(Properties);
        NameTxt->setObjectName(QString::fromUtf8("NameTxt"));

        verticalLayout->addWidget(NameTxt);

        Value = new QLabel(Properties);
        Value->setObjectName(QString::fromUtf8("Value"));

        verticalLayout->addWidget(Value);

        ValTxt = new QLineEdit(Properties);
        ValTxt->setObjectName(QString::fromUtf8("ValTxt"));

        verticalLayout->addWidget(ValTxt);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(Properties);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Properties);
        QObject::connect(buttonBox, SIGNAL(accepted()), Properties, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Properties, SLOT(reject()));

        QMetaObject::connectSlotsByName(Properties);
    } // setupUi

    void retranslateUi(QDialog *Properties)
    {
        Properties->setWindowTitle(QCoreApplication::translate("Properties", "Dialog", nullptr));
        Name->setText(QCoreApplication::translate("Properties", "Name", nullptr));
        Value->setText(QCoreApplication::translate("Properties", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Properties: public Ui_Properties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIES_H
