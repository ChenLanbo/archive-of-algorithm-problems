#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100080
int n, q;
int len;
int str[N]; 
int sa1[N], sa2[N], rank1[N], rank2[N], h[N], height[N];
char wi[64][2048];
int id[N], pos[N];
int sl[64];

bool cmp(int x, int y){
	return str[x] < str[y];
}

void create_suffix_array(){
	int i, k, *s1 = sa1, *s2 = sa2, *r1 = rank1, *r2 = rank2;
	for (int i = 0; i < len; i++) s1[i] = i;
	sort(s1, s1 + len, cmp);
	for (r1[s1[0]] = 0, i = 1; i < len; i++){
		if (str[s1[i]] == str[s1[i-1]]) r1[s1[i]] = r1[s1[i-1]];
		else r1[s1[i]] = r1[s1[i-1]] + 1;
	}

	for (k = 1; k < len && r1[s1[len-1]] < len - 1; k <<= 1){
		for (i = 0; i < len; i++) r2[r1[s1[i]]] = i;
		for (i = len - 1; i >= 0; i--)
			if (k <= s1[i])
				s2[r2[r1[s1[i] - k]]--] = s1[i] - k;
		for (i = len - k; i < len - (k >> 1); i++) s2[r2[r1[i]]] = i;
		swap(s1, s2);
		for (r2[s1[0]] = 0, i = 1; i < len; i++){
			if (r1[s1[i]] != r1[s1[i - 1]] || r1[s1[i] + k] != r1[s1[i - 1] + k])
				r2[s1[i]] = r2[s1[i - 1]] + 1;
			else r2[s1[i]] = r2[s1[i-1]];
		}
		swap(r1, r2);
	}

	if (s1 != sa1) for (i = 0; i < len; i++) sa1[i] = s1[i];
	if (r1 != rank1) for (i = 0; i < len; i++) rank1[i] = r1[i];
}

void cal_height(){
	int i, j, k;
	for (i = k = 0; i < len; i++){
		if (rank1[i] == 0) h[i] = 0;
		else {
			for (j = sa1[rank1[i] - 1]; str[i + k] == str[j + k]; k++);
			h[i] = k;
			if (k > 0) k--;
		}
	}
	for (i = 0; i < len; i++) height[i] = h[sa1[i]];
	for (i = 0; i < len; i++){
		cout << sa1[i] << " " << height[i] << endl;
	}
}

void init(){
	int i, j;
	len = 0;
	for (i = 0; i < n; i++){
		sl[i] = strlen(wi[i]);
		for (j = 0; j < sl[i]; j++){
			str[len] = wi[i][j];
			id[len] = i;
			pos[len] = j;
			len++;
		}
		str[len] = -i;
		id[len] = i;
		pos[len] = j;
		len++;
	}
	// cout << "Len : " << len << endl;
}

void query(int kth){
	int i, j, k;

	for (i = n; i < len; i++){
		j = sl[id[sa1[i]]] - pos[sa1[i]];
		j -= height[i];
	//	cout << j << endl;
		if (kth <= j){
			for (k = 0; k < height[i]; k++){
				printf("%c", str[sa1[i] + k]);
			}
			for (k = 0; k < kth; k++){
				printf("%c", str[sa1[i] + height[i] + k]);
			}
			puts("");
			return ;
		}
		kth -= j;
	}
	puts("INVALID");
}

int main(){
	int i, j;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", wi[i]);
	}
	init();
	create_suffix_array();
	cal_height();
	scanf("%d", &q);
	while (q--){
		scanf("%d", &i);
		query(i);
	}
}
