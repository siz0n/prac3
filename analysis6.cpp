#include "all.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Response {
    string team;
    int delayMinutes;
    bool acknowledged;
    string dayOfWeek; // "Mon", "Tue", ...
};

struct ReportStats {
    double avgAckDelay;      // -1.0 means n/a
    double medianAckDelay;   // -1.0 means n/a
    double ackPercent;
    int totalRequests;
};

void analysis6() {
    vector<Response> responses = {
        {"A", 10, true, "Mon"}, {"A", 15, true, "Mon"}, {"A", 20, false, "Mon"},
        {"A", 12, true, "Tue"}, {"A", 14, true, "Tue"}, {"A", 13, true, "Tue"},
        {"B", 30, true, "Mon"}, {"B", 40, false, "Mon"}, {"B", 35, true, "Mon"},
        {"B", 50, true, "Tue"}, {"B", 44, true, "Tue"}, {"B", 39, false, "Tue"},
        {"C", 25, true, "Mon"}, {"C", 28, true, "Mon"}, {"C", 27, true, "Mon"},
        {"C", 22, false, "Mon"}, {"C", 21, true, "Tue"}, {"C", 22, false, "Tue"}
    };
    int N = 3;
    map<string, map<string, ReportStats>> result;

    // Группировка
    map<string, map<string, vector<Response>>> grouped;
    for (const auto& r : responses) {
        grouped[r.team][r.dayOfWeek].push_back(r);
    }

    // Анализ
    for (const auto& teamPair : grouped) {
        const auto& team = teamPair.first;
        const auto& days = teamPair.second;
        for (const auto& dayPair : days) {
            const auto& day = dayPair.first;
            const auto& vec = dayPair.second;
            if ((int)vec.size() < N) continue;
            vector<int> ackDelays;
            int ackCount = 0;
            for (const auto& r : vec) {
                if (r.acknowledged) {
                    ackDelays.push_back(r.delayMinutes);
                    ackCount++;
                }
            }
            double avg = -1.0, med = -1.0;
            if (!ackDelays.empty()) {
                double sum = 0.0;
                for (size_t i = 0; i < ackDelays.size(); ++i)
                    sum += ackDelays[i];
                avg = sum / ackDelays.size();
                sort(ackDelays.begin(), ackDelays.end());
                if (ackDelays.size() % 2)
                    med = ackDelays[ackDelays.size() / 2];
                else
                    med = 0.5 * (ackDelays[ackDelays.size() / 2 - 1] + ackDelays[ackDelays.size() / 2]);
            }
            double percent = 100.0 * ackCount / vec.size();
            result[team][day] = { avg, med, percent, (int)vec.size() };
        }
    }

    for (const auto& teamPair : result) {
        const auto& team = teamPair.first;
        const auto& days = teamPair.second;
        cout << "Команда: " << team << "\n";
        for (const auto& dayPair : days) {
            const auto& day = dayPair.first;
            const auto& stat = dayPair.second;
            cout << "  День: " << day << ", Всего: " << stat.totalRequests
                 << ", % подтвержд: " << stat.ackPercent
                 << ", Среднее: ";
            if (stat.avgAckDelay >= 0)
                cout << stat.avgAckDelay;
            else
                cout << "n/a";
            cout << ", Медиана: ";
            if (stat.medianAckDelay >= 0)
                cout << stat.medianAckDelay;
            else
                cout << "n/a";
            cout << "\n";
        }
    }
}