#include "header.h"

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
