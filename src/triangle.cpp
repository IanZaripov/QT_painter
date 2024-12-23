#include "figure.h"

FigureType Triangle::GetFigureType() const {
	return FigureType::Triangle_;
}

void Triangle::computeMinAndMax(QMouseEvent* mouse_pos) {
	mx_x = std::max(mouse_pos->x(), first_click.x());
	mx_y = std::max(mouse_pos->y(), first_click.y());
	mn_x = std::min(mouse_pos->x(), first_click.x());
	mn_y = std::min(mouse_pos->y(), first_click.y());
	/*int y_center = triangle[0].y() + ((2 * frame.height()) / 3);
	center = QPoint(triangle[0].x(), y_center);*/
}

void Triangle::setMinAndMax() {
	mx_x = frame.bottomRight().x();
	mx_y = frame.bottomRight().y();
	mn_x = frame.topLeft().x();
	mn_y = frame.topLeft().y();
	int upangle = frame.topLeft().x() + ((frame.topRight().x() - frame.topLeft().x()) / 2);
	triangle[0] = QPointF(QPoint(upangle, frame.topLeft().y()));
	triangle[1] = QPointF(frame.bottomLeft());
	triangle[2] = QPointF(frame.bottomRight());
	triangle[3] = QPointF(QPoint(upangle, frame.topLeft().y()));
	/*int y_center = triangle[0].y() + ((2 * frame.height()) / 3);
	center = QPoint(triangle[0].x(), y_center);*/
}

void Triangle::StartDrawFigure(QMouseEvent* mouse_position) {
	first_click = mouse_position->pos();
	computeMinAndMax(mouse_position);
	frame.setTopLeft(mouse_position->pos());
	frame.setBottomRight(mouse_position->pos());
	int upAngle = frame.topLeft().x() + ((frame.topRight().x() - frame.topLeft().x()) / 2);
	triangle[0] = QPointF(QPoint(upAngle, frame.topLeft().y()));
	triangle[1] = QPointF(frame.bottomLeft());
	triangle[2] = QPointF(frame.bottomRight());
	triangle[3] = QPointF(QPoint(upAngle, frame.topLeft().y()));
	//int y_center = triangle[0].y() + ((2 * frame.height()) / 3);
	//center = QPoint(triangle[0].x(), y_center);
}

void Triangle::UpdateDrawFigure(QMouseEvent* mouse_position) {
	computeMinAndMax(mouse_position);
	frame.setTopLeft(QPoint(mn_x, mn_y));
	frame.setBottomRight(QPoint(mx_x, mx_y));
	setMinAndMax();
}

void Triangle::DrawFigure(QPainter& painter) {
	painter.drawPolyline(triangle,4);
}

void Triangle::StartMoveFigure(QMouseEvent* mouse_position) {
	pivot_moving_point = mouse_position->pos();
}

void Triangle::DoMoveFigure(QMouseEvent* mouse_position) {
	QPoint cur_point = mouse_position->pos();
	QPoint dif = cur_point - pivot_moving_point;
	frame.moveCenter(frame.center() + dif);
	mx_x = frame.bottomRight().x();
	mx_y = frame.bottomRight().y();
	mn_x = frame.topLeft().x();
	mn_y = frame.topLeft().y();
	setMinAndMax();
	pivot_moving_point = cur_point;
}

bool Triangle::isMouseClickInsideFigure(QMouseEvent* mouse_click_pos) const {
	int upAngle = (triangle[0].x() - mouse_click_pos->x())
		* (triangle[1].y() - triangle[0].y()) - (triangle[1].x() - triangle[0].x())
		* (triangle[0].y() - mouse_click_pos->y());
	int bottomLeftAngle = (triangle[1].x() - mouse_click_pos->x())
		* (triangle[2].y() - triangle[1].y()) - (triangle[2].x() - triangle[1].x())
		* (triangle[1].y() - mouse_click_pos->y());
	int bottomRightAngle = (triangle[2].x() - mouse_click_pos->x())
		* (triangle[0].y() - triangle[2].y()) - (triangle[0].x() - triangle[2].x())
		* (triangle[2].y() - mouse_click_pos->y());
	if ((upAngle >= 0 && bottomLeftAngle >= 0 && bottomRightAngle >= 0) || (upAngle <=0 && bottomLeftAngle <= 0 && bottomRightAngle <= 0)) {
		return true;
	}
	return false;
}


void Triangle::StartDrawConnection(QMouseEvent* mouse_position) {
	line.setP1(frame.center());
	line.setP2(mouse_position->pos()); 
}

void Triangle::UpdateDrawConnection(QMouseEvent* mouse_position) {
	line.setP2(mouse_position->pos());
}

QPoint Triangle::GetLeftTopCorner() const {
	return frame.topLeft();
}

QPoint Triangle::GetBottomRightCorner() const {
	return frame.bottomRight();
}

QPoint Triangle::GetCenter() const {
	return frame.center();
}

void Triangle::DrawConnection(QPainter& painter) {
	painter.drawLine(line);
}

void Triangle::FinishDrawConnection(std::shared_ptr<Figure>figure) {
	connecting_figure.insert(figure);
}

void Triangle::RedrawConnection(QPainter& painter) {
	for (const auto& fig : connecting_figure) {
		painter.drawLine(QLine(frame.center(), fig->GetCenter()));
	}
}

void Triangle::RemoveConnectionWithFigure(std::shared_ptr<Figure> figure) {
	if (connecting_figure.find(figure) != connecting_figure.end()) {
		connecting_figure.erase(figure);
	}
}

const std::unordered_set<std::shared_ptr<Figure>>& Triangle::GetConnectedFigure() {
	return connecting_figure;
}


void Triangle::setLeftTopCorner(QPoint corner) {
	frame.setTopLeft(corner);
}
void Triangle::setBottomRightCorner(QPoint corner) {
	frame.setBottomRight(corner);
	setMinAndMax();
}