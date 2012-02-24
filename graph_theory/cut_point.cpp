// Cut point of undirected graph
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1024
struct Edge {
	int v, next;
	Edge(){}
	Edge(int _v, int _next): v(_v), next(_next) {}
}edge[N << 1];
int size, n, rt, mp[N], visit[N], dep[N], low[N], mark[N];

void add_edge(int u, int v){
	edge[size] = Edge(u, mp[u]);
	mp[u] = size++;
}

void dfs(int u, int d, int p){
	int i, v, son = 0;
	visit[u] = 1;
	dep[u] = low[u] = d;
	for (i = mp[u]; i != -1; i = edge[i].next){
		v = edge[i].v;
		if (visit[v]){
			if (v != p){
				low[u] = min(low[u], dep[v]);
			}
			continue;
		}
		dfs(v, d + 1, u);
		son++;
		low[u] = min(low[u], low[v]);
		if ((u == rt && son > 1) || (u != rt && low[v] >= dep[u])){
			mark[u] = 1;
		}
	}
}

int main(){
	;
}
