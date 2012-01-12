// www.interviewstreet.com
// Problem: Grid Walking
// Solution: dynamic programming, combinatorics
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 16
typedef long long LL;
const LL mod = 1000000007;
int n, m;
int xi[N], di[N];
LL step[304][104];
LL cnt[N][304];
LL dp[N][304];
LL co[512][512] = { 0 };

void init(){
	int i, j, k;

	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; i++){
		//init
		for (j = 0; j <= m; j++)
			for (k = 0; k <= di[i]; k++)
				step[j][k] = 0;

		step[0][xi[i]] = 1;
		cnt[i][0] = 1;

		for (j = 0; j < m; j++){
			for (k = 1; k <= di[i]; k++){
				if (step[j][k] == 0) continue;
				if (k - 1 > 0){
					step[j+1][k-1] = (step[j+1][k-1] + step[j][k]) % mod;
				}
				if (k + 1 <= di[i]){
					step[j+1][k+1] = (step[j+1][k+1] + step[j][k]) % mod;
				}
			}

			for (k = 1; k <= di[i]; k++){
				cnt[i][j+1] = (cnt[i][j+1] + step[j+1][k]) % mod;
			}
		}
	}
}

void solve(){
	int i, j, k;
	memset(dp, 0, sizeof(dp));
	for (i = 0; i <= m; i++)
		dp[0][i] = cnt[0][i];
	for (i = 0; i < n - 1; i++){
		for (j = 0; j <= m; j++){
			for (k = 0; k <= m - j; k++){
				dp[i+1][j+k] = (dp[i+1][j+k] + dp[i][j] * cnt[i+1][k] % mod * co[j+k][k] % mod) % mod;
			}
		}
	}
	//puts("ANS");
	cout << dp[n-1][m] << endl;
}

int main(){
	int t, i, j;

	co[0][0] = 1;
	for (i = 1; i < 512; i++){
		co[i][0] = 1;
		for (j = 1; j <= i; j++){
			co[i][j] = (co[i-1][j] + co[i-1][j-1]) % mod;
		}
	}

	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> xi[i];
		for (int i = 0; i < n; i++) cin >> di[i];
		init();
		solve();
	}
}

