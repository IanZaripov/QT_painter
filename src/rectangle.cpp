#include "figure.h"

FigureType Rectangle::GetFigureType() const{
	return FigureType::Rectangle_;
}

void Rectangle::computeMinAndMax(QMouseEvent* mouse_pos) {
	mx_x = std::max(mouse_pos->x(), first_click.x());
	mx_y = std::max(mouse_pos->y(), first_click.y());
	mn_x = std::min(mouse_pos->x(), first_click.x());
	mn_y = std::min(mouse_pos->y(), first_click.y());
}

void Rectangle::setMinAndMax() {
	mx_x = rect.bottomRight().x();
	mx_y = rect.bottomRight().y();
	mn_x = rect.topLeft().x();
	mn_y = rect.topLeft().y();
}

void Rectangle::StartDrawFigure(QMouseEvent* mouse_position) {
	first_click = mouse_position->pos();
	computeMinAndMax(mouse_position);
	rect.setTopLeft(mouse_position->pos());
	rect.setBottomRight(mouse_position->pos());
}

void Rectangle::UpdateDrawFigure(QMouseEvent* mouse_position) {
	computeMinAndMax(mouse_position);
	rect.setTopLeft(QPoint(mn_x, mn_y));
	rect.setBottomRight(QPoint(mx_x, mx_y));
}

void Rectangle::DrawFigure(QPainter& painter) {
	painter.drawRect(rect);
}

void Rectangle::StartMoveFigure(QMouseEvent* mouse_position) {
	pivot_moving_point = mouse_position->pos();
}


void Rectangle::DoMoveFigure(QMouseEvent* mouse_position) {
	QPoint cur_point = mouse_position->pos();
	QPoint dif = cur_point - pivot_moving_point;
	rect.moveCenter(rect.center() + dif);
	setMinAndMax();
	pivot_moving_point = cur_point;
}

bool Rectangle::isMouseClickInsideFigure(QMouseEvent* mouse_click_pos) const {
	if (mouse_click_pos->x() <= mx_x && mouse_click_pos->y() <= mx_y &&
		mouse_click_pos->x() >= mn_x && mouse_click_pos->y() >= mn_y) {
		return true;
	}
	return false;
}


void Rectangle::StartDrawConnection(QMouseEvent* mouse_position) {
	line.setP1(rect.center());
	line.setP2(mouse_position->pos());
}

void Rectangle::UpdateDrawConnection(QMouseEvent* mouse_position) {
	line.setP2(mouse_position->pos());
}


void Rectangle::DrawConnection(QPainter& painter) {
	painter.drawLine(line);
}

void Rectangle::FinishDrawConnection(std::shared_ptr<Figure>figure) {
	connecting_figure.insert(figure);
}

void Rectangle::RedrawConnection(QPainter& painter) {
	for (const auto& fig : connecting_figure) {
		painter.drawLine(QLine(rect.center(), fig->GetCenter()));
	}
}

void Rectangle::RemoveConnectionWithFigure(std::shared_ptr<Figure> figure) {
	if (connecting_figure.find(figure) != connecting_figure.end()) {
		connecting_figure.erase(figure);
	}
}

const std::unordered_set<std::shared_ptr<Figure>>& Rectangle::GetConnectedFigure() {
	return connecting_figure;
}

QPoint Rectangle::GetLeftTopCorner() const {
	return rect.topLeft();
}

QPoint Rectangle::GetBottomRightCorner() const {
	return rect.bottomRight();
}

QPoint Rectangle::GetCenter() const {
	return rect.center();
}

void Rectangle::setLeftTopCorner(QPoint corner) {
	rect.setTopLeft(corner);
}
void Rectangle::setBottomRightCorner(QPoint corner) {
	rect.setBottomRight(corner);
	setMinAndMax();
}