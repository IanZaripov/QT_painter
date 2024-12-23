#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "Design_window.h"
#include <memory>
#include <QMouseEvent>
#include <QPainter>
#include <unordered_set>
#include <unordered_map>
#include <QWidget>
#include "figure.h"
#include <QFileDialog>
#include <fstream>
#include <string>

namespace Ui {
    class lineWidget;
}

class lineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit lineWidget(QWidget* parent = 0);
    bool mouseRightButtonPressed;
    bool mouseWasPressedInFigureArea;
    bool firstcleack;
    enum selectTool {
        Ffigure = 1,
        Connection = 2,
        Move = 3,
        Remove = 4
    };
    enum selectFigure {
        Rectangle = 1,
        Ellipse = 2,
        Triangle = 3
    };
    ~lineWidget();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    FigureType convert(selectFigure selectfigure);
    std::shared_ptr<Figure> FindClosestFigure(QMouseEvent* event);
    void ChangeStyleSheet();
    void parseAndSetCondition(std::ifstream& inpt);

private slots:
    void on_Rectangle_clicked();
    void on_Triangle_clicked();
    void on_Ellipse_clicked();
    void on_Connection_clicked();
    void on_Move_clicked();
    void on_Remove_clicked();
    void on_Load_clicked();
    void on_Save_clicked();
    

private:
    Ui::lineWidget* ui;
    QPainter painter;
    QPixmap mPix;
    selectTool selecttool;
    selectFigure selectfigure;
    QPoint mouseClickPos;
};
#endif
