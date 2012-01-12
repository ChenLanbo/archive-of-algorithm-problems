// www.interviewstreet.com
// Problem: Stone Piles
// Solution: Game Theory, SG function
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 128
int seq[N] = { 0 }, p, cnt = 0;
int sg[N] = { 0 }, visit[N];

void partition(int n, int dep){
	if (dep == p){
		int ans = 0;
		if (n <= seq[dep-1]) return ;
		seq[dep] = n;
		cnt++;
		for (int i = 1; i <= p; i++) ans ^= sg[seq[i]];
		visit[ans] = 1;
		return ;
	}

	for (int i = 1; i <= n; i++){
		if (i > seq[dep-1]){
			seq[dep] = i;
			partition(n - i, dep + 1);
		}
	}
}

int 
main(){
	int itr, mex, ans;
	int ca, n, xi[N];

	for (itr = 2; itr <= 50; itr++){
		memset(visit, 0, sizeof(visit));
		for (p = 2; ; p++){
			cnt = 0;
			partition(itr, 1);
			if (cnt == 0){
				break;
			}
		}
		for (mex = 0; visit[mex]; mex++);
		sg[itr] = mex;
		//	cout << itr << " " << sg[itr] << endl;
	}

	cin >> ca;
	while (ca--){
		cin >> n;
		ans = 0;
		for (itr = 0; itr < n; itr++){
			cin >> xi[itr];
			ans ^= sg[xi[itr]];
		}

		//	cout << "ANS " << ans << endl;

		if (ans){
			cout << "ALICE" << endl;
		} else {
			cout << "BOB" << endl;
		}
	}

	return 0;
}

