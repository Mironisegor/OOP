#include <iostream>
#define _USE_MATH_DEFINES //Для использования M_PI
#include <math.h>
#include <vld.h>

using namespace std;

class Point {
public:
	double x = 0, y = 0;
};

class Shape {
protected:
	int n{};
	double squareOfFigure{};
	Point* arc{};
	Point center{};
public:
	double getSquare() const {
		return squareOfFigure;
	}
	Point getCenter() {
		return center;
	}
	int getN() {
		return n;
	}
	Point* getArc() {
		return arc;
	}

	//Метод для подсчета площади фигуры
	void countSquare();

	//Метод для подсчета центра тяжести многоугольника
	void countCentOfGrav();

	//Метод для вращения фигуры
	void rotate(int gr);

	//Метод для сдвига фигуры
	void move(double hor, double vert);

	//Чисто виртуальный метод для ввода координат
	virtual void input() = 0;

	virtual ~Shape() {
	}
};

class Pentagon : public Shape {
public:
	Pentagon() {
		n = 5;
		arc = new Point[n];
	}
	void input() override {
		for (int i = 0; i < n; i++) {
			cin >> arc[i].x >> arc[i].y;
		}
	}
	~Pentagon() {
		delete[] arc;
	}
};

class Octagon : public Shape {
public:
	Octagon() {
		n = 8;
		arc = new Point[n];
	}

	void input() override {
		for (int i = 0; i < n; i++) {
			cin >> arc[i].x >> arc[i].y;
		}
	}
	~Octagon() {
		delete[] arc;
	}
};

class Operations {
public:
	//Метод для сравнения площадей
	static int Compare(Shape* first, Shape* second);

	//Метод для вычисления расстояние между точками
	static double distance(Point p1, Point p2) {
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}

	//Метод для вычисления максимального расстояния от центра до наиболее удаленной точки у фигуры
	static double getBoundingRadius(Shape* elem);

	//Метод для проверки пересечения фигур
	static bool isIntersect(Shape* first, Shape* second);

	//Метод для проверки включения одной фигуры в другую
	static bool isInclude(Shape* first, Shape* second);
};

class FactoryShape {
public:
	static Shape* createShape(char sym) {
		switch (sym) {
		case 'P':
			return new Pentagon;
		case 'O':
			return new Octagon;
		default:
			return nullptr;
		}
	}
};
