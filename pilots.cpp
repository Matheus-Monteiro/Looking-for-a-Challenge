#include <bits/stdc++.h>
using namespace std;
const int MAX = 3000003;

int n, t, arr[MAX], p[MAX];
deque<int> left_max, left_min;

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> t >> n;
	for(int i = 0; i < n; i++)
		cin >> arr[i];

	p[0] = 0;
	left_min.push_back(0);
	left_max.push_back(0);

	int answer = 1;

	for(int i = 1; i < n; i++) {
		int k = p[i - 1];

		while(!left_min.empty() and arr[i] - arr[left_min.front()] > t) {
			k = max(k, left_min.front() + 1);
			left_min.pop_front();
		}

		while(!left_max.empty() and arr[left_max.front()] - arr[i] > t) {
			k = max(k, left_max.front() + 1);
			left_max.pop_front();
		}

		while(!left_max.empty() and arr[left_max.back()] < arr[i])
			left_max.pop_back();
		left_max.push_back(i);

		while(!left_min.empty() and arr[left_min.back()] > arr[i])
			left_min.pop_back();
		left_min.push_back(i);

		p[i] = k;

		answer = max(answer, i - p[i] + 1);
	}

	cout << answer << '\n';

	return 0;
}
