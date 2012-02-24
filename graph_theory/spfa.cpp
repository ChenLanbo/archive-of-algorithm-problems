// Shortest path faster algorithm
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 100000
#define INF 0x1f1f1f1f
struct Edge {
	int v, next, d;
	Edge(){}
	Edge(int _v, int _d, int _next): v(_v), d(_d), next(_next){}
}edge[N];
int size, n, mp[N], dist[N], visit[N];

void initg(){
	size = 0;
	memset(mp, -1, sizeof(mp));
}

void add_edge(int u, int v, int d){
	edge[size] = Edge(v, d, mp[u]);
	mp[u] = size++;
}

int spfa(int s, int t){
	int i, u, v;
	queue<int> que;

	memset(visit, 0, sizeof(visit));
	memset(dist, 0x1f, sizeof(dist));
	dist[s] = 0;
	que.push(s);
	
	while (!que.empty()){
		u = que.front();
		que.pop();
		visit[u] = 0;
		for (i = mp[u]; i != -1; i = edge[i].next){
			v = edge[i].v;
			if (dist[v] > dist[u] + edge[i].d){
				dist[v] = dist[u] + edge[i].d;
				if (!visit[v]){
					visit[v] = 1;
					que.push(v);
				}
			}
		}
	}
	return dist[t];
}

int main(){
	;
}
