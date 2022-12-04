#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s;
    vector<pair<int, int>> intervals;

    while (getline(cin, s)) {
        if (s.empty())
            continue;
        int a, b, c, d;
        sscanf(s.c_str(), "%d-%d,%d-%d", &a, &b, &c, &d);

        intervals.push_back({a, b});
        intervals.push_back({c, d});
    }

    long long count = 0, overlap = 0;
    for (int i = 0; i < intervals.size(); i += 2) {
        auto a = intervals[i];
        auto b = intervals[i + 1];

        if (a.first >= b.first && a.second <= b.second)
            /* a contained in b */
            count++;
        else if (b.first >= a.first && b.second <= a.second)
            /* b contained in a */
            count++;

        if (a.first >= b.first && a.first <= b.second)
            /* some of a contained in b */
            overlap++;
        else if (b.first >= a.first && b.first <= a.second)
            /* some of b contained in a */
            overlap++;
    }

    cout << "Part 1: " << count << endl;
    cout << "Part 2: " << overlap << endl;
}
