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
const int M   = (int) 500 + 5;

char pt[M][M], txt[N];

int state = 0;
int node[M * M][26], failure[M * M];
bitset<M> out[M * M];

void build_aho(int n) {
	memset(node, -1, sizeof(node));
	for (int i = 0; i < n; i++) {
		int root = 0, len = strlen(pt[i]);
		for (int j = 0; j < len; j++) {
			int to = pt[i][j] - 'a';
			if (node[root][to] == -1) node[root][to] = ++state;
			root = node[root][to];
		}
		out[root].set(i);
	}
	for (int i = 0; i < 26; i++) {
		if (node[0][i] == -1) node[0][i] = 0;
	}
	queue <int> q;
	for (int i = 0; i < 26; i++) {
		if (node[0][i] != -1 and node[0][i] != 0) {
			failure[node[0][i]] = 0;
			q.push(node[0][i]);
		}
	}
	while (!q.empty()) {
		int root = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (node[root][i] != -1) {
				int fail = failure[root];
				while (node[fail][i] == -1) {
					fail = failure[fail];
				}
				fail = node[fail][i];
				failure[node[root][i]] = fail;
				out[node[root][i]] |= out[fail];
				q.push(node[root][i]);
			}
		}
	}
}

int findstate(int root, int to) {
	while ( node[root][to] == -1) {
		root = failure[root];
	}
	return node[root][to];
}

vector<int> get_result(int n) {
	vector<int> ans(n, 0);
	int root = 0, len = strlen(txt);
	for (int i = 0; i < len; i++) {
		int to = txt[i] - 'a';
		root = findstate(root, to);
		if (out[root] == 0) continue;
		for (int j = 0; j < n; j++) {
			if (out[root].test(j)) ans[j]++;
		}
	}
	return ans;
}

int solve() {
	int n; Int(n);
	for (int i = 0; i < n; i++) {
		scanf("%s", pt[i]);
	}
	scanf("%s", txt);
	build_aho(n);
	vector<int> ans = get_result(n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ans[i]);
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
