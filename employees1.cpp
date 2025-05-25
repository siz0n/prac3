#include "all.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Employee {
    string name;
    double salary;
    string department;
};

void employe1() {
    vector<Employee> employees = {
        {"Alice", 3000, "IT"}, {"Bob", 4000, "HR"}, {"Charlie", 5500, "IT"},
        {"David", 4000, "IT"}, {"Eve", 4000, "HR"}, {"Frank", 2000, "Sales"},
        {"Grace", 3500, "Sales"}
    };

    // Группировка по департаменту
    map<string, vector<Employee>> dept_map;
    for_each(employees.begin(), employees.end(), [&](const Employee& e) {
        dept_map[e.department].push_back(e);
    });

    // Сортировка сотрудников внутри департамента
    for_each(dept_map.begin(), dept_map.end(), [](pair<const string, vector<Employee>>& pr) {
        sort(pr.second.begin(), pr.second.end(), [](const Employee& a, const Employee& b) {
            return a.salary != b.salary ? a.salary > b.salary : a.name < b.name;
        });
    });

    // Список департаментов с сортировкой по средней зарплате
    vector<pair<string, vector<Employee>>> sorted_deps;
    copy(dept_map.begin(), dept_map.end(), back_inserter(sorted_deps));
    sort(sorted_deps.begin(), sorted_deps.end(), [](const auto& a, const auto& b) {
        auto avg = [](const vector<Employee>& v) {
            return accumulate(v.begin(), v.end(), 0.0,
                [](double sum, const Employee& e){ return sum + e.salary; }) / v.size();
        };
        return avg(a.second) > avg(b.second);
    });

    // Вывод результата
    cout << "Департаменты по убыванию средней зарплаты:\n";
    for_each(sorted_deps.begin(), sorted_deps.end(), [](const auto& dep) {
        double avg = accumulate(dep.second.begin(), dep.second.end(), 0.0,
            [](double sum, const Employee& e){ return sum + e.salary; }) / dep.second.size();
        cout << dep.first << " (ср. зарплата: " << avg << "):\n";
        for_each(dep.second.begin(), dep.second.end(), [](const Employee& e) {
            cout << "  " << e.name << " (" << e.salary << ")\n";
        });
    });
}