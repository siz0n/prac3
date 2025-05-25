#include "all.h"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

void dictionary() {
    using Dict = map<string, int>;
    vector<Dict> dicts = {
        {{"a", 2}, {"b", 3}, {"c", 5}},
        {{"a", 2}, {"b", 8}, {"d", 1}},
        {{"a", 7}, {"c", 5}, {"d", 1}}
    };

    map<string, set<int>> all_values;
    for_each(dicts.begin(), dicts.end(), [&](const Dict& d){
        for_each(d.begin(), d.end(), [&](const auto& pr){
            all_values[pr.first].insert(pr.second);
        });
    });

    map<string, int> result;
    vector<string> conflicts;
    auto resolve = [](const set<int>& v) {
        // пользовательская функция: медиана
        vector<int> vals(v.begin(), v.end());
        sort(vals.begin(), vals.end());
        int n = vals.size();
        return vals[n/2];
    };

    for_each(all_values.begin(), all_values.end(), [&](const auto& pr){
        if (pr.second.size() > 1) conflicts.push_back(pr.first);
        result[pr.first] = resolve(pr.second);
    });

    cout << "Итоговый словарь:\n";
    for_each(result.begin(), result.end(), [](const auto& pr){
        cout << pr.first << ": " << pr.second << "\n";
    });
    cout << "Конфликтные ключи: ";
    for_each(conflicts.begin(), conflicts.end(), [](const string& k){
        cout << k << " ";
    });
    cout << "\n";
}