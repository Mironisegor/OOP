#include <iostream>
#include <cmath>
#include <vld.h>

using namespace std;

class Point {
public:
	double x = 0, y = 0;
};

class Shape {
protected:
	int n{};
	Point* arc = nullptr;
public:
	//Метод для подсчета суммы
	double square() {
		double ans{};
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			ans += (arc[i].x * arc[j].y) - (arc[i].y * arc[j].x);
		}
		return abs(ans) / 2.0;
	}
	//Метод для подсчета центра тяжести многоугольника
	Point centOfGrav(double area) {
		double xc = 0, yc = 0;
		double P = 0;
		for (int i = 0; i < n; i++) {
			if (i == n - 1) {
				double l = sqrt((arc[i].x - arc[0].x) * (arc[i].x - arc[0].x) + (arc[i].y - arc[0].y) * (arc[i].y - arc[0].y));
				xc += l * (arc[i].x + arc[(0) % n].x) / 2;
				yc += l * (arc[i].y + arc[(0) % n].y) / 2;
				P += l;
			}
			else {
				double l = sqrt((arc[i].x - arc[i + 1].x) * (arc[i].x - arc[i + 1].x) + (arc[i].y - arc[i + 1].y) * (arc[i].y - arc[i + 1].y));
				xc += l * (arc[i].x + arc[(i + 1) % n].x) / 2;
				yc += l * (arc[i].y + arc[(i + 1) % n].y) / 2;
				P += l;
			}
		}
		xc /= P;
		yc /= P;
		return {xc, yc};
	}

	virtual void input() = 0;
//	virtual void rotate() = 0;
//	virtual void move() = 0;

	~Shape() {
		delete[]arc;
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
//	void centOfGrav() override {};
//	void rotate() override {};
//	void move() override {};
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
//	void centOfGrav() override {};
//	void rotate() override {};
//	void move() override {};
};

class Operations {
public:
	bool Compare() {};
	bool isIntersect() {};
	bool isInclude() {};
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

int main() {
	setlocale(LC_ALL, "ru");

	Shape* ptr = nullptr;
	char type{};
	int choose = 1;

	while (choose) {
		if (ptr) {
			delete ptr;
			ptr = nullptr;
		}
		cout << "Введите тип фигуры. P/O: ";
		cin >> type;
		ptr = FactoryShape::createShape(type);
		if (!ptr) {
			cout << "Нет такой фигуры!" << endl;
			break;
		}
		cout << "Введите координаты точек: " << endl;
		ptr->input();

		double square = ptr->square();
		cout << "Площадь фигуры равна: " << square << endl;
		Point cntOfGrav = ptr->centOfGrav(square);
		cout << "Центр тяжести по x: " << cntOfGrav.x << ", по y: " << cntOfGrav.y << endl;

		cout << "Продолжим? 1/0: ";
		cin >> choose;
	}

	delete ptr;

	return 0;
}

/*
Пятиугольник
0 0
0 2
3 2
3 0
2 -2
Ответ: 9
*/
/*
Восьмиугольник
-1 0
0 2
2 3
4 2
5 0
4 -2
2 -3
0 -2
Площадь: 24
Центр тяжести: 2 0
*/
