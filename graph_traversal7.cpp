#include "all.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct Dependency { string from, to; };

void graphs7() {
    vector<Dependency> deps = {
        {"A", "B"}, {"B", "C"}, {"C", "D"}, {"D", "A"}, // цикл
        {"E", "F"}, {"F", "G"}, {"G", "E"} // цикл
    };

    map<string, vector<string>> graph;
    for (const auto& d : deps) {
        graph[d.from].push_back(d.to);
    }

    vector<vector<string>> cycles;
    set<string> visited, inStack;
    vector<string> stack;

    // Рекурсивная лямбда через захват самой себя
    auto dfs = [&](const auto& self, const string& node) -> void {
        visited.insert(node);
        inStack.insert(node);
        stack.push_back(node);
        auto it = graph.find(node);
        if(it != graph.end()) {
            for (const auto& neigh : it->second) {
                if (inStack.count(neigh)) {
                    auto pos = find(stack.begin(), stack.end(), neigh);
                    if (pos != stack.end())
                        cycles.push_back(vector<string>(pos, stack.end()));
                } else if (!visited.count(neigh)) {
                    self(self, neigh);
                }
            }
        }
        stack.pop_back();
        inStack.erase(node);
    };

    for (const auto& pr : graph) {
        if (!visited.count(pr.first))
            dfs(dfs, pr.first);
    }

    cout << "Циклы:\n";
    for (const auto& cyc : cycles) {
        for (const auto& s : cyc) cout << s << " ";
        if (!cyc.empty()) cout << cyc.front();
        cout << "\n";
    }
}