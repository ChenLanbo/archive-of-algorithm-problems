// www.interviewstreet.com
// Problem: Equations
// Solution: Number Theory
// 1/x + 1/y = 1/a => xy - a(x + y) + a^2 = a^2
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
#define N 1000000
bool check[N] = { 0 };
int sizePrime, prime[N];
int cnt[N];

void getPrime(){
	int i, j;
	sizePrime = 0;
	for (i = 2; i < N; i++){
		if (!check[i]) prime[sizePrime++] = i;
		for (j = 0; j < sizePrime && i * prime[j] < N; j++){
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

void solve(int n){
	int i, j;
	LL ans = 1;
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < sizePrime && prime[i] <= n; i++){
		j = n;
		while (j > 0){
			cnt[i] += j / prime[i];
			j /= prime[i];
		}
	}
	for (i = 0; i < sizePrime && prime[i] <= n; i++){
		ans = ans * (cnt[i]<<1|1) % 1000007;
	}
	cout << ans << endl;
}

int main(){
	int n;
	getPrime();
	while (cin >> n){
		solve(n);
	}
}

