#pragma once
#ifndef DESIGN_WINDOW_H
#define DESIGN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
// #include <QtWidgets/QAction>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_lineWidget
{
public:
    QWidget* widget;
    QHBoxLayout* horizontalLayout;
    QPushButton* Rectangle;
    QPushButton* Triangle;
    QPushButton* Ellipse;
    QPushButton* Connection;
    QPushButton* Move;
    QPushButton* Remove;
    QPushButton* Load;
    QPushButton* Save;

    void setupUi(QWidget* lineWidget)
    {
        if (lineWidget->objectName().isEmpty())
                    lineWidget->setObjectName(QStringLiteral("MainWindow"));
        lineWidget->resize(800, 600);
        widget = new QWidget(lineWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 2, 2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        Rectangle = new QPushButton(widget);
        Rectangle->setObjectName(QStringLiteral("Rectangle"));
        horizontalLayout->addWidget(Rectangle);

        Triangle = new QPushButton(widget);
        Triangle->setObjectName(QStringLiteral("Triangle"));
        horizontalLayout->addWidget(Triangle);

        Ellipse = new QPushButton(widget);
        Ellipse->setObjectName(QStringLiteral("Ellipse"));
        horizontalLayout->addWidget(Ellipse);

        Connection = new QPushButton(widget);
        Connection->setObjectName(QStringLiteral("Connection"));
        horizontalLayout->addWidget(Connection);

        Move = new QPushButton(widget);
        Move->setObjectName(QStringLiteral("Move"));
        horizontalLayout->addWidget(Move);

        Remove = new QPushButton(widget);
        Remove->setObjectName(QStringLiteral("Remove"));
        horizontalLayout->addWidget(Remove);

        Load = new QPushButton(widget);
        Load->setObjectName(QStringLiteral("Load"));
        horizontalLayout->addWidget(Load);

        Save = new QPushButton(widget);
        Save->setObjectName(QStringLiteral("Save"));
        horizontalLayout->addWidget(Save);

        retranslateUi(lineWidget);

        QMetaObject::connectSlotsByName(lineWidget);
    } // setupUi

    void retranslateUi(QWidget *lineWidget)
    {
        lineWidget->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        
        Rectangle->setText(QApplication::translate("MainWindow", "Rectangle", 0));
        Triangle->setText(QApplication::translate("MainWindow", "Triangle", 0));
        Ellipse->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        Connection->setText(QApplication::translate("MainWindow", "Connection", 0));
        Move->setText(QApplication::translate("MainWindow", "Move", 0));
        Remove->setText(QApplication::translate("MainWindow", "Remove", 0));
        Load->setText(QApplication::translate("MainWindow", "Load", 0));
        Save->setText(QApplication::translate("MainWindow", "Save", 0));
    } // retranslateUi

};


namespace Ui {
    class lineWidget: public Ui_lineWidget {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H


