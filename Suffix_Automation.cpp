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

map<int, int> node[N];
int len[N], link[N], state, last;

void init() {
	state = last = 1;
	len[1] = 0;
	link[1] = -1;
}

void Insert(string& s, int p) {
	int cur = ++state;
	len[cur] = len[last] + 1;
	int c = s[p] - 'a';
	p = last;
	while (p != -1 and !node[p].count(c)) {
		node[p][c] = cur;
		p = link[p];
	}
	if (p == -1) {
		link[cur] = 1;
	}
	else {
		int q = node[p][c];
		if (len[p] + 1 == len[q]) {
			link[cur] = q;
		}
		else {
			int clone = ++state;
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			node[clone] = node[q];
			while (p != -1 and node[p][c] == q) {
				node[p][c] = clone;
				p = link[p];
			}
			link[q] = link[cur] = clone;
		}
	}
	last = cur;
}

int dp[N];

int call(int u) {
	int& ans = dp[u];
	if (ans) return ans;
	ans = 1;
	for (auto v : node[u]) {
		ans += call(v.ss);
	}
	return ans;
}

int solve() {
	string s; cin >> s;
	init();
	int n = sz(s);
	for (int i = 1; i <= 2 * n; ++i) {
		dp[i] = 0;
		node[i].clear();
	}
	for (int i = 0; i < n; ++i) {
		Insert(s, i);
	}
	printf("%d\n", call(1) - 1);
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
