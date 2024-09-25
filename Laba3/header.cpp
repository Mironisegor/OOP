#include "header.h"

void Shape:: countSquare() {
	double ans{};
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		ans += (arc[i].x * arc[j].y) - (arc[i].y * arc[j].x);
	}
	squareOfFigure = abs(ans) / 2.0;
}

void Shape::countCentOfGrav() {
	double P = 0;
	for (int i = 0; i < n; i++) {
		//Соединяем первую и посленюю точку
		if (i == n - 1) {
			double l = sqrt((arc[i].x - arc[0].x) * (arc[i].x - arc[0].x) + (arc[i].y - arc[0].y) * (arc[i].y - arc[0].y));
			center.x += l * (arc[i].x + arc[(0) % n].x) / 2;
			center.y += l * (arc[i].y + arc[(0) % n].y) / 2;
			P += l;
		}
		//Соединяем все остальные точки
		else {
			double l = sqrt((arc[i].x - arc[i + 1].x) * (arc[i].x - arc[i + 1].x) + (arc[i].y - arc[i + 1].y) * (arc[i].y - arc[i + 1].y));
			center.x += l * (arc[i].x + arc[(i + 1) % n].x) / 2;
			center.y += l * (arc[i].y + arc[(i + 1) % n].y) / 2;
			P += l;
		}
	}
	center.x /= P;
	center.y /= P;
}

void Shape::rotate(int gr) {
	if (gr >= 360) {
		gr = gr - 360;
	}

	double sina = sin(gr * (M_PI / 180)); //0
	//Проверка на близость к нулю
	if (abs(sina) < 1e-10) {
		sina = 0;
	}
	double cosa = cos(gr * (M_PI / 180)); //-1

	for (int i = 0; i < n; i++) {
		double newX = ((arc[i].x - center.x) * cosa - (arc[i].y - center.y) * sina) + center.x;
		//Проверка на близость к нулю
		if (abs(newX) < 1e-10) {
			newX = 0;
		}
		double newY = ((arc[i].x - center.x) * sina + (arc[i].y - center.y) * cosa) + center.y;
		arc[i].x = newX;
		arc[i].y = newY;
		cout << arc[i].x << ' ' << arc[i].y << endl;
	}
}

void Shape::move(double hor, double vert) {
	for (int i = 0; i < n; i++) {
		arc[i].x += hor;
		arc[i].y += vert;
		cout << arc[i].x << ' ' << arc[i].y << endl;
	}
}

int Operations::Compare(Shape* first, Shape* second) {
	if (first->getSquare() > second->getSquare()) {
		return 0;
	}
	else if (first->getSquare() < second->getSquare()) {
		return 1;
	}
	else {
		return 2;
	}
};

double Operations::getBoundingRadius(Shape* elem) {
	double maxDistance = 0;
	Point* vertices = elem->getArc();
	for (int i = 0; i < elem->getN(); i++) {
		double dist = distance(elem->getCenter(), vertices[i]);
		if (dist > maxDistance) {
			maxDistance = dist;
		}
	}
	return maxDistance;
}

bool Operations::isIntersect(Shape* first, Shape* second) {
	double d = distance(first->getCenter(), second->getCenter());
	double radiusFirst = getBoundingRadius(first);
	double radiusSecond = getBoundingRadius(second);

	return d <= (radiusFirst + radiusSecond);
}

bool Operations::isInclude(Shape* first, Shape* second) {

	Point centerFirst = { first->getCenter().x, first->getCenter().y };
	Point centerSecond = { second->getCenter().x, second->getCenter().y };

	double radiusFirst = getBoundingRadius(first);
	double radiusSecond = getBoundingRadius(second);

	// Расстояние между центрами двух фигур
	double centerDistance = distance(centerFirst, centerSecond);

	// Проверка, включена ли одна окружность в другую
	return centerDistance + radiusFirst <= radiusSecond || centerDistance + radiusSecond <= radiusFirst;
}
