// www.interviewstreet.com
// Problem: Substring Diff
// Solution: dynamic programming, O(n^2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 1600
int kk, l1, l2;
// int d[N][N];
char s1[N], s2[N];
int que[N][2];

void solve(){
	int i, j, ans = 0;
	for (i = 0; i < l2; i++){
		int cnt = 0, head = 0, tail = 0;
		for (j = 0; ; j++){
			if (0 + j >= l1 || i + j >= l2)
				break;
			// que.push(make_pair(0 + j, i + j));
			que[tail][0] = j;
			que[tail][1] = i + j;
			tail++;

			if (s1[0+j] != s2[i+j])
				cnt++;

			while (cnt > kk && head < tail){
				// e = que.front();
				// que.pop();
				if (s1[que[head][0]] != s2[que[head][1]])
					cnt--;
				head++;
				// if (d[e.first][e.second]) cnt--;
			}
			ans = max(ans, tail - head);
		}
	}
	for (i = 0; i < l1; i++){
		int cnt = 0, head = 0, tail = 0;
		for (j = 0; ; j++){
			if (i + j >= l1 || 0 + j >= l2)
				break;
			que[tail][0] = i + j;
			que[tail][1] = j;
			tail++;
			if (s1[i+j] != s2[0+j])
				cnt++;
			while (cnt > kk && head < tail){
				if (s1[que[head][0]] != s2[que[head][1]])
					cnt--;
				head++;
			}
			ans = max(ans, tail - head);
		}
	}
	cout << ans << endl;
}

int main(){
	int ca;
	cin >> ca;
	while (ca--){
		cin >> kk >> s1 >> s2;
		l1 = strlen(s1);
		l2 = strlen(s2);
		solve();
	}
}

