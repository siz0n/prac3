#include "all.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct ConfigEntry {
    string key;
    string value;
    vector<ConfigEntry> children;
};

void tree4() {
    using namespace std;
    // Пример данных
    vector<ConfigEntry> oldConf = {
        {"root", "", {
            {"section1", "", {
                {"key1", "val1", {}},
                {"key2", "val2", {}}
            }},
            {"section2", "", {
                {"key3", "val3", {}}
            }}
        }}
    };

    vector<ConfigEntry> newConf = {
        {"root", "", {
            {"section1", "", {
                {"key1", "val1", {}},
                {"key2", "val2_changed", {}},
                {"key4", "val4", {}}
            }},
            {"section3", "", {
                {"key5", "val5", {}}
            }}
        }}
    };

    set<string> added, removed, modified;

    // Рекурсивная лямбда через захват самой себя (C++14+)
    auto diff = [&](const auto& self, const vector<ConfigEntry>& oldV, const vector<ConfigEntry>& newV, string path) -> void {
        map<string, ConfigEntry> oldMap, newMap;
        for_each(oldV.begin(), oldV.end(), [&](const ConfigEntry& e){ oldMap[e.key]=e; });
        for_each(newV.begin(), newV.end(), [&](const ConfigEntry& e){ newMap[e.key]=e; });

        for_each(newMap.begin(), newMap.end(), [&](const auto& pr){
            if (oldMap.find(pr.first) == oldMap.end())
                added.insert(path + "." + pr.first);
        });

        for_each(oldMap.begin(), oldMap.end(), [&](const auto& pr){
            if (newMap.find(pr.first) == newMap.end())
                removed.insert(path + "." + pr.first);
        });

        for_each(newMap.begin(), newMap.end(), [&](const auto& pr){
            auto it = oldMap.find(pr.first);
            if (it != oldMap.end()) {
                if (pr.second.value != it->second.value)
                    modified.insert(path + "." + pr.first);
                self(self, it->second.children, pr.second.children, path + "." + pr.first);
            }
        });
    };

    diff(diff, oldConf, newConf, "root");

    cout << "Добавленные: "; for (auto& s : added) cout << s << " "; cout << "\n";
    cout << "Удалённые: "; for (auto& s : removed) cout << s << " "; cout << "\n";
    cout << "Изменённые: "; for (auto& s : modified) cout << s << " "; cout << "\n";
}