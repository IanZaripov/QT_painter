#pragma once

#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <QRect>
#include <QMouseEvent>
#include <unordered_set>

enum class FigureType {
    Rectangle_,
    Triangle_,
    Ellipse_
};

class Figure {
public:
    virtual void StartDrawFigure(QMouseEvent* mouse_position) = 0;
    virtual void UpdateDrawFigure(QMouseEvent* mouse_position) = 0;
    virtual void DrawFigure(QPainter& painter) = 0;

    virtual void StartDrawConnection(QMouseEvent* mouse_position) = 0;
    virtual void UpdateDrawConnection(QMouseEvent* mouse_position) = 0;
    virtual void DrawConnection(QPainter& painter) = 0;
    virtual void FinishDrawConnection(std::shared_ptr<Figure>figure)= 0;
    virtual void RedrawConnection(QPainter& painter)= 0;
    virtual void RemoveConnectionWithFigure(std::shared_ptr<Figure> figure) = 0;

    virtual bool isMouseClickInsideFigure(QMouseEvent* mouse_position) const = 0;
    virtual void StartMoveFigure(QMouseEvent* mouse_position) = 0;
    virtual void DoMoveFigure(QMouseEvent* mouse_position) = 0;

    virtual QPoint GetCenter() const = 0;
    virtual QPoint GetLeftTopCorner() const = 0;
    virtual QPoint GetBottomRightCorner() const = 0;
    virtual const std::unordered_set<std::shared_ptr<Figure>>& GetConnectedFigure() = 0;

    virtual void computeMinAndMax(QMouseEvent* mouse_pos) = 0;
    virtual void setLeftTopCorner(QPoint corner) = 0;
    virtual void setBottomRightCorner(QPoint corner) = 0;
    virtual void setMinAndMax() = 0;
    virtual FigureType GetFigureType() const = 0;
    QPoint first_click;
    QPoint pivot_moving_point;
};

class Rectangle : public Figure {
public:
    void StartDrawFigure(QMouseEvent* mouse_position);
    void UpdateDrawFigure(QMouseEvent* mouse_position);
    void DrawFigure(QPainter& painter);

    void StartDrawConnection(QMouseEvent* mouse_position);
    void UpdateDrawConnection(QMouseEvent* mouse_position);
    void DrawConnection(QPainter& painter);
    void FinishDrawConnection(std::shared_ptr<Figure>figure);
    void RedrawConnection(QPainter& painter);
    void RemoveConnectionWithFigure(std::shared_ptr<Figure> figure);

    bool isMouseClickInsideFigure(QMouseEvent* mouse_position) const;
    void StartMoveFigure(QMouseEvent* mouse_position);
    void DoMoveFigure(QMouseEvent* mouse_position);

    QPoint GetCenter() const;
    QPoint GetLeftTopCorner() const;
    QPoint GetBottomRightCorner() const;
    const std::unordered_set<std::shared_ptr<Figure>>& GetConnectedFigure();

    void setLeftTopCorner(QPoint corner);
    void setBottomRightCorner(QPoint corner);
    void computeMinAndMax(QMouseEvent* mouse_pos);
    void setMinAndMax();
    FigureType GetFigureType() const;
private:
    QRect rect;
    QLine line;
    std::unordered_set<std::shared_ptr<Figure>> connecting_figure;
    int mn_x = 0;
    int mn_y = 0;
    int mx_x = 0;
    int mx_y = 0;
};


class Ellipse : public Figure {
public:
    void StartDrawFigure(QMouseEvent* mouse_position);
    void UpdateDrawFigure(QMouseEvent* mouse_position);
    void DrawFigure(QPainter& painter);

    void StartDrawConnection(QMouseEvent* mouse_position);
    void UpdateDrawConnection(QMouseEvent* mouse_position);
    void DrawConnection(QPainter& painter);
    void FinishDrawConnection(std::shared_ptr<Figure>figure);
    void RedrawConnection(QPainter& painter);
    void RemoveConnectionWithFigure(std::shared_ptr<Figure> figure);

    bool isMouseClickInsideFigure(QMouseEvent* mouse_click_pos) const;
    void StartMoveFigure(QMouseEvent* mouse_position);
    void DoMoveFigure(QMouseEvent* mouse_position);

    QPoint GetCenter() const;
    QPoint GetLeftTopCorner() const;
    QPoint GetBottomRightCorner() const;
    const std::unordered_set<std::shared_ptr<Figure>>& GetConnectedFigure();

    void setLeftTopCorner(QPoint corner);
    void setBottomRightCorner(QPoint corner);
    void computeMinAndMax(QMouseEvent* mouse_pos);
    void setMinAndMax();
    FigureType GetFigureType() const;
private:
    QRect ellipse;
    QLine line;
    std::unordered_set<std::shared_ptr<Figure>> connecting_figure;
    int mn_x = 0;
    int mn_y = 0;
    int mx_x = 0;
    int mx_y = 0;
};

class Triangle : public Figure {
public:
    void StartDrawFigure(QMouseEvent* mouse_position);
    void UpdateDrawFigure(QMouseEvent* mouse_position);
    void DrawFigure(QPainter& painter);

    void StartDrawConnection(QMouseEvent* mouse_position);
    void UpdateDrawConnection(QMouseEvent* mouse_position);
    void DrawConnection(QPainter& painter);
    void FinishDrawConnection(std::shared_ptr<Figure>figure);
    void RemoveConnectionWithFigure(std::shared_ptr<Figure> figure);
    void RedrawConnection(QPainter& painter);

    bool isMouseClickInsideFigure(QMouseEvent* mouse_click_pos) const;
    void StartMoveFigure(QMouseEvent* mouse_position);
    void DoMoveFigure(QMouseEvent* mouse_position);

    QPoint GetLeftTopCorner() const;
    QPoint GetBottomRightCorner() const;
    QPoint GetCenter() const;
    const std::unordered_set<std::shared_ptr<Figure>>& GetConnectedFigure();

    void setLeftTopCorner(QPoint corner);
    void setBottomRightCorner(QPoint corner);
    void computeMinAndMax(QMouseEvent* mouse_pos);
    void setMinAndMax();
    FigureType GetFigureType() const;
private:
    QPointF triangle[4];
    QRect frame;
    QLine line;
    std::unordered_set<std::shared_ptr<Figure>> connecting_figure;
    int mn_x = 0;
    int mn_y = 0;
    int mx_x = 0;
    int mx_y = 0;
};


std::shared_ptr<Figure> build_figure(FigureType type);

#endif
