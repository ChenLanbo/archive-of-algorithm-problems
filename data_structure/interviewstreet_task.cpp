// interviewstreet
// problem: task scheduling
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200008
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)
struct Task {
	int id, di, mi;
	Task(){}
	Task(int _id, int _di, int _mi): id(_id), di(_di), mi(_mi){}
	bool operator<(const Task &t) const {
		if (di == t.di) return id < t.id;
		return di < t.di;
	}
}task[N];

struct Node {
	int l, r, over, c;
}tree[N<<1];
int n, pos[N], over[N], ans[N];

inline void down(int id){
	// > 0
	if (tree[id].c == 0) return ;
	tree[lc(id)].over -= tree[id].c;
	tree[rc(id)].over -= tree[id].c;
	tree[lc(id)].c += tree[id].c;
	tree[rc(id)].c += tree[id].c;
	tree[id].c = 0;
}

inline void up(int id){
	tree[id].over = max(tree[lc(id)].over, tree[rc(id)].over);
}

void build(int id, int l, int r){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].c = 0;
	if (l == r){
		tree[id].over = over[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(lc(id), l, mid);
	build(rc(id), mid + 1, r);
	up(id);
}

void insert(int id, int l, int r, int delta){
	if (l <= tree[id].l && tree[id].r <= r){
		tree[id].over -= delta;
		tree[id].c += delta;
		return ;
	}
	int mid = (tree[id].l + tree[id].r) >> 1;
	down(id);
	if (l <= mid) insert(lc(id), l, r, delta);
	if (r > mid) insert(rc(id), l, r, delta);
	up(id);
}

void solve(){
	int i, j, total = 0;
	sort(task, task + n);
	for (i = 0; i < n; i++) pos[task[i].id] = i;
	for (i = 0; i < n; i++){
		total += task[i].mi;
		over[i] = total - task[i].di;
		// cout << "Over " << over[i] << endl;
	}
	build(1, 0, n - 1);
	for (i = n - 1; i >= 0; i--){
		ans[i] = tree[1].over;
		insert(1, pos[i], n - 1, task[pos[i]].mi);
	}
	for (i = 0; i < n; i++){
		cout << max(0, ans[i]) << endl;
	}
}

int main(){
	int i, x, y;
	while (cin >> n){
		for (i = 0; i < n; i++){
			cin >> x >> y;
			task[i] = Task(i, x, y);
		}
		solve();
	}
}
