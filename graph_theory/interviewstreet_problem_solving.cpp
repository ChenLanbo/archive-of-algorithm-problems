// www.interviewstreet.com
// Problem: Problem Solving
// Solution: Bipartite Matching
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 308
#define ABS(x) ((x) < 0 ? -(x) : (x))
int n, k, vi[N], mp[N][N];
int cx[N], cy[N], visit[N];

void init()
{
	int i, j;
	memset(mp, 0, sizeof(mp));
	for (i = 0; i < n; i++){
		for (j = i + 1; j < n; j++){
			if (ABS(vi[i] - vi[j]) >= k){
				// cout << i << " " << j << endl;
				mp[i][j] = 1;
			}
		}
	}
}

int path(int u)
{
	int v;
	for (v = 0; v < n; v++){
		if (!mp[u][v]) continue;
		if (!visit[v]){
			visit[v] = 1;
			if (cy[v] == -1 || path(cy[v])){
				cy[v] = u;
				cx[u] = v;
				return 1;
			}
		}
	}
	return 0;
}

void bipartite(){
	int i, ans = 0;
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	for (i = 0; i < n; i++){
		if (cx[i] == -1){
			memset(visit, 0, sizeof(visit));
			ans += path(i);
		}
	}
	// printf("ANS %d %d\n", ans, n - ans);
	printf("%d\n", n - ans);
}

int main()
{
	int t, i;
	cin >> t;
	while (t--){
		cin >> n >> k;
		for (i = 0; i < n; i++) cin >> vi[i];
		init();
		bipartite();
	}
	return 0;
}

