#ifndef PROGRESSION_H
#define PROGRESSION_H

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Родительский класс
class Progression {
protected:
	double start{}, end{}, dif{}; // начало отрезка, конец отрезка, разница между двумя членами прогрессии

public:
	// Виртуальный метод для подсчета суммы прогрессии 
	virtual double sum() {
		return 0;
	}
};

// Класс для арифметической прогрессии
class Linear : public Progression {
public:
	Linear(double start, double end, double dif);
	double sum() override;
};

// Класс для геометрической прогрессии
class Exponential : public Progression {
public:
	Exponential(double start, double end, double dif);
	double sum() override;
};

// Класс для вычисления суммы прогрессий
class Count {
public:
	Progression* prog = nullptr;
	void calcProg();
};

#endif // PROGRESSION_H
