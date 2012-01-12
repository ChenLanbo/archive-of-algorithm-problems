// www.interviewstreet.com
// Problem: String Similarity
// Solution: Suffix Array, Range Minimum Query
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100008
int len;
char str[N]; 
int sa1[N], sa2[N], rank1[N], rank2[N], h[N], height[N];
int hh[N][17];

void rmq_init(){
	int i, j, l;
	for (i = 0; i < len; i++) hh[i][0] = height[i];
	for (j = l = 1; l*2 <= len; j++, l <<= 1){
		for (i = 0; i <= len-l*2; i++)
			hh[i][j] = min(hh[i][j-1], hh[i+l][j-1]);
	}
}

inline int rmq_query(int start, int end){
	int j = 0, l = 1;
	while (l*2 <= end-start+1){
		j++;
		l <<= 1;
	}
	return min(hh[start][j], hh[end-l+1][j]);
}


inline bool cmp(int x, int y){
	return str[x] < str[y];
}

void create_suffix_array(){
	int i, k, *s1 = sa1, *s2 = sa2, *r1 = rank1, *r2 = rank2;
	for (i = 0; i < len; i++) s1[i] = i;
	sort(s1, s1+len, cmp);
	for (r1[s1[0]] = 0, i = 1; i < len; i++){
		if (str[s1[i]] == str[s1[i-1]]) r1[s1[i]] = r1[s1[i-1]];
		else r1[s1[i]] = r1[s1[i-1]]+1;
	}
	for (k = 1; k < len && r1[s1[len-1]] < len-1; k <<= 1){
		for (i = 0; i < len; i++) r2[r1[s1[i]]] = i;
		for (i = len-1; i >= 0; i--)
			if (k <= s1[i])
				s2[r2[r1[s1[i]-k]]--] = s1[i]-k;
		for ( i = len-k; i < len-(k>>1); i++ ) s2[r2[r1[i]]] = i;
		swap(s1, s2);
		for (r2[s1[0]] = 0, i = 1; i < len; i++){
			if (r1[s1[i]] != r1[s1[i-1]] || r1[s1[i]+k] != r1[s1[i-1]+k])
				r2[s1[i]] = r2[s1[i-1]]+1;
			else r2[s1[i]] = r2[s1[i-1]];
		}
		swap(r1, r2);
	}
	if (s1 != sa1) for (i = 0; i < len; i++) sa1[i] = s1[i];
	if (r1 != rank1) for (i = 0; i < len; i++) rank1[i] = r1[i];
}

inline void cal_height(){
	int i, j, k;
	for (i = k = 0; i < len; i++){
		if (rank1[i] == 0) h[i] = 0;
		else {
			for (j = sa1[rank1[i]-1]; str[i+k] == str[j+k]; k++);
			h[i] = k;
			if (k > 0) k--;
		}
	}
	for (i = 0; i < len; i++) height[i] = h[sa1[i]];
	// for (i = 0; i < len; i++){ cout << sa1[i] << " - " << height[i] << endl; }
}

void solve(){
	int i, j, x, y;
	long long ans = len - 1;
	for (i = 1; i < len - 1; i++){
		x = rank1[0];
		y = rank1[i];
		if (x > y) swap(x, y);
		j = rmq_query(x + 1, y);
		ans += j;
	}
	cout << ans << endl;
}

int main(){
	int ca;
	cin >> ca;
	while (ca--){
		memset(str, 0, sizeof(str));
		scanf("%s", str);
		len = strlen(str);
		str[len++] = '$';
		create_suffix_array();
		cal_height();
		rmq_init();
		solve();
	}
}

