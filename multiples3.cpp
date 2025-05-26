#include "all.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void miltiples3() {
    vector<int> nums = {3, 6, 18, 36, 72, 144, 9, 27, 81, 162};
    sort(nums.begin(), nums.end());

    vector<int> max_chain;

    
    auto find_chain = [&](const auto& self, vector<int>& curr, int idx, vector<int>& best) -> void {
        for (size_t i = idx + 1; i < nums.size(); ++i) {
            if (nums[i] % curr.back() == 0) {
                curr.push_back(nums[i]);
                self(self, curr, i, best);
                curr.pop_back();
            }
        }
        if (curr.size() > best.size()) best = curr;
    };

    for (size_t i = 0; i < nums.size(); ++i) {
        vector<int> curr = {nums[i]};
        find_chain(find_chain, curr, i, max_chain);
    }

    cout << "Максимальная цепочка кратных: ";
    for_each(max_chain.begin(), max_chain.end(), [](int x){ cout << x << " "; });
    cout << "\n";
}
