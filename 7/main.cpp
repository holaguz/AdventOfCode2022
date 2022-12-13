#include <bits/stdc++.h>
#include <cmath>
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

struct Node {
    string name;
    vector<Node *> children;
    bool isDir = false;
    ll size;
};

ll dfs(Node *n, int indent = 0) {
    if (!n->isDir)
        return n->size;

    for (const auto &next : n->children) {
        n->size += dfs(next, indent + 1);
    }
    return n->size;
}

void part1(Node *n, ll &size) {
    if (!n->isDir)
        return;

    for (const auto &next : n->children) {
        part1(next, size);
    }

    if (n->size <= 100'000)
        size += n->size;
}

void part2(Node *n, ll &size, int target) {
    if (!n->isDir)
        return;

    for (const auto &next : n->children) {
        part2(next, size, target);
    }

    if (n->size >= target) {
        setmin(size, n->size);
    }
}

int main() {
    string s;
    vector<string> inputs;

    while (getline(cin, s)) {
        if (s.empty())
            continue;
        inputs.push_back(s);
    }

    Node root = {.name = "/", .isDir = true, .size = 0};

    vector<Node *> dirStack = {&root};

    for (int i = 1; i < inputs.size(); ++i) {
        auto line = inputs[i];
        if (line[0] != '$')
            continue;

        if (line.find("cd") != string::npos) {
            auto name =
                string{line.begin() + line.find_last_of(' ') + 1, line.end()};
            if (name == "..") {
                dirStack.pop_back();
            } else {
                auto n = new Node{.name = name, .isDir = true, .size = 0};
                dirStack.back()->children.push_back(n);
                dirStack.push_back(n);
            }
        } else if (line.find("ls") != string::npos) {
            for (int k = i + 1; k < inputs.size() && inputs[k][0] != '$'; ++k) {
                istringstream iss{inputs[k]};
                string a, b;
                iss >> a >> b;

                if (a == "dir") {

                } else {
                    uint32_t size = stoi(a);
                    auto d = new Node{.name = b, .isDir = false, .size = size};
                    dirStack.back()->children.push_back(d);
                }
            }
        }
    }

    dfs(&root);
    ll size{0};
    ll min_size = 1E9;

    ll used = root.size;
    ll free = 70'000'000 - used;
    ll target = 30'000'000 - free;

    cout << "Used " << used << endl;
    cout << "Free " << free << endl;
    cout << "Target " << target << endl;

    part1(&root, size);
    part2(&root, min_size, target);
    cout << "Part 1: " << size << endl;
    cout << "Part 2: " << min_size << endl;
}
