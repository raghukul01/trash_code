// Wed Mar 6 16:21:25 IST 2019
#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

const int M = 1e9 + 7;
const int N = 2e5 + 5;

int n;
vector<int> G[N];
vector<pair<int,pair<int,int>>> T[N];
vector<int> C(N);
int child[N];

void clean() {
	for(int i = 0;i < n;i++) {
		G[i].clear();
		T[i].clear();
	}
}

int binpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1)
            res = (1LL * res * a)%M;
        a = (1LL * a * a)%M;
        b >>= 1;
    }
    return res;
}

int modInv(int x) {
	return binpow(x, M-2);
}

void pre(int u, int p) {
	if(G[u].size() == 1 && p != -1) {
		T[u].push_back({0, {0, 0}});
		C[u] = 1;
	}
	else {
		C[u] = 1;

		for(auto x: G[u])
			if(x != p)
				pre(x, u);
		
		T[u].push_back({1, {0, 0}});	
		int m = 0;	
		for(auto x: G[u])
			if(x != p) {
				child[m++] = x;
				C[u] += C[x];
			}
		vector<pair<int,pair<int,int>>>::iterator ptr[m];
		int val = 0;
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		for(int i = 0;i < m;i++) {
			ptr[i] = T[child[i]].begin();
			pq.push({(*(ptr[i])).second.second, i});
			val += (*(ptr[i])).first;
		}
		int mn = 0, mx, idx;
		while(true) {
			if(pq.empty())
				break;
			pair<int,int> curr = pq.top();
			mx = curr.first;
			if((T[u].back()).first == val)
				T[u][T[u].size()-1] = {val, {T[u].back().second.first, mx+1}};
			else
				T[u].push_back({val, {mn+1, mx+1}});
			mn = mx+1;
			while(!pq.empty() && (pq.top().first == mx)) {
				curr = pq.top();
				pq.pop();
				val -= (*ptr[curr.second]).first;
				ptr[curr.second]++;
				if(ptr[curr.second] != T[child[curr.second]].end()) {
					val += (*ptr[curr.second]).first;
					pq.push({(*(ptr[curr.second])).second.second, curr.second});
				}

			}
		}
	}
}

int xk, xk1, xk2, xk3, xk4, v1, diff1, diff2, v2;

int get_val(int& k, int& l, int& r, int& pw, int& x) {
	if(x == 1) {
		int ans = ((1LL*(r+l)*(r-l+1))/2LL)%M;
		return (1LL*ans*k)%M;
	}
	xk = binpow(x, k);
	v1 = (xk - 1)%M;
	v1 = (1LL*v1*modInv(x-1))%M;

	xk1 = binpow(x, pw - ((r-l+1)*k) + 1);
	xk2 = binpow(x, (r-l)*k);
	xk3 = (1LL*xk*xk1)%M;
	xk4 = modInv(xk-1);

	v2 = (1LL*r*((1LL*xk2*xk3)%M))%M;
	diff1 = (1LL*l*xk1)%M; 
	diff2 = (((1LL*xk3*(xk2 - 1))%M)*xk4)%M;

	v2 = (((1LL*v2 - 1LL*diff2 - 1LL*diff1 + 3LL*M)%M)*xk4)%M;
	pw -= (r-l+1)*k;
	return (1LL*v2*v1)%M;
}

int pw, val;

int get(int& u, int& x) {
	pw = C[u] - 1;
	val = 0;
	for(int i = T[u].size()-1;i >= 0;i--)
		val = (val + get_val(T[u][i].first, T[u][i].second.first, T[u][i].second.second, pw, x))%M;
	
	return val;
}


int main() {
    ios_base::sync_with_stdio(false),cin.tie(0),cout.precision(17);
    int tests, q;
    cin >> tests;
    int u, v;
    while(tests--) {
    	cin >> n >> q;
    	clean();
    	for(int i = 0;i < n-1;i++) {
    		cin >> u >> v;
    		u--; v--;
    		G[u].push_back(v);
    		G[v].push_back(u);
    	}
    	pre(0, -1);
    	int ans = 0;
    	while(q--) {
    		cin >> u >> v;
    		u ^= ans;
    		v ^= ans;
    		u--;
    		ans = get(u, v);
    		cout << ans << endl;
    	}
    }
    return 0;
}
