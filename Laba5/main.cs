using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace laba4
{
    // Класс для хранения данных о людях
    public class Elections
    {
        public string name { get; set; }        // Имя
        public string surname { get; set; }     // Фамилия
        public string patronymic { get; set; }  // Отчество
        public string dateOfBirth { get; set; } // Дата рождения
        public string placeOfWork { get; set; } // Место работы
        public float rate { get; set; }         // Рейтинг

        // Конструктор с параметрами
        public Elections(string surname, string name, string patronymic, string dateOfBirth, string placeOfWork, float rate)
        {
            this.name = name;
            this.surname = surname;
            this.patronymic = patronymic;
            this.dateOfBirth = dateOfBirth;
            this.placeOfWork = placeOfWork;
            this.rate = rate;
        }
    }

    class Program
    {
        // Функция для открытия файла
        static StreamReader InputFromFile()
        {
            Console.Write("Введите имя файла(например text.txt): ");
            string filename = Console.ReadLine();
            try
            {
                return new StreamReader(filename);
            }
            catch (FileNotFoundException)
            {
                throw new Exception("Файл невозможно открыть! Проверьте имя файла");
            }
        }

        // Функция для выполнения задания A
        static (float, float) TaskA()
        {
            HashSet<float> rates = new HashSet<float>();
            using (StreamReader file = InputFromFile())
            {
                string line;
                while ((line = file.ReadLine()) != null)
                {
                    string[] parts = line.Split(' ');
                    if (parts.Length == 6 && float.TryParse(parts[5], out float rate))
                    {
                        rates.Add(rate);
                    }
                }
            }
            return (rates.Min(), rates.Max());
        }

        // Функция для выполнения задания B
        static void TaskB(List<Elections> vec, float rateForCompare)
        {
            using (StreamReader file = InputFromFile())
            {
                string line;
                while ((line = file.ReadLine()) != null)
                {
                    string[] parts = line.Split(' ');
                    if (parts.Length == 6 && float.TryParse(parts[5], out float rate))
                    {
                        vec.Add(new Elections(parts[0], parts[1], parts[2], parts[3], parts[4], rate));
                    }
                }
            }

            foreach (var person in vec)
            {
                if (person.rate > rateForCompare)
                {
                    Console.WriteLine($"{person.surname} {person.name} {person.patronymic} {person.dateOfBirth} {person.placeOfWork} {person.rate}");
                    Console.WriteLine("--------------------------");
                }
            }
        }

        static void Main(string[] args)
        {
            List<Elections> vec = new List<Elections>();
            bool isContinue = true;

            while (isContinue)
            {
                Console.Write("Какую задачу хотите выполнить, a или b? Введите латинскую букву: ");
                char choice = Console.ReadKey().KeyChar;
                float rateForCompare = 0;
                Console.WriteLine(); // Перевод строки

                try
                {
                    if (choice == 'a' || choice == 'A')
                    {
                        var res = TaskA();
                        Console.WriteLine($"Диапозон рейтингов: {res.Item1} - {res.Item2}");
                    }
                    else if (choice == 'b' || choice == 'B')
                    {
                        Console.Write("Введите число для поиска людей с большим рейтингом, чем ваше число: ");
                        if (float.TryParse(Console.ReadLine(), out rateForCompare))
                        {
                            TaskB(vec, rateForCompare);
                        }
                        else
                        {
                            Console.WriteLine("Неправильный формат числа.");
                        }
                    }
                    else
                    {
                        throw new Exception("Неправильный выбор задачи. Нужно ввести одну из двух латинских букв: a, b");
                    }

                    Console.Write("Хотите еще раз выполнить какое-нибудь задание? 1/0: ");
                    isContinue = Console.ReadLine() == "1";
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    return;
                }
            }
        }
    }
}
