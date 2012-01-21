// www.interviewstreet.com
// Problem: Vertical Stick
// Solution: Calculate the expected value for each position
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 64
int n, stk[N];
int c[N][2];

// Calculate the expected value for each position
// stk[i], input
double solve() {
	double ans = 1.0;
	for (int pos = 2; pos <= n; pos++) {
		double t1 = 0.0;
		for (int i = 0; i < n; i++) { // choose i in position pos
			int x = c[i][0]; // <  stk[i]
			int y = c[i][1]; // >= stk[i]

			double pre = 1.0;
			int k = 1;
			for (; k <= (pos - 1); k++) {
				double t2 = pre * ( (double)y / (double)(x + y) );
				t1 += (t2 * k);
				pre *= ( (double)x / (double) (x + y) );
				if (x-- <= 0) 
					break;
			}
			if (k == pos)
				t1 += (pre * pos);
		}
		// cout << "POS " << pos << ": " << t1 / n << endl;
		ans += (t1 / n);
	}
	return ans;
}


int main(){
	int t;
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 0; i < n; i++) cin >> stk[i];
		sort(stk, stk + n);
		for (int i = 0; i < n; i++){
			c[i][0] = c[i][1] = 0;
			for (int j = 0; j < n; j++){
				if (stk[j] < stk[i]) c[i][0]++;
				else c[i][1]++;
			}
			c[i][1]--;
			// cout << c[i][0] << " " << c[i][1] << endl;
		}
		printf("%.2lf\n", solve());
	}
}
