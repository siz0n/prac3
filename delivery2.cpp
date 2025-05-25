#include "all.h"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

struct DeliveryPoint {
    string name;
    double x, y;
    double priority;
};

void delivery2() {
    vector<DeliveryPoint> points = {
        {"A", 1, 2, 2}, {"B", 3, 4, 1.5}, {"C", -2, 1, 3}, {"D", 5, 0, 2.5}
    };
    set<int> visited;
    vector<string> route;
    double curr_x = 0, curr_y = 0;

    for (size_t step = 0; step < points.size(); ++step) {
        double min_cost = 1e9;
        int next = -1;
        for_each(points.begin(), points.end(), [&](const DeliveryPoint& p) {
            int idx = &p - &points[0];
            if (visited.count(idx)) return;
            double dist = sqrt((p.x-curr_x)*(p.x-curr_x) + (p.y-curr_y)*(p.y-curr_y));
            double cost = dist / p.priority;
            if (cost < min_cost) {
                min_cost = cost;
                next = idx;
            }
        });
        if (next != -1) {
            visited.insert(next);
            route.push_back(points[next].name);
            curr_x = points[next].x;
            curr_y = points[next].y;
        }
    }
    cout << "Маршрут: ";
    for_each(route.begin(), route.end(), [](const string& name) {
        cout << name << " ";
    });
    cout << "\n";
}