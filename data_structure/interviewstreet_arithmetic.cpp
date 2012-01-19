#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N (1<<17)
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)
typedef unsigned long long LL;
const LL mod = 1000003;
int n, q;
LL fact[mod], ai[N], di[N], pi[N];
LL total;
// Segment tree
int ll[N<<1], rr[N<<1];
LL prod1[N<<1], prod2[N<<1], sum1[N<<1], sum2[N<<1];

LL power(LL x, LL y){
	LL ret = 1, d = x % mod;
	while (y > 0){
		if (y & 1) ret = ret * d % mod;
		d = d * d % mod;
		y >>= 1;
	}
	return ret;
}

void build(int id, int l, int r){
	ll[id] = l;
	rr[id] = r;
	sum2[id] = 0;
	if (l == r){
		prod1[id] = power(di[l], pi[l]);
		prod2[id] = di[l];
		sum1[id] = pi[l];
	//	cout << id << " : " << sum1[l] << endl;
		return ;
	}
	int mid = (l + r) >> 1;
	build(lc(id), l, mid);
	build(rc(id), mid + 1, r);

	prod1[id] = prod1[lc(id)] * prod1[rc(id)] % mod;
	prod2[id] = prod2[lc(id)] * prod2[rc(id)] % mod;
	sum1[id] = sum1[lc(id)] + sum1[rc(id)];
}

inline void down(int id){
	if (sum2[id] == 0 || ll[id] == rr[id]) return ;
	sum2[lc(id)] += sum2[id];
	sum1[lc(id)] += sum2[id] * (rr[lc(id)] - ll[lc(id)] + 1);
	prod1[lc(id)] = prod1[lc(id)] * power(prod2[lc(id)], sum2[id]) % mod;
	sum2[rc(id)] += sum2[id];
	sum1[rc(id)] += sum2[id] * (rr[rc(id)] - ll[rc(id)] + 1);
	prod1[rc(id)] = prod1[rc(id)] * power(prod2[rc(id)], sum2[id]) % mod;
	sum2[id] = 0;
}

inline void up(int id){
	prod1[id] = prod1[lc(id)] * prod1[rc(id)] % mod;
	// prod2[id] = prod2[lc(id)] * prod2[rc(id)] % mod;
	sum1[id] = sum1[lc(id)] + sum1[rc(id)];
}

void insert(int id, int l, int r, int p){
	if (l <= ll[id] && rr[id] <= r){
		sum1[id] += p * (rr[id] - ll[id] + 1);
		sum2[id] += p;
		prod1[id] = prod1[id] * power(prod2[id], p) % mod;
		return ;
	}
	int mid = (ll[id] + rr[id]) >> 1;
	down(id);
	if (l <= mid) insert(lc(id), l, r, p);
	if (r > mid) insert(rc(id), l, r, p);
	up(id);
}

LL query(int id, int l, int r){
	if (l <= ll[id] && rr[id] <= r){
		//cout << id << " - " << sum1[id] << endl;
		total += sum1[id];
		return prod1[id];
	}
	int mid = (ll[id] + rr[id]) >> 1;
	LL ret = 1;
	down(id);
	if (l <= mid) ret = ret * query(lc(id), l, r) % mod;
	if (r > mid) ret = ret * query(rc(id), l, r) % mod;
	up(id);
	return ret;
}

int main(){
	int i, u, v, w;
	for (fact[0] = 1, i = 1; i < mod; i++){ fact[i] = i * fact[i-1] % mod; }
	scanf("%d", &n);
	for (i = 1; i <= n; i++){ scanf("%lld%lld%lld", ai + i, di + i, pi + i); }
	build(1, 1, n);
	//puts("DONE");
	scanf("%d", &q);
	while (q--){
		scanf("%d", &i);
		if (i){
			scanf("%d%d%d", &u, &v, &w);
			insert(1, u, v, w);
		} else {
			scanf("%d%d", &u, &v);
			total = 0;
			LL ret = query(1, u, v);
			if (total >= mod) ret = 0;
			else ret = ret * fact[total] % mod;
			cout << total << " " << ret << endl;
	//		printf("%lld %lld\n", total, ret);
		}
	}
}
