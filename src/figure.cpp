#include "figure.h"
 
std::shared_ptr<Figure> build_figure(FigureType type) {
	switch (type)
	{
	case FigureType::Rectangle_:
		return std::make_shared<Rectangle>();
		break;
	case FigureType::Ellipse_:
		return std::make_shared<Ellipse>();
		break;
	case FigureType::Triangle_:
		return std::make_shared<Triangle>();
		break;
	default:
		break;	
	}
}
