#include <iostream>
using namespace std;
#define N 100
int n, mp[N][N];

void floyd(){
	int i, j, k;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			for (k = 0; k < n; k++){
				if (mp[j][i] + mp[i][k] < mp[j][k]){
					mp[j][k] = mp[j][i] + mp[i][k];
				}
			}
		}
	}
}

int main(){
	;
}
