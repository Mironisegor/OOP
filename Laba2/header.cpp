#include "progression.h"

// Реализация конструктора и метода для класса Linear (арифметическая прогрессия)
Linear::Linear(double start, double end, double dif) {
	this->start = start;
	this->end = end;
	this->dif = dif;
}

//Реализация метода для арифметической прогрессии
double Linear::sum() {
	int n = ((end - start) / dif) + 1;
	return ((start + end) * n) / 2;
}

// Реализация конструктора и метода для класса Exponential (геометрическая прогрессия)
Exponential::Exponential(double start, double end, double dif) {
	this->start = start;
	this->end = end;
	this->dif = dif;
}

//Реализация метода для геометрической прогрессии
double Exponential::sum() {
	return (end * dif - start) / (dif - 1);
}

// Реализация метода для класса Count
void Count::calcProg() {
	int choose = 1, cinCout{};
	cout << "Введите 1, если хотите ввести данные из консоли, иначе 0: ";
	cin >> cinCout;
	if (cinCout) {
		//Пользователь сам вводит данные
		while (true) {
			double num1{}, num2{}, num3{};
			cout << "Введите 1, если хотите посчитать сумму арифметической прогрессии и 0, если геометрической: ";
			cin >> choose;
			if (choose) {
				cout << "Введите диапозон и разницу для арифметической прогрессии: ";
				cin >> num1 >> num2 >> num3;

				prog = new Linear(num1, num2, num3);
			}
			else {
				cout << "Введите диапозон и разницу для геометрической прогрессии: ";
				cin >> num1 >> num2 >> num3;

				prog = new Exponential(num1, num2, num3);
			}
			cout << "Ответ: " << prog->sum() << endl;
			delete prog;
			cout << "Ввести данные еще раз? Введите 1, если да, иначе 0: ";
			cin >> choose;

			if (!choose) {
				break;
			}
		}
	}
	//Пользователь не захотел сам вводить данные
	else {
		cout << "Сумма арифметической прогрессии для диапозона [1, 10] и разницой в 1 равна: ";
		prog = new Linear(1, 10, 1);
		cout << prog->sum() << endl;
		delete prog;
		cout << "Сумма геометрической прогрессии для диапозона [2, 64] и разницой в 2 равна: ";
		prog = new Exponential(2, 64, 2);
		cout << prog->sum() << endl;
		delete prog;
	}
}
