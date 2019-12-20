#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<int> text;
vector<int> pattern;
vector<int> LMax;
vector<int> LMin;
vector<int> P;
vector<int> ans;
bool lemma2(vector<int> vec, int a, int b, int t, int index) {
	if (a != 0 && vec[index + a] > vec[t + 1]) {
		return false;
	}
	if (b != 0 && vec[t + 1] > vec[index + b]) {
		return false;
	}
	return true;
}
void make_LMax() {
	vector< pair<int, int> > temp;
	for (int i = 1; i < pattern.size(); i++) {
		temp.push_back({ pattern[i],i });// number, index
	}
	sort(temp.begin(), temp.end());
	LMax.assign(pattern.size(), 0);
	stack<int> sta;
	sta.push(temp[0].second);
	for (int i = 1; i < temp.size(); i++) {
		while (!sta.empty() && sta.top() > temp[i].second) {
			sta.pop();
		}
		if (!sta.empty()) {
			LMax[temp[i].second] = sta.top();
		}
		sta.push(temp[i].second);
	}
}
void make_LMin() {
	struct stru {
		int number;
		int index;
		bool operator<(stru k) {
			if (number != k.number) {
				return number < k.number;
			}
			else {
				return index > k.number;
			}
		}
	};
	vector<stru> temp;
	for (int i = 1; i < pattern.size(); i++) {
		temp.push_back({ pattern[i],i });
	}
	sort(temp.begin(), temp.end());
	LMin.assign(pattern.size(), 0);
	stack<int> sta;
	sta.push(temp[temp.size() - 1].index);
	for (int i = temp.size() - 2; i >= 0; i--) {
		while (!sta.empty() && sta.top() > temp[i].index) {
			sta.pop();
		}
		if (!sta.empty()) {
			LMin[temp[i].index] = sta.top();
		}
		sta.push(temp[i].index);
	}
}
void make_P() {
	P.push_back(-1);
	int t = -1;
	for (int i = 1; i < pattern.size(); i++) {
		while (t > 0 && !lemma2(pattern, LMax[t + 1], LMin[t + 1], t, 0)) {
			t = P[t];
		}
		t++;
		P.push_back(t);
	}
}
void func() {
	int i = 0;
	int j = 1;
	while (i <= text.size() - pattern.size()) {
		while (j < pattern.size() - 1 && lemma2(text, LMax[j + 1], LMin[j + 1], i + j, i)) {
			j++;
		}
		if (j == pattern.size() - 1) {
			ans.push_back(i);
		}
		i = i + j - P[j];
		j = max(1, P[j]);
	}
}
int main() {
	int n;
	int m;
	cin >> n;
	text.push_back(0);
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		text.push_back(num);
	}
	cin >> m;
	pattern.push_back(0);
	for (int i = 0; i < m; i++) {
		int num;
		cin >> num;
		pattern.push_back(num);
	}
	make_LMax();
	make_LMin();
	make_P();
	func();
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	return 0;
}