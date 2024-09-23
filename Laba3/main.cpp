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
	void countSquare() {
		double ans{};
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			ans += (arc[i].x * arc[j].y) - (arc[i].y * arc[j].x);
		}
		squareOfFigure = abs(ans) / 2.0;
	}

	//Метод для подсчета центра тяжести многоугольника
	void countCentOfGrav() {
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

	//Метод для вращения фигуры
	void rotate(int gr) {
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

	//Метод для сдвига фигуры
	void move(double hor, double vert) {
		for (int i = 0; i < n; i++) {
			arc[i].x += hor;
			arc[i].y += vert;
			cout << arc[i].x << ' ' << arc[i].y << endl;
		}
	}

	//Чисто виртуальный метод для ввода координат
	virtual void input() = 0;

	virtual ~Shape() {
		delete arc;
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
};

class Operations {
public:
	//Метод для сравнения площадей
	static int Compare(Shape* first, Shape* second) {
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

	static double distance(Point p1, Point p2) {
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}

	//Метод для вычисления максимального расстояния от центра до наиболее удаленной точки у фигуры
	static double getBoundingRadius(Shape* elem) {
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

	//Метод для проверки пересечения фигур
	static bool isIntersect(Shape* first,Shape* second) {
		double d = distance(first->getCenter(), second->getCenter());
		double radiusFirst = getBoundingRadius(first);
		double radiusSecond = getBoundingRadius(second);

		return d <= (radiusFirst + radiusSecond);
	}

	//Метод для проверки включения одной фигуры в другую
	static bool isInclude(Shape* first, Shape* second) {

		Point centerFirst = { first->getCenter().x, first->getCenter().y};
		Point centerSecond = { second->getCenter().x, second->getCenter().y };

		double radiusFirst = getBoundingRadius(first);
		double radiusSecond = getBoundingRadius(second);

		// Расстояние между центрами двух фигур
		double centerDistance = distance(centerFirst, centerSecond);

		// Проверка, включена ли одна окружность в другую
		return centerDistance + radiusFirst <= radiusSecond || centerDistance + radiusSecond <= radiusFirst;
	}
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

	Shape* first = nullptr;
	Shape*second = nullptr;
	char type{};
	bool isContinue = 1;
	int gr{}, rotateOrNot = 0, moveOrNot = 0;

	while (isContinue) {
		try {
			if (first) {
				delete first;
				first = nullptr;
			}
			cout << "Введите тип фигуры. P/O: ";
			cin >> type;
			first = FactoryShape::createShape(type);
			if (!first) {
				isContinue = 0;
				throw 1;
			}
			cout << "Введите координаты точек: " << endl;
			first->input();

			first->countSquare();
			cout << "Площадь фигуры равна: " << first->getSquare() << endl;
			first->countCentOfGrav();
			cout << "Центр тяжести по x: " << first->getCenter().x << ", по y: " << first->getCenter().y << endl;

			cout << "Хотите вращать фигуру? 1/0 ";
			cin >> rotateOrNot;
			if (rotateOrNot) {
				cout << "Введите на сколько градусов хотите повернуть: ";
				cin >> gr;
				cout << "Новые координаты: " << endl;
				first->rotate(gr);
			}
			cout << "Хотите передвинуть фигуру по горизонтали либо вертикали? 1/0: ";
			cin >> moveOrNot;
			if (moveOrNot) {
				double horizontal{}, vertical{};
				cout << "На сколько передвинуть по горизонтали и вертикали? Введите числа через пробел: ";
				cin >> horizontal >> vertical;
				first->move(horizontal, vertical);
			}

			/*
			----------------------------------------------------------------------------------------------------------------
			*/

			if (second) {
				delete second;
				second = nullptr;
			}
			cout << "Введите тип фигуры. P/O: ";
			cin >> type;
			second = FactoryShape::createShape(type);
			if (!second) {
				isContinue = 0;
				throw 2;
			}
			cout << "Введите координаты точек: " << endl;
			second->input();

			second->countSquare();
			cout << "Площадь фигуры равна: " << second->getSquare() << endl;
			second->countCentOfGrav();
			cout << "Центр тяжести по x: " << second->getCenter().x << ", по y: " << second->getCenter().y << endl;

			cout << "Хотите вращать фигуру? 1/0 ";
			cin >> rotateOrNot;
			if (rotateOrNot) {
				cout << "Введите на сколько градусов хотите повернуть: ";
				cin >> gr;
				cout << "Новые координаты: " << endl;
				second->rotate(gr);
			}
			cout << "Хотите передвинуть фигуру по горизонтали либо вертикали? 1/0: ";
			cin >> moveOrNot;
			if (moveOrNot) {
				double horizontal{}, vertical{};
				cout << "На сколько передвинуть по горизонтали и вертикали? Введите числа через пробел: ";
				cin >> horizontal >> vertical;
				second->move(horizontal, vertical);
			}
			/*
			-----------------------------------------------------------------------------------------------------------------
			*/
			int cmp = Operations::Compare(first, second);
			if (cmp == 0) {
				cout << "Площадь первой фигуры больше первой" << endl;
			}
			else if (cmp == 1) {
				cout << "Площадь первой фигуры меньше второй" << endl;
			}
			else {
				cout << "Площади фигур равны" << endl;
			}

			int flag1 = 0, flag2 = 0;
			if (Operations::isInclude(first, second)) {
				cout << "Одна из фигур включена в другую" << endl;
				flag1 = 1;
			}
			else {
				cout << "Ни одна из фигур не включена в другую" << endl;
				if (!flag1) {
					if (Operations::isIntersect(first, second)) {
						cout << "Фигуры пересекаются" << endl;
						flag2 = 1;
					}
				}
			}
			if (!flag2) {
				cout << "Фигуры не пересекаются" << endl;
			}

			cout << "Хотите ввести фигуры еще раз? 1/0: ";
			cin >> isContinue;
			if (!isContinue) {
				isContinue = 0;
			}
		}
		catch (int num) {
			if (num == 1) {
				cout << "Неправильно введен тип для первой фигуры" << endl;
			}
			else {
				cout << "Неправильно введен тип для второй фигуры" << endl;
			}
			cout << "Нужно ввести либо P, либо O" << endl;
		}
	}

	delete first;
	delete second;

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

/*
Проверка на включение
2 1
1 2
2 4
4 4
4 2
-----------
1 0
0 1
0 4
2 6
5 6
6 4
6 1
4 -1
*/

/*
Проверка на включение
3 0
1 1
2 3
4 3
5 1
----------
0 0
0 1
1 3
2 4
4 4
7 1
5 -1
2 -1
*/
/*
Проверка на не пересечение и не включение
-5 1
-6 2
-5 4
-3 4
-3 2
-----------
0 0
0 1
1 3
2 4
4 4
7 1
5 -1
2 -1
*/
