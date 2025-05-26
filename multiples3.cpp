
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

struct User {
    int id;
    string name;
    vector<int> friends; 
};

// Поиск пользователя по id
auto find_user(const vector<User>& users, int id) {
    return find_if(users.begin(), users.end(), [id](const User& u) { return u.id == id; });
}

// Кратчайшая цепочка знакомств без std::queue (волнами через два вектора)
vector<int> shortest_chain(const vector<User>& users, int user_from, int user_to) {
    map<int, int> prev;
    set<int> visited;
    vector<int> current_wave = { user_from };
    visited.insert(user_from);

    bool found = false;
    while (!current_wave.empty() && !found) {
        vector<int> next_wave;
        for (int curr_id : current_wave) {
            if (curr_id == user_to) {
                found = true;
                break;
            }
            auto it = find_user(users, curr_id);
            if (it == users.end()) continue;
            for (int friend_id : it->friends) {
                if (!visited.count(friend_id)) {
                    visited.insert(friend_id);
                    prev[friend_id] = curr_id;
                    next_wave.push_back(friend_id);
                }
            }
        }
        current_wave = move(next_wave);
    }

    // Восстановим путь
    vector<int> path;
    if ((!prev.count(user_to) && user_from != user_to) && user_from != user_to) return path; // не найдено

    for (int at = user_to; ; at = prev[at]) {
        path.push_back(at);
        if (at == user_from) break;
    }
    reverse(path.begin(), path.end());
    return path;
}

// Поиск пары пользователей с максимальным количеством общих друзей
tuple<int, int, vector<int>> max_common_friends(const vector<User>& users) {
    int max_count = -1;
    int user1 = -1, user2 = -1;
    vector<int> max_common;

    for (size_t i = 0; i < users.size(); ++i) {
        set<int> f1(users[i].friends.begin(), users[i].friends.end());
        for (size_t j = i + 1; j < users.size(); ++j) {
            set<int> f2(users[j].friends.begin(), users[j].friends.end());
            vector<int> common;
            set_intersection(
                f1.begin(), f1.end(),
                f2.begin(), f2.end(),
                back_inserter(common),
                [](int a, int b) { return a < b; }
            );
            if ((int)common.size() > max_count) {
                max_count = (int)common.size();
                user1 = users[i].id;
                user2 = users[j].id;
                max_common = move(common);
            }
        }
    }
    return {user1, user2, max_common};
}

int main() {
    vector<User> users = {
        {1, "Alice", {2, 3}},
        {2, "Bob", {1, 3, 4}},
        {3, "Charlie", {1, 2, 4}},
        {4, "Diana", {2, 3, 5}},
        {5, "Eve", {4}}
    };

    cout << "Введите id двух пользователей для поиска цепочки: ";
    int from_id, to_id;
    cin >> from_id >> to_id;

    auto chain = shortest_chain(users, from_id, to_id);
    if (chain.empty()) {
        cout << "Цепочка не найдена.\n";
    } else {
        cout << "Кратчайшая цепочка: ";
        for (size_t i = 0; i < chain.size(); ++i) {
            auto it = find_user(users, chain[i]);
            if (it != users.end())
                cout << it->name;
            else
                cout << chain[i];
            if (i + 1 < chain.size()) cout << " -> ";
        }
        cout << '\n';
    }

    // Поиск пары с максимальным числом общих друзей
    auto [id1, id2, common] = max_common_friends(users);
    if (id1 != -1 && id2 != -1) {
        auto u1 = find_user(users, id1);
        auto u2 = find_user(users, id2);
        cout << "Пара с максимальным числом общих друзей: "
                  << (u1 != users.end() ? u1->name : to_string(id1)) << " и "
                  << (u2 != users.end() ? u2->name : to_string(id2))
                  << " (общих: " << common.size() << "): ";
        for (int fid : common) {
            auto fn = find_user(users, fid);
            if (fn != users.end()) cout << fn->name << ' ';
            else cout << fid << ' ';
        }
        cout << '\n';
    }
}
