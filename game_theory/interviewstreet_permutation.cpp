// www.interviewstreet.com
// Problem: Permutation Game
// Solution: Game Theory, calculate SG function
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N (1<<16)
int n, seq[16], sg[N];
int tmp[16], s;
bool visit[256];

bool check(){
	int i;
	if (s == 1)
		return false;
	for (i = 1; i < s; i++){
		if (tmp[i-1] > tmp[i])
			break;
	}
	if (i == s)
		return false;
	return true;
}

void solve(){
	int i, j;

	for (i = 1; i < (1 << n); i++){
		s = 0;
		for (j = 0; j < n; j++){
			if (i & (1<<j)){
				tmp[s++] = seq[j];
			}
		}
		if (!check()){
			sg[i] = 0;
		} else {
			memset(visit, 0, sizeof(visit));
			for (j = 0; j < n; j++){
				if (i & (1 << j)){
					visit[sg[i ^ (1 << j)]] = true;
				}
			}
			for (j = 0; j < 256 && visit[j]; j++);
			sg[i] = j;
		}
		//printf("%d %d\n", i, sg[i]);
	}

	if (sg[(1 << n) - 1])
		puts("Alice");
	else
		puts("Bob");
}

int main(){
	int t;
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 0; i < n; i++) cin >> seq[i];
		memset(sg, 0, sizeof(sg));
		solve();
	}
}

