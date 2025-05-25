#include "all.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Event { int day; int hour; int priority; };

void schedule5() {
    multimap<int, Event> sched1 = { {1, {1, 9, 10}}, {1, {1, 10, 7}}, {2, {2, 14, 9}} };
    multimap<int, Event> sched2 = { {1, {1, 9, 12}}, {2, {2, 14, 11}}, {2, {2, 16, 5}} };

    vector<multimap<int, Event>> schedules = {sched1, sched2};
    vector<Event> all_events;
    for_each(schedules.begin(), schedules.end(), [&](const multimap<int, Event>& sch){
        for_each(sch.begin(), sch.end(), [&](const auto& pr){
            all_events.push_back(pr.second);
        });
    });

    // Сортировка по дню и часу, затем по убыванию приоритета
    sort(all_events.begin(), all_events.end(), [](const Event& a, const Event& b){
        if (a.day != b.day) return a.day < b.day;
        if (a.hour != b.hour) return a.hour < b.hour;
        return a.priority > b.priority;
    });

    // Оставить только максимальный приоритет на каждый день-час
    vector<Event> result;
    for_each(all_events.begin(), all_events.end(), [&](const Event& e) {
        if (result.empty() || result.back().day != e.day || result.back().hour != e.hour)
            result.push_back(e);
    });

    cout << "Слитое расписание (день, час, приоритет):\n";
    for_each(result.begin(), result.end(), [](const Event& e){
        cout << "(" << e.day << ", " << e.hour << ", " << e.priority << ")\n";
    });
}