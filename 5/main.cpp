#include <bits/stdc++.h>
#include <sstream>
using namespace std;

#define ll long long
#define ld long double

#define ar array
#define vt vector

#define vi vt<int>
#define vc vt<char>
#define vd vt<double>
#define vs vt<string>
#define vll vt<ll>
#define vld vt<ld>
#define vpi vt<pi>

#define pi pair<int, int>
#define pl pair<ll, ll>
#define pd pair<ld, ld>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORN(i, n) FOR(i, 0, n)
#define DFORN(i, n) for (int i = n; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

template <class _, class __> bool setmin(_ &a, const __ &b) {
    return b < a ? a = b, 1 : 0;
}
template <class _, class __> bool setmax(_ &a, const __ &b) {
    return a < b ? a = b, 1 : 0;
}

template <class T> void rd(T &t) { cin >> t; }
template <class T> void rd(vector<T> &v) {
    for (T &el : v)
        cin >> el;
}

template <class T, class H> void rd(vector<pair<T, H>> &v) {
    for (pair<T, H> &el : v)
        cin >> el.first >> el.second;
}

template <class H, class... T> void rd(H &h, T &...t) {
    rd(h);
    rd(t...);
}

#define mp make_pair
#define dq deque
#define pb push_back
#define pf pop_front
#define st first
#define nd second

#define INF 0x3fffffff
#define inf ~0x3fffffff

#define dbg(...)                                                               \
    do {                                                                       \
        if (DEBUG)                                                             \
            fprintf(stderr, __VA_ARGS__);                                      \
    } while (0)
#define dbgnl                                                                  \
    do {                                                                       \
        if (DEBUG)                                                             \
            dbg("\n");                                                         \
    } while (0)

#define DEBUG 1

const int MOD = (int)1e9 + 7;
const int mxn = 100;

using vvc = vector<vector<char>>;

void move(vvc &vec, int from, int to, int count) {
    while (vec[from].size() && count--) {
        vec[to].push_back(vec[from].back());
        vec[from].pop_back();
    }
}

void move2(vvc &vec, int from, int to, int count) {

    const auto beg = vec[from].end() - count;
    const auto end = vec[from].end();

    vec[to].resize(vec[to].size() + count);
    copy(beg, end, vec[to].end() - count);
    vec[from].erase(beg, end);
}

int main() {
    string s;
    vvc stacks(9);
    vector<string> inst;

    while (getline(cin, s)) {
        if (s.empty())
            continue;

        if (s.find('[') != string::npos) {
            for (int i = 1; i < s.length(); i += 4) {
                if (s[i] >= 'A' && s[i] <= 'Z') {
                    stacks[(i - 1) / 4].push_back(s[i]);
                }
            }
        } else if (s[0] == 'm') {
            inst.push_back(s);
        }
    }

    for (auto &s : stacks) {
        reverse(s.begin(), s.end());
    }

    vvc original = stacks;

    for (const auto &i : inst) {
        int from, to, count;
        sscanf(i.c_str(), "move %d from %d to %d", &count, &from, &to);
        from--;
        to--;
        move(stacks, from, to, count);
        move2(original, from, to, count);
    }

    cout << "Part 1: ";

    for (const auto &s : stacks) {
        if (!s.empty()) {
            cout << s.back();
        }
    }

    cout << endl << "Part 2: ";

    for (const auto &s : original) {
        if (!s.empty()) {
            cout << s.back();
        }
    }

    cout << endl;
}
