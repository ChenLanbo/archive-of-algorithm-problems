#include <iostream>
using namespace std;
#define N 128
int n, mp[N][N];
int visit[N], linkx[N], linky[N];

void init(){
	int i, j, k;
	memset(mp, 0, sizeof(mp));
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> j;
		while (j--){
			cin >> k;
			mp[i][k] = 1;
		}
	}
}

int augmenting(int u){
	int v;
	for (v = 0; v < n; v++){
		if (mp[u][v] == 0 || visit[v]) continue;
		visit[v] = 1;
		if (linky[v] == -1 || augmenting(v)){
			linky[v] = u;
			linky[u] = v;
			return 1;
		}
	}
	return 0;
}

int bipartite(){
	int m = 0, i;
	memset(linkx, -1, sizeof(linkx));
	memset(linky, -1, sizeof(linky));
	for (i = 0; i < n; i++){
		if (linkx[i] == -1){
			memset(visit, 0, sizeof(visit));
			m += augmenting(i);
		}
	}
	return m;
}

int main(){
	;
}
