// www.interviewstreet.com
// Problem: Quadrant Queries
// Solution: Segment tree
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100008
#define LC(r) ((r)<<1)
#define RC(r) ((r)<<1|1)
struct Node {
	int l, r, mark;
	int cnt[4];
}node[N<<2];
int n, q;
int px[N], py[N];
int ans[4];

inline int getQuadrant(int x, int y){
	if (x > 0){
		if (y > 0) return 0;
		else return 3;
	} else {
		if (y > 0) return 1;
		else return 2;
	}
}

void down(int rt){
	// reflect x
	if (node[rt].mark & 1){
		node[rt].mark ^= 1;
		node[LC(rt)].mark ^= 1;
		swap(node[LC(rt)].cnt[0], node[LC(rt)].cnt[3]);
		swap(node[LC(rt)].cnt[1], node[LC(rt)].cnt[2]);
		node[RC(rt)].mark ^= 1;
		swap(node[RC(rt)].cnt[0], node[RC(rt)].cnt[3]);
		swap(node[RC(rt)].cnt[1], node[RC(rt)].cnt[2]);
	}
	// reflect y
	if (node[rt].mark & 2){
		node[rt].mark ^= 2;
		node[LC(rt)].mark ^= 2;
		swap(node[LC(rt)].cnt[0], node[LC(rt)].cnt[1]);
		swap(node[LC(rt)].cnt[2], node[LC(rt)].cnt[3]);
		node[RC(rt)].mark ^= 2;
		swap(node[RC(rt)].cnt[0], node[RC(rt)].cnt[1]);
		swap(node[RC(rt)].cnt[2], node[RC(rt)].cnt[3]);
	}
}

void up(int rt){
	for (int i = 0; i < 4; i++){
		node[rt].cnt[i] = node[LC(rt)].cnt[i] + node[RC(rt)].cnt[i];
	}
}

void build(int rt, int l, int r){
	node[rt].l = l;
	node[rt].r = r;
	node[rt].mark = 0;
	for (int i = 0; i < 4; i++) node[rt].cnt[i] = 0;
	if (l == r){
		node[rt].cnt[getQuadrant(px[l], py[l])]++;
		return ;
	}
	int mid = (l + r) >> 1;
	build(LC(rt), l, mid);
	build(RC(rt), mid + 1, r);
	up(rt);
}

void insert(int rt, int l, int r, int mm){
	if (node[rt].l != node[rt].r){
		down(rt);
	}
	if (node[rt].l >= l && node[rt].r <= r){
		node[rt].mark = mm;
		if (mm == 1){
			swap(node[rt].cnt[0], node[rt].cnt[3]);
			swap(node[rt].cnt[1], node[rt].cnt[2]);
		} else if (mm == 2) {
			swap(node[rt].cnt[0], node[rt].cnt[1]);
			swap(node[rt].cnt[2], node[rt].cnt[3]);
		}
		return ;
	}
	int mid = (node[rt].l + node[rt].r) >> 1;
	if (l <= mid) insert(LC(rt), l, r, mm);
	if (r > mid) insert(RC(rt), l, r, mm);
	up(rt);
}

void query(int rt, int l, int r){	
	if (node[rt].l != node[rt].r){
		down(rt);
	}
	if (node[rt].l >= l && node[rt].r <= r){
		/*puts("DEBUG");
		  cout << node[rt].l << " " << node[rt].r << endl;
		  for (int i = 0; i < 4; i++) cout << node[rt].cnt[i] << " "; cout << endl;
		  puts("DEBUG");*/
		for (int i = 0; i < 4; i++){
			ans[i] += node[rt].cnt[i];
		}
		return ;
	}
	int mid = (node[rt].l + node[rt].r) >> 1;
	if (l <= mid) query(LC(rt), l, r);
	if (r > mid) query(RC(rt), l, r);
	up(rt);
}

int main(){
	int u, v;
	char str[16];
	while (cin >> n){
		for (int i = 1; i <= n; i++){
			cin >> px[i] >> py[i];
		}
		build(1, 1, n);
		cin >> q;
		while (q--){
			scanf("%s", str);
			cin >> u >> v;
			if (str[0] == 'X'){
				insert(1, u, v, 1);
			} else if (str[0] == 'Y'){
				insert(1, u, v, 2);
			} else if (str[0] == 'C'){
				memset(ans, 0, sizeof(ans));
				query(1, u, v);
				cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << endl;
				// puts("");
			}
		}
	}
}

