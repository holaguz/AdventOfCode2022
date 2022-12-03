#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int get_score(char c) {
    if (c >= 'a' && c <= 'z') {
        return 1 + (c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
        return 27 + (c - 'A');
    }
    assert(false);
}

int main() {
    string s;
    long long ans = 0;
    vector<pair<string, string>> rugsacks;

    while (getline(cin, s)) {
        if (s.empty())
            continue;
        const int n = s.length();
        auto s1 = string{s.begin(), s.begin() + n / 2};
        auto s2 = string{s.begin() + n / 2, s.end()};
        auto p = make_pair(s1, s2);
        rugsacks.push_back(p);
    }

    for (const auto &[st, nd] : rugsacks) {
        set<char> inFirstSack;

        for (const auto &c : st) {
            inFirstSack.insert(c);
        }

        for (const auto &c : nd) {
            if (inFirstSack.count(c)) {
                ans += get_score(c);
                inFirstSack.erase(c);
            }
        }
    }

    cout << "Part 1: " << ans << endl;

    /* Part 2 */
    ans = 0;
    assert(rugsacks.size() % 3 == 0);

    for (int i = 0; i < rugsacks.size(); i += 3) {
        map<char, int> count;

        for (int j = 0; j < 3; ++j) {
            set<char> used;
            auto sack =
                string(rugsacks[i + j].first) + string(rugsacks[i + j].second);

            for (const auto &c : sack) {
                if (used.count(c))
                    continue;

                count[c]++;
                used.insert(c);
            }
        }

        for (const auto &[key, value] : count) {
            ans += value == 3 ? get_score(key) : 0;
        }
    }

    cout << "Part 2: " << ans << endl;
}
