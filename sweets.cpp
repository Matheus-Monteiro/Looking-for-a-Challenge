#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ii pair<int, int>
#define fi first
#define se second
#define SZ(a) (int)a.size()

int aux[30];
vector<pair<ii, int>> points;

// O(n*3^n)
void partition(int i, vector<int> &arr, bool label_of_the_set) {
	if(i == SZ(arr)) {
		int a = 0, d = 0, b = 0;
		for(int k = 0; k < SZ(arr); k++)
			if(aux[k] == 0)
				a += arr[k];
			else if(aux[k] == 1)
				d += arr[k];
			else
				b += arr[k];
		// y , x , set
		if(label_of_the_set)
			points.push_back({{d - b, a - d}, label_of_the_set});
		else
			points.push_back({{b - d, d - a}, label_of_the_set});
		return;
	}
	aux[i] = 0;
	partition(i + 1, arr, label_of_the_set);
	aux[i] = 1;
	partition(i + 1, arr, label_of_the_set);
	aux[i] = 2;
	partition(i + 1, arr, label_of_the_set);
}
	
int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<int> K, L;
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if(i < n / 2) K.push_back(x);
		else L.push_back(x);
	}

	partition(0, K, true);
	partition(0, L, false);

	sort(points.begin(), points.end());
	map<int, int> mapa;
	int ans = 0x3f3f3f3f;

	// O(n * sqrt(3^n))
	for(int i = 0; i < SZ(points); i++) {
		int x = points[i].fi.se;
		int y = points[i].fi.fi;
		int s = points[i].se;
		if(s == 0) {
			auto it = mapa.find(x);
			if(it == mapa.end()) mapa[x] = x + y;
			else mapa[x] = max(mapa[x], x + y);
			it = mapa.find(x);
			int val = it->se;
			it++;
			while(it != mapa.end()) {
				if(it->se <= val)
					it = mapa.erase(it);
				else
					break;
			}
		} else {
			auto it = mapa.upper_bound(x);
			if(it == mapa.begin()) continue;
			it--;
			ans = min(ans, x + y - it->se);
		}
	}
	
	cout << ans << '\n';
	
	return 0;
}
