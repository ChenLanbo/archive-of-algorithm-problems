// Manacher algorithm for longest palindromic substring
#include <iostream>
#include <cstring>
using namespace std;
#define N (1 << 20)
char str1[N], str2[N << 1];
int n, m, p[N << 1];

void init(){
	int i = 0, k = 1, t = 0;
	str2[0] = '$';
	while (str1[i] != '\0'){
		str2[k++] = t ? str1[i++] : '#';
		t ^= 1;
	}
	str2[k++] = '#';
	str2[k] = '\0';
	m = k;
}

int mancher(){
	int mx = 0, id, i, ans = 0;
	memset(p, 0, sizeof(p));

	for (i = 1; i < m; i++){
		if (mx > i){
			p[i] = min(p[2 * id - i], mx - i);
		} else {
			p[i] = 1;
		}
		for ( ; str2[i - p[i]] == str2[i + p[i]]; p[i]++);
		if (i + p[i] > mx){
			mx = i + p[i];
			id = i;
		}
	}
	for (i = 0; i < m; i++){
		ans = max(ans, p[i]);
	}
	ans--;
	// cout << ans << endl;
	return ans;
}

int main(){
	int ca = 0;
	while (cin >> str1){
		if (str1[0] == 'E' && str1[1] == 'N' && str1[2] == 'D'){
			break;
		}
		init();
		cout << "Case " << ++ca << ": " << mancher() << endl;
	}
}
