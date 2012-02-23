// www.interviewstreet.com
// Problem: Lego Blocks
// Solution: dynamic programming

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1024
typedef long long LL;
const LL mod = 1000000007;
int n, m;
LL a[N], b[N], c[N];

void solve(){
	int i, j;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	a[0] = 1;
	for (i = 1; i <= m; i++){
		for (j = max(0, i - 4); j < i; j++){
			a[i] = (a[i] + a[j]) % mod;
		}
	}
	for (i = 1; i <= m; i++){
		b[i] = 1;
		for (j = 0; j < n; j++){
			b[i] = b[i] * a[i] % mod;
		}
		c[i] = b[i];
		for (j = 1; j < i; j++){
			c[i] = (c[i] - c[j] * b[i-j] % mod + mod) % mod;
		}
	}
	cout << c[m] << endl;
}

int main(){
	int ca;
	cin >> ca;
	while (ca--){
		cin >> n >> m;
		solve();
	}
}
