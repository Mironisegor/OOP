#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;

//Класс для хранения данных о людях
class Elections {
public:
    string name{};        //Имя
    string surname{};     //Фамилия
    string patronymic{};  //Отчество
    string dateOfBirth{}; //Дата рождения
    string placeOfWork{}; //Место работы
    float rate{};         //Рейтинг

    //Конструктор с параметрами
    Elections(string surname, string name, string patronymic, string dateOfBirth, string placeOfWork, float rate) {
        this->name = name;
        this->surname = surname;
        this->patronymic = patronymic;
        this->dateOfBirth = dateOfBirth;
        this->placeOfWork = placeOfWork;
        this->rate = rate;
    }
};

//Функция для открытия файла
ifstream inputFromFile() {
    string filename;
    cout << "Введите имя файла(например text.txt): ";
    cin >> filename;
    ifstream file;
    file.open(filename);

    if (!file) {
        throw 1;
    }
    return file;
}

//Функция для выполнения задания a
pair<float, float> taskA() {
    set <int> rates;
    float rate = 0;
    string name, surname, patronymic, dateOfBirth, placeOfwork, lineFromFile;
    ifstream file = inputFromFile();

    while (!file.eof()) {
        getline(file, lineFromFile);
        istringstream lineStream(lineFromFile);
        lineStream >> surname >> name >> patronymic >> dateOfBirth >> placeOfwork >> rate;
        rates.insert(rate);
    }
    file.close();

    return { *rates.begin(), *rates.rbegin() };
}

//Функция для выполнения задания b
void taskB(vector <Elections>& vec, float rateForCompare) {
    float rate = 0;
    string name, surname, patronymic, dateOfBirth, placeOfwork, lineFromFile;
    ifstream file = inputFromFile();
    while (!file.eof()) {
        getline(file, lineFromFile);
        istringstream lineStream(lineFromFile);
        lineStream >> surname >> name >> patronymic >> dateOfBirth >> placeOfwork >> rate;
        vec.push_back(Elections(surname, name, patronymic, dateOfBirth, placeOfwork, rate));
    }
    file.close();

    for (const auto& person : vec) {
        if (person.rate > rateForCompare) {
            cout << person.surname << ' ' << person.name << ' ' << person.patronymic << ' ' << person.dateOfBirth << ' ' << person.placeOfWork << ' ' << person.rate << endl;
            cout << "--------------------------" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<Elections> vec;
    bool isContinue = true;
    char choice = ' ';

    while (true) {
        cout << "Какую задачу хотите выполнить, a или b? Введите латинскую маленькую букву: ";
        cin >> choice;
        cin.ignore();

        try {
            if (choice == 'a' or choice == 'A') {
                pair<float, float> res = taskA();
                cout << "Диапозон рейтингов: " << res.first << " - " << res.second << endl;
            }
            else if (choice == 'b' or choice == 'B') {
                float rateForComare = 0;
                cout << "Введите число для поиска людей с большим рейтингом, чем ваше число: ";
                cin >> rateForComare;
                taskB(vec, rateForComare);
            }
            else {
                throw 2;
            }
            cout << "Хотите еще раз выполнить какое-нибудь задание? 1/0: ";
            cin >> isContinue;
            if (!isContinue) {
                isContinue = false;
            }
        }
        catch (int num) {
            if (num == 1) {
                cout << "Файл невозможно открыть! Проверьте имя файла" << endl;
                return 1;
            }
            else if (num == 2) {
                cout << "Неправильнй выбор задачи. Нужно ввести одну из двух латинских букв: a, b" << endl;
                return 2;
            }
        }
    }

    return 0;
}
