#include <algorithm>
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

bool is_valid(const vs &grid, int x, int y) {
    auto cols = grid.size();
    auto rows = grid[0].size();
    assert(x < rows && x >= 0 && y < cols && y >= 0);

    int visible = 4;
    auto height = grid[y][x];

    for (int i = 0; i < x; ++i) {
        if (grid[y][i] >= height) {
            --visible;
            break;
        }
    }
    for (int i = rows - 1; i > x; --i) {
        if (grid[y][i] >= height) {
            --visible;
            break;
        }
    }
    for (int i = 0; i < y; ++i) {
        if (grid[i][x] >= height) {
            --visible;
            break;
        }
    }
    for (int i = cols - 1; i > y; --i) {
        if (grid[i][x] >= height) {
            --visible;
            break;
        }
    }
    return visible > 0;
}

long long score(const vs &grid) {
    auto rows = grid.size();
    auto cols = grid[0].size();
    ll max_score = 0;
    for (int x = 1; x < cols - 1; ++x) {
        for (int y = 1; y < rows - 1; ++y) {

            auto cur = grid[y][x];
            ll left = 0, up = 0, down = 0, right = 0;

            for (int i = x - 1; i >= 0; --i) {
                left++;
                if (grid[y][i] >= cur)
                    break;
            }

            for (int i = x + 1; i < cols; ++i) {
                right++;
                if (grid[y][i] >= cur)
                    break;
            }

            for (int j = y - 1; j >= 0; --j) {
                up++;
                if (grid[j][x] >= cur)
                    break;
            }

            for (int j = y + 1; j < rows; ++j) {
                down++;
                if (grid[j][x] >= cur)
                    break;
            }
            max_score = max(max_score, left * down * up * right);
        }
    }
    return max_score;
}

int main() {
    string s;
    vs grid;

    while (getline(cin, s)) {
        if (s.empty())
            continue;
        grid.push_back(s);
    }

    const auto rows = grid.size();
    const auto cols = grid[0].size();

    ll ans = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            ans += is_valid(grid, y, x);
        }
    }

    cout << "Part 1: " << ans << endl;
    cout << "Part 2: " << score(grid) << endl;
}
