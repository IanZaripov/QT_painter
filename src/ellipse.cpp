#include "figure.h"

FigureType Ellipse::GetFigureType() const{
	return FigureType::Ellipse_;
}

void Ellipse::computeMinAndMax(QMouseEvent* mouse_pos) {
	mx_x = std::max(mouse_pos->x(), first_click.x());
	mx_y = std::max(mouse_pos->y(), first_click.y());
	mn_x = std::min(mouse_pos->x(), first_click.x());
	mn_y = std::min(mouse_pos->y(), first_click.y());
}

void Ellipse::StartDrawFigure(QMouseEvent* mouse_position) {
	first_click = mouse_position->pos();
	computeMinAndMax(mouse_position);
	ellipse.setTopLeft(mouse_position->pos());
	ellipse.setBottomRight(mouse_position->pos());
}

void Ellipse::setMinAndMax() {
	mx_x = ellipse.bottomRight().x();
	mx_y = ellipse.bottomRight().y();
	mn_x = ellipse.topLeft().x();
	mn_y = ellipse.topLeft().y();
}

void Ellipse::UpdateDrawFigure(QMouseEvent* mouse_position) {
	computeMinAndMax(mouse_position);
	ellipse.setTopLeft(QPoint(mn_x, mn_y));
	ellipse.setBottomRight(QPoint(mx_x, mx_y));
}

void Ellipse::DrawFigure(QPainter& painter) {
	painter.drawEllipse(ellipse);
}

void Ellipse::StartMoveFigure(QMouseEvent* mouse_position) {
	pivot_moving_point = mouse_position->pos();
}


void Ellipse::DoMoveFigure(QMouseEvent* mouse_position) {
	QPoint cur_point = mouse_position->pos();
	QPoint dif = cur_point - pivot_moving_point;
	ellipse.moveCenter(ellipse.center() + dif);
	setMinAndMax();
	pivot_moving_point = cur_point;
}

bool Ellipse::isMouseClickInsideFigure(QMouseEvent* mouse_click_pos) const {
	double a = (ellipse.bottomRight().x() - ellipse.bottomLeft().x())/2;
	double b = (ellipse.bottomLeft().y() - ellipse.topLeft().y())/2;
	double the_canonical_equation_of_the_ellipse = (pow((mouse_click_pos->x() - ellipse.center().x()), 2) / pow(a, 2))
		+ (pow((mouse_click_pos->y() - ellipse.center().y()), 2) / pow(b, 2));
	if (the_canonical_equation_of_the_ellipse <= 1.0) {
		return true;
	}
	return false;
	
}


void Ellipse::StartDrawConnection(QMouseEvent* mouse_position) {
	line.setP1(ellipse.center());
	line.setP2(mouse_position->pos());
}

void Ellipse::UpdateDrawConnection(QMouseEvent* mouse_position) {
	line.setP2(mouse_position->pos());
}

QPoint Ellipse::GetLeftTopCorner() const {
	return ellipse.topLeft();
}

QPoint Ellipse::GetBottomRightCorner() const {
	return ellipse.bottomRight();
}

QPoint Ellipse::GetCenter() const {
	return ellipse.center();
}

void Ellipse::DrawConnection(QPainter& painter) {
	painter.drawLine(line);
}

void Ellipse::FinishDrawConnection(std::shared_ptr<Figure>figure) {
	connecting_figure.insert(figure);
}

void Ellipse::RedrawConnection(QPainter& painter) {
	for (const auto& fig : connecting_figure) {
		painter.drawLine(QLine(ellipse.center(), fig->GetCenter()));
	}
}

void Ellipse::RemoveConnectionWithFigure(std::shared_ptr<Figure> figure) {
	if (connecting_figure.find(figure) != connecting_figure.end()) {
		connecting_figure.erase(figure);
	}
}

const std::unordered_set<std::shared_ptr<Figure>>& Ellipse::GetConnectedFigure() {
	return connecting_figure;
}

void Ellipse::setLeftTopCorner(QPoint corner) {
	ellipse.setTopLeft(corner);
}
void Ellipse::setBottomRightCorner(QPoint corner) {
	ellipse.setBottomRight(corner);
	setMinAndMax();
}