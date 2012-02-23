#include <iostream>
using namespace std;
#define N 1024
int n, gp[N];

void init(){
	for (int i = 0; i < n; i++){
		gp[i] = i;
	}
}

int find_set(int u){
	if (gp[u] == u){
		return u;
	}
	return (gp[u] = find_set(gp[u]));
}

void join_set(int u, int v){
	int x, y;
	x = find_set(u);
	y = find_set(v);
	if (x != y){
		gp[y] = x;
	}
}

int main(){
	;
}
