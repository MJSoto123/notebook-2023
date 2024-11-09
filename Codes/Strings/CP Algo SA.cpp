#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pii> vii;

template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

const int MAX_LEN = 500000 + 10;
struct state{
	int len = 0; 
	int link = 0; 
	map<char, int> nxt; 
};

state st[MAX_LEN * 2];
int sz = 0, last = 0;

void SA_init() {
	st[0].len = 0; 
	st[0].link = -1; 
	sz++; 
	last = 0;
}

void SA_extend(char c) {  
	int cur = sz++; 
	st[cur].len = st[last].len + 1; 
	int p = last; 
	while(p != -1 && !st[p].nxt.count(c)) {
		st[p].nxt[c] = cur; 
		p = st[p].link; 
	}

	if(p == -1) {
		st[cur].link = 0; 
	}else{
		int q = st[p].nxt[c]; 
		if(st[p].len + 1 == st[q].len) { 
			st[cur].link = q; 
		}else{
			int clone = sz++; 
			st[clone].len = st[p].len + 1; 
			st[clone].nxt = st[q].nxt; 
			st[clone].link = st[q].link; 
			while(p != -1 && st[p].nxt[c] == q) {
				st[p].nxt[c] = clone; 
				p = st[p].link; 
			}
			st[q].link = st[cur].link = clone; 
		}
	}
	last = cur; 
}

bool exists(const string& s) {
	int cur = 0; 
	for(char c : s) {
		if(st[cur].nxt.count(c)) cur = st[cur].nxt[c]; 
		else return false; 
	}
	return true; 
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	string t; cin >> t; 
	SA_init();
	for(char c : t) SA_extend(c);
	int qq; cin >> qq; 
	while(qq--) {
		string s; cin >> s; 
		if(exists(s)) cout << "YES\n"; 
		else cout << "NO\n"; 
	}
}
