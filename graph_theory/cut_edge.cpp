// Cut edge(bridge) of undirected graph, there may be multiple edges between two points
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1024
struct Edge {
	int v, id, next;
	Edge(){}
	Edge(int _v, int _id, int _next): v(_v), id(_id), next(_next){}
}edge[N << 1];
int size, n, rt, mp[N], visit[N], dep[N], low[N], mark[N], bridge[N];

void add_edge(int u, int v){
	edge[size] = Edge(u, mp[u]);
	mp[u] = size++;
}

void dfs(int u, int d, int p){
	int i, v, son = 0;
	visit[u] = 1;
	dep[u] = low[u] = d;
	for (i = mp[u]; i != -1; i = edge[i].next){
		if (mark[edge[i].id]) continue;
		mark[edge[i].id] = 1;
		v = edge[i].v;
		if (visit[v]){
			low[u] = min(low[u], dep[v]);
			continue;
		}
		dfs(v, d + 1, u);
		low[u] = min(low[u], low[v]);
		son++;
		// bridge
		if (low[v] > dep[u]){
			// ith edge is bridge
			bridge[edge[i].id] = 1;
		}
	}
}

int main(){
	;
}
