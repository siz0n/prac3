#include <iostream>
#include "all.h"

using namespace std;

int main() {
    while (true) {
        cout << "\nМеню задач:\n"
                     "1. Группировка сотрудников\n"
                     "2. Доставка (жадный маршрут)\n"
                     "3. Цепочка кратных\n"
                     "4. Сравнение конфигураций\n"
                     "5. Слияние расписаний\n"
                     "6. Анализ команд\n"
                     "7. Поиск циклов в графе\n"
                     "8. Планирование задач\n"
                     "9. Доминирующие цвета\n"
                     "10. Объединение словарей\n"
                     "0. Выход\n"
                     "Выберите задачу: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: employe1();break;
            case 2:  delivery2();break;
            case 3:  miltiples3();break;
            case 4:  tree4();break;
            case 5:  schedule5();break;
            case 6:  analysis6();break;
            case 7:  graphs7();break;
            case 8:  deadline8();break;
            case 9:  colors9();break;
            case 10:  dictionary();break;
            case 0: return 0;
            default: cout << "Некорректный выбор\n";
        }
    }
}