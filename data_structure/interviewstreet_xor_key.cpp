// www.interviewstreet.com
// Problem: XOR KEY
// Data structure: similar to merge sort tree
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100008
#define L 14
#define LOG(a, ...) (a ? printf(__VA_ARGS__) : 0)
int n, q;
int seq[N], nxt[N], id[N], pos[N];
int cntL[15][N] = { 0 };

int query(int dep, int req, int val, int left, int right, int ql, int qr){
	int dif, l, ret;
	LOG(0, "%d: %d %d %d %d\n", dep, left, right, ql, qr);
	if (dep == L + 1){
		return val;
	}
	dif = cntL[dep][qr] - cntL[dep][ql-1];
	l = qr - ql + 1;
	LOG(0, "dif: %d --- l %d\n", dif, l);
	if (req & (1 << (L - dep))){
		// goto left
		if (dif > 0){
			LOG(0, "A\n");
			ret = query(dep + 1, req, val, \
					left, left + cntL[dep][right] - cntL[dep][left-1] - 1, \
					left + cntL[dep][ql-1] - cntL[dep][left-1], 
					left + cntL[dep][qr] - cntL[dep][left-1] - 1);
		} else {
			LOG(0, "B\n");
			val |= (1 << (L - dep));
			ret = query(dep + 1, req, val, \
					left + cntL[dep][right] - cntL[dep][left-1], right, \
					left + cntL[dep][right] - cntL[dep][left-1] + ql - left - (cntL[dep][ql-1] - cntL[dep][left-1]), \
					left + cntL[dep][right] - cntL[dep][left-1] + qr - left - (cntL[dep][qr] - cntL[dep][left-1]));
		}
	} else {
		// goto right
		if (dif == l){
			LOG(0, "C\n");
			ret = query(dep + 1, req, val, \
					left, left + cntL[dep][right] - cntL[dep][left-1] - 1, \
					left + cntL[dep][ql-1] - cntL[dep][left-1], 
					left + cntL[dep][qr] - cntL[dep][left-1] - 1);
		} else {
			LOG(0, "D\n");
			val |= (1<< (L - dep));
			ret = query(dep + 1, req, val, \
					left + cntL[dep][right] - cntL[dep][left-1], right, \
					left + cntL[dep][right] - cntL[dep][left-1] + ql - left - (cntL[dep][ql-1] - cntL[dep][left-1]), \
					left + cntL[dep][right] - cntL[dep][left-1] + qr - left - (cntL[dep][qr] - cntL[dep][left-1]));
		}
	}
	return ret;
}

// Reverse of merge sort, but we sort according to the bits
void build(int dep, int l, int r, int head){
	int hl, hr, tl, tr, i, j;
	hl = hr = tl = tr = 0;
	for (i = head, j = l; i != -1; i = nxt[i], j++){
		cntL[dep][j] = cntL[dep][j-1];
		if (!(seq[i] & (1 << (L - dep)))){
			nxt[tl] = i;
			tl = i;
			if (hl == 0) hl = i;
			cntL[dep][j]++;
		} else {
			nxt[tr] = i;
			tr = i;
			if (hr == 0) hr = i;
		}
	}
	nxt[tl] = nxt[tr] = -1;
	if (hl == 0) hl = -1;
	if (hr == 0) hr = -1;

	if (dep == L){
		return ;
	}
	if (cntL[dep][r] - cntL[dep][l-1] > 0){
		build(dep + 1, l, l + cntL[dep][r] - cntL[dep][l-1] - 1, hl);
	}
	if (cntL[dep][r] - cntL[dep][l-1] != r - l + 1){
		build(dep + 1, l + cntL[dep][r] - cntL[dep][l-1], r, hr);
	}
}

int main(){
	int ca, x, y, z;
	cin >> ca;
	while (ca--){
		cin >> n >> q;
		for (int i = 1; i <= n; i++) scanf("%d", seq + i);
		for (int i = 1; i <= n; i++){
			LOG(0, "%d: %02x\n", i, seq[i]);
			nxt[i] = i + 1;
		}
		nxt[n] = -1;
		build(0, 1, n, 1);
		while (q--){
			scanf("%d%d%d", &x, &y, &z);
			printf("%d\n", x ^ query(0, x, 0, 1, n, y, z));
		}
	}
}
