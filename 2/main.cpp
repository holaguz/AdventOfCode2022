#include <map>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
using ps = pair<string, string>;

int main() {
    string s;
    long long score = 0;
    vector<ps> plays;

    map<string, string> wins = {
        {"A", "C"}, /* rock beats scissors  */
        {"B", "A"}, /* paper beats rock     */
        {"C", "B"}, /* scissors beats paper */
    };

    map<string, string> losses = {
        {"A", "B"},
        {"B", "C"},
        {"C", "A"},
    };

    map<string, int> scores = {
        {"A", 1},
        {"B", 2},
        {"C", 3},
    };

    while (getline(cin, s)) {
        if (s.empty())
            continue;
        string p1, p2;
        istringstream iss{s};
        iss >> p1 >> p2;
        plays.emplace_back(p1, p2);
    }

    for (auto [p1, p2] : plays) {
        if (p2 == "X") {
            p2 = "A";
        } else if (p2 == "Y") {
            p2 = "B";
        } else if (p2 == "Z") {
            p2 = "C";
        }

        if (wins[p2] == p1) {
            score += 6;
        } else if (p1 == p2) {
            score += 3;
        } else {
            score += 0;
        }
        score += scores[p2];
    }

    cout << "Part 1: " << score << endl;

    score = 0;
    for (auto [p1, p2] : plays) {
        string target = p2;
        if (p2 == "X") {
            score += 0;
            p2 = wins[p1];
        } else if (p2 == "Y") {
            score += 3;
            p2 = p1;
        } else if (p2 == "Z") {
            score += 6;
            p2 = losses[p1];
        }
        score += scores[p2];
    }

    cout << "Part 2: " << score << endl;
}

