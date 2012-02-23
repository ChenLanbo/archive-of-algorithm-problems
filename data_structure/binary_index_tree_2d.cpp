#include <iostream>
using namespace std;
#define N 1024
int n, d[N][N];

void init(){
	memset(d, 0, sizeof(d));
}

int lowbit(int v){
	return v & (-v);
}

void update(int x, int y, int delta){
	int u = x, v = y;
	while (u <= n){
		v = y;
		while (v <= n){
			d[u][v] += delta;
			v += lowbit(v);
		}
		u += lowbit(u);
	}
}

int get_sum(int x, int y){
	int ret = 0, u = x, v = y;
	while (u > 0){
		v = y;
		while (v > 0){
			ret += d[u][v];
			v -= lowbit(v);
		}
		u -= lowbit(u);
	}
	return ret;
}

int main(){
	;
}
