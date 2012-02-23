// One dimensional binary index tree
#include <iostream>
#include <algorithm>
using namespace std;
#define N (1<<16)
int n, array[N];

void init(){
	memset(d, 0, sizeof(d));
}

int lowbit(int v){
	return v&(-v);
}

void update(int d[], int size, int pos, int delta){
	while (pos <= size){
		d[pos] += delta;
		pos += lowbit(pos);
	}
}

int get_sum(int d[], int size, int pos){
	int ret = 0;
	while (pos > 0){
		ret += d[pos];
		pos -= lowbit(pos);
	}
	return ret;
}

int main(){
	;
}
