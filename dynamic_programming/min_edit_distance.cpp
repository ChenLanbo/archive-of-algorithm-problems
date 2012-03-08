// Minimum editing distance of two strings(Levenshtein)
#include <iostream>
#include <cstring>
using namespace std;
#define N 1000
#define MIN(x, y) ((x) < (y) ? (x) : (y))
int m, n, dp[2][N];
char str1[N], str2[N];

int DP(){
	int i, j, pre, cur;
	for ( i = 0; i <= n; i++ )
		dp[0][i] = i;
	pre = 0, cur = 1;
	for (i = 1; i <= m; i++){
		dp[cur][0] = i;
		for (j = 1; j <= n; j++){
			if (str1[i-1] == str2[j-1])
				dp[cur][j] = MIN(dp[pre][j-1], MIN(dp[pre][j] + 1, dp[cur][j-1] + 1));
			else
				dp[cur][j] = MIN(dp[pre][j-1] + 1, MIN(dp[pre][j] + 1, dp[cur][j-1] + 1));
		}
		pre ^= 1;
		cur ^= 1;
	}
	return dp[pre][n];
}

int main(){
	cin >> str1;
	cin >> str2;
	cout << DP() << endl;
}
