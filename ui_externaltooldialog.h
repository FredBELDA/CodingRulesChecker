/********************************************************************************
** Form generated from reading UI file 'externaltooldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTERNALTOOLDIALOG_H
#define UI_EXTERNALTOOLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExternalToolDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_ExcelPath;

    void setupUi(QDialog *ExternalToolDialog)
    {
        if (ExternalToolDialog->objectName().isEmpty())
            ExternalToolDialog->setObjectName(QStringLiteral("ExternalToolDialog"));
        ExternalToolDialog->resize(400, 300);
        verticalLayoutWidget = new QWidget(ExternalToolDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_ExcelPath = new QLabel(verticalLayoutWidget);
        label_ExcelPath->setObjectName(QStringLiteral("label_ExcelPath"));

        verticalLayout->addWidget(label_ExcelPath);


        retranslateUi(ExternalToolDialog);

        QMetaObject::connectSlotsByName(ExternalToolDialog);
    } // setupUi

    void retranslateUi(QDialog *ExternalToolDialog)
    {
        ExternalToolDialog->setWindowTitle(QApplication::translate("ExternalToolDialog", "Dialog", 0));
        label_ExcelPath->setText(QApplication::translate("ExternalToolDialog", "Veuillez renseigner le chemin vers Excel :", 0));
    } // retranslateUi

};

namespace Ui {
    class ExternalToolDialog: public Ui_ExternalToolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTERNALTOOLDIALOG_H
