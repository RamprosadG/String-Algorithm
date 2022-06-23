#include<bits/stdc++.h>
using namespace std;

#define ll       long long
#define ull      unsigned ll
#define pii      pair<int, int>
#define pll      pair<ll, ll>
#define mp       make_pair
#define ff       first
#define ss       second
#define sz(x)    (int) x.size()
#define all(v)   v.begin(), v.end()

template <typename T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <typename T> inline void smax(T &a, T b) {a = a > b ? a : b;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << ", ";
	err(++it, args...);
}

template <typename T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

template <typename T, typename TT> inline void Int(T &n, TT &m) { Int(n); Int(m); }
template <typename T, typename TT, typename TTT> inline void Int(T &n, TT &m, TTT &l) { Int(n, m); Int(l); }

const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b) {return (ll) a * b % mod;}

const int inf = (int) 2e9 + 5;
const ll  Inf = (ll) 2e18 + 5;
const int N   = (int) 2e5 + 5;
const int M   = (int) 18;

string s;

int p[N], pn[N], cn[N], ra[N], pre[N], cnt[N], c[M][N];

void buildSA() {
	int n = sz(s);
	for (int i = 0; i < n; ++i) {
		++cnt[s[i]];
	}
	for (int i = 1; i < 300; ++i) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = 0; i < n; ++i) {
		p[--cnt[s[i]]] = i;
	}
	c[0][p[0]] = 0;
	int r = 1;
	for (int i = 1; i < n; ++i) {
		if (s[p[i]] != s[p[i - 1]]) ++r;
		c[0][p[i]] = r - 1;
	}
	for (int k = 0; (1 << k) < n; ++k) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			pn[i] = p[i] - (1 << k);
			if (pn[i] < 0) pn[i] += n;
			++cnt[c[k][pn[i]]];
		}
		for (int i = 1; i < n; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; i >= 0; --i) {
			p[--cnt[c[k][pn[i]]]] = pn[i];
		}
		cn[p[0]] = 0;
		r = 1;
		for (int i = 1; i < n; ++i) {
			pii cur = {c[k][p[i]], c[k][(p[i] + (1 << k)) % n]};
			pii prev = {c[k][p[i - 1]], c[k][(p[i - 1] + (1 << k)) % n]};
			if (cur != prev) ++r;
			cn[p[i]] = r - 1;
		}
		for (int i = 0; i < n; ++i) {
			c[k + 1][i] = cn[i];
		}
	}
}

void kasaiLCP() {
	int n = sz(s);
	for (int i = 0; i < n; ++i) {
		ra[p[i]] = i;
	}
	int k = 0;
	for (int i = 0; i < n; ++i) {
		if (ra[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = p[ra[i] + 1];
		while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
		pre[ra[i]] = k;
		if (k > 0) --k;
	}
}

int lcp(int x, int y) {
	int ans = 0;
	int n = sz(s);
	for (int i = log2(n); i >= 0; --i) {
		if (c[i][x] == c[i][y]) {
			ans += (1 << i);
			x += (1 << i);
			y += (1 << i);
		}
	}
	return ans;
}

int solve() {
	cin >> s;
	s += "$";
	buildSA();
	kasaiLCP();
	int q; Int(q);
	while (q--) {
		int x, y; Int(x, y);
		int ans = lcp(x, y);
		printf("%d\n", ans);
	}
	return 0;
}

int main() {
	//ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int test = 1, tc = 0;
	//Int(test);
	//cin >> test;
	while (test--) {
		//printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}
