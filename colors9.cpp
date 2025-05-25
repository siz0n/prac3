#include "all.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <cstdint>

using namespace std;

struct RGB { uint8_t r, g, b; };
bool operator==(const RGB& a, const RGB& b) {
    return tie(a.r,a.g,a.b)==tie(b.r,b.g,b.b);
}
namespace std {
    template<> struct hash<RGB> {
        size_t operator()(const RGB& c) const {
            return (c.r << 16) | (c.g << 8) | c.b;
        }
    };
}

void colors9() {
    vector<RGB> pixels = {
        {255,0,0},{255,0,0},{0,255,0},{0,0,255},
        {255,0,0},{0,255,0},{0,255,0},{0,0,255},{0,0,255},{0,0,255}
    };

    map<RGB, int> color_counts;
    for_each(pixels.begin(), pixels.end(), [&](const RGB& px) { color_counts[px]++; });

    vector<pair<RGB, int>> sorted;
    for_each(color_counts.begin(), color_counts.end(), [&](const auto& pr){
        sorted.push_back(pr);
    });
    partial_sort(sorted.begin(), sorted.begin() + min(3UL, sorted.size()), sorted.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    cout << "Топ-3 цвета:\n";
    for_each(sorted.begin(), sorted.begin()+min(3UL, sorted.size()), [](const pair<RGB,int>& pr){
        cout << "RGB(" << +pr.first.r << "," << +pr.first.g << "," << +pr.first.b
                  << "): " << pr.second << "\n";
    });
}