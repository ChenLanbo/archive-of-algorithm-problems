// Strongest Connected Component
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N (1 << 15)
int n, m;
int seq_num, seq[N];
int comp_num, part[N], visit[N];
vector<int> g[N], gt[N];

void initg(){
	for (int i = 1; i <= n; i++){
		g[i].clear();
		gt[i].clear();
	}
}

void add_edge(int u, int v){
	g[u].push_back(v);
	gt[v].push_back(u);
}

void dfs_g(int u){
	visit[u] = 1;
	for (int i = 0; i < g[u].size(); i++){
		if (!visit[g[u][i]]){
			dfs_g(g[u][i]);
		}
	}
	seq[++seq_num] = u;
}

void dfs_gt(int u){
	visit[u] = 1;
	part[u] = comp_num;
	for (int i = 0; i < gt[u].size(); i++){
		if (!visit[gt[u][i]]){
			dfs_gt(gt[u][i]);
		}
	}
}

void scc(){
	int u, v, ic, oc;

	seq_num = 0;
	memset(visit, 0, sizeof(visit));
	for (u = 1; u <= n; u++){
		if (!visit[u]){
			dfs_g(u);
		}
	}

	comp_num = 0;
	memset(visit, 0, sizeof(visit));
	for (u = n; u > 0; u--){
		if (!visit[seq[u]]){
			comp_num++;
			dfs_gt(seq[u]);
		}
	}

}

int main(){
	int ca, u, v;
	scanf("%d", &ca);
	while (ca--){
		scanf("%d%d", &n, &m);
		initg();
		while (m--){
			scanf("%d%d", &u, &v);
			add_edge(u, v);
		}
		scc();
	}
}
