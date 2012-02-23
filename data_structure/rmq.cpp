#include <iostream>
#include <algorithm>
using namespace std;
#define N 1024
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int n, seq[N];
int hh[N][20];

void rmq_init(){
	int i, j, l;
	for (i = 0; i < n; i++) hh[i][0] = seq[i];
	for (j = l = 1; l * 2 <= len; j++, l <<= 1){
		for (i = 0; i <= len - l * 2; i++){
			hh[i][j] = MIN(hh[i][j-1], hh[i+l][j-1]);
		}
	}
}

int rmq_query(int start, int end){
	int j = 0, l = 1;
	while (l * 2 <= end - start + 1){
		j++;
		l <<= 1;
	}
	return MIN(hh[start][j], hh[end-l+1][j]);
}

int main(){
	;
}
