#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

struct Player {
    string name;
    int hp;
    int attack;
    int team;
    bool alive() const { return hp > 0; }
};

struct LogEntry {
    string attacker;
    string target;
    int damage;
    int attacker_team;
};

int main() {
    
    vector<Player> players = {
        {"Egor",   60, 10, 1},
        {"Vasya",     50, 15, 1},
        {"Kiril",   55, 12, 1},
        {"Vlad",   65, 13, 2},
        {"Petya",   45, 18, 2},
        {"Anya",   70,  9, 2}
    };

    //очередь ходов по указателям (живые игроки)
    deque<Player*> turn_queue;
    for (auto& p : players) turn_queue.push_back(&p);

    vector<LogEntry> battle_log;
    bool battle_ongoing = true;
    int round = 1;

    while (battle_ongoing) {
        for (auto it = turn_queue.begin(); it != turn_queue.end(); ++it) {
            Player* attacker = *it;
            if (!attacker->alive()) continue;

            // поиск живых
            vector<Player*> enemies;
            for (auto& p : players)
                if (p.team != attacker->team && p.alive())
                    enemies.push_back(&p);

            if (enemies.empty()) {
                
                battle_ongoing = false;
                break;
            }

            // поиск мин хп
            auto target_it = min_element(
                enemies.begin(), enemies.end(),
                [](Player* a, Player* b) { return a->hp < b->hp; }
            );
            Player* target = *target_it;

            // Атака
            int damage = attacker->attack;
            target->hp -= damage;
            if (target->hp < 0) target->hp = 0;

            battle_log.push_back({attacker->name, target->name, damage, attacker->team});
            
        }
        // убираем мертвых
        round++;
        
    }

    // Опоиск команды которая победила
    int alive_team = -1;
    for (const auto& p : players) {
        if (p.alive()) {
            alive_team = p.team;
            break;
        }
    }

    cout << "\nБитва завершена! Победила команда " << alive_team << "\n\n";

    
    int teams[3] = {0, 0, 0}; 
    for (int t = 1; t <=2; ++t) {
        teams[t] = accumulate(
            battle_log.begin(), battle_log.end(), 0,
            [t](int sum, const LogEntry& log) {
                return sum + (log.attacker_team == t ? log.damage : 0);
            }
        );
    }
    cout << "Статистика по урону:\n";
    cout << "Команда 1: " << teams[1] << " урона\n";
    cout << "Команда 2: " << teams[2] << " урона\n";

    // Лог атак
    cout << "\nИстория атак:\n";
    for (const auto& log : battle_log) {
        cout << log.attacker << " (Team " << log.attacker_team << ") -> " 
                  << log.target << " : " << log.damage << " урона\n";
    }

    return 0;
}
