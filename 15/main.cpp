#include <bits/stdc++.h>
#define LOCAL

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
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}
template <class _, class __> bool setmax(_ &a, const __ &b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> void read(T &t) { cin >> t; }

template <class H, class... T> void read(H &h, T &...t) {
  read(h);
  read(t...);
}

template <class T> void read(vector<T> &v) {
  for (T &el : v)
    read(el);
}

template <class T, class H> void read(pair<T, H> &v) {
  read(v.first, v.second);
}

void dbg(const char *fmt, char end = '\0') {
#ifndef LOCAL
  return;
#endif
  fprintf(stderr, "%s", fmt);
}

template <class T> void dbg(const char *fmt, const T &t) {
#ifndef LOCAL
  return;
#endif
  fprintf(stderr, fmt, t);
}

template <class T> void dbg(const T &t) {
#ifndef LOCAL
  return;
#endif
  cerr << t;
}

template <class T, class H> void dbg(const pair<T, H> &th) {
#ifndef LOCAL
  return;
#endif
  cerr << "(" << th.first << ", " << th.second << ")";
}

template <class T> void dbg(const vector<T> &a) {
#ifndef LOCAL
  return;
#endif
  cerr << "[";

  for (auto it = begin(a); it != end(a); ++it) {
    if (!is_arithmetic<decltype(*it)>()) {
      cerr << ", " + 2 * (it == begin(a));
      dbg(*it);
    } else
      dbg(*it);
  }
  cerr << "]";
}

template <class T> void dbg(set<T> &a) {
#ifndef LOCAL
  return;
#endif
  cerr << "[";

  for (auto it = begin(a); it != end(a); ++it) {
    if (!is_arithmetic<decltype(*it)>()) {
      cerr << ", " + 2 * (it == begin(a));
      dbg(*it);
    } else
      dbg(*it);
  }
  cerr << "]";
}

template <class T, class... H> void dbg(const T &t, const H &...h) {
  dbg(t);
  dbg(" ");
  dbg(h...);
}

#define mp make_pair
#define dq deque
#define pb push_back
#define pf pop_front
#define st first
#define nd second

#define INF 0x3fffffff
#define inf ~0x3fffffff

const char nl = '\n';

#define pterr(...)                                                             \
  dbg("[%s: ", #__VA_ARGS__);                                                  \
  dbg(__VA_ARGS__);                                                            \
  dbg(" ]\n")

class dumb {
public:
  vector<dumb> children;
  string remaining;
};

inline ll dist(const pi &a, const pi &b) {
  return (abs(a.st - b.st) + abs(a.nd - b.nd));
}

inline bool inside(const pi &p, const pi &s, const ll range) {
  return (dist(p, s) <= range);
}

pi merge(const pi &a, const pi &b) {
  /* assert(a.st >= a.nd); */
  /* assert(b.st >= b.nd); */
  return {a.st, b.nd};
}

void solve() {
  int n;
  cin >> n;
  vpi beacons(n), sensors(n);
  vi range(n);
  set<pi> bset;
  set<pi> sset;

  pi rangex = {1E9, -1E9}, rangey = {1E9, -1E9};
  FORN(i, n) {
    read(sensors[i]);
    read(beacons[i]);
    range[i] = dist(sensors[i], beacons[i]);
    bset.insert(beacons[i]);
    sset.insert(sensors[i]);

    setmin(rangex.st, sensors[i].st - range[i]);
    setmax(rangex.nd, sensors[i].nd + range[i]);

    setmin(rangey.st, sensors[i].st - range[i]);
    setmax(rangey.nd, sensors[i].nd + range[i]);

    pterr(i, sensors[i], beacons[i], range[i]);
  }

  const auto y = 2000000;
  unsigned ll ans = 0;

  pterr(rangex);
  pterr(rangey);

  for (int x = rangex.st; x < rangex.nd; ++x) {
    const pi p = {x, y};
    for (int i = 0; i < sensors.size(); ++i) {
      if (inside(p, sensors[i], range[i]) && !bset.count(p)) {
        ans++;
        break;
      }
    }
  }

  cout << "Part 1: " << ans << endl;

  struct PiComp {
    typedef std::pair<int, int> const &param_type;

    bool operator()(const pi &a, const pi &b) const {
      if (a.st != b.st) {
        return a.st <= b.st;
      } else {

        return a.nd <= b.nd;
      }
    }
  };

  /* key is ypos, value is vector of intervals */
  map<int, vt<pi>> ivmap;

  for (int i = 0; i < n; ++i) {
    const pi &c = sensors[i];
    const int r = range[i];
    /* pterr(i); */

    for (int dy = 0; dy <= r; ++dy) {
      int dx = r - dy;
      int begx = max(0, c.st - dx - 1);

      int endx = min(c.st + dx, 4000000);
      /* int endx = min(c.st + dx, 20); */

      if (c.nd + dy <= 4000000)
        ivmap[c.nd + dy].emplace_back(begx, endx);
      if (c.nd - dy >= 0)
        ivmap[c.nd - dy].emplace_back(begx, endx);
    }
  }

  for (auto &[y, ivals] : ivmap) {
    if (y > 4000000)
      break;

    sort(all(ivals), PiComp{});
    /* pterr(y, ivals); */
    auto it = ivals.begin();

    while (it != ivals.end()) {
      auto next = it + 1;

      if (next == ivals.end()) {
        ++it;
        break;
      }

      if (it->nd >= next->st) {
        it->nd = max(it->nd, next->nd);
        it = ivals.erase(next) - 1;
      } else {
        ++it;
      }
    }
    /* pterr(y, ivals); */
  }

  for (auto &[k, v] : ivmap) {
    if (v.size() > 1) {
      pterr(k, v, v.size());
      ans = ((unsigned ll)v[1].st * 4000000ull) + (unsigned ll)k;
      break;
    }
  }

  cout << "Part 2: " << ans << endl;
}

int main() {
  using us = std::chrono::microseconds;

  auto start = std::chrono::high_resolution_clock::now();
  solve();
  auto end = std::chrono::high_resolution_clock::now();
  ld dur = std::chrono::duration_cast<us>(end - start).count() / 1000.0;
  dbg("after %4.1LF ms\n", dur);
}
