#include "all.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Task { int id; int deadline; int priority; };

void deadline8() {
    multimap<int, Task> taskmap = {
        {1, {1, 1, 10}}, {2, {2, 2, 8}}, {1, {3, 1, 15}},
        {3, {4, 3, 6}}, {2, {5, 2, 7}}
    };

    int curr_time = 2; // пример текущего времени

    // Удаляем просроченные
    vector<Task> tasks;
    for (const auto& p : taskmap) {
        if (p.second.deadline >= curr_time)
            tasks.push_back(p.second);
    }

    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b){
        return a.priority > b.priority;
    });

    cout << "Очередь задач по приоритету:\n";
    for (const auto& t : tasks) {
        cout << "id=" << t.id << " deadline=" << t.deadline << " priority=" << t.priority << "\n";
    }
}