#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> getpi(string pattern) {
	int j = 0;
	vector<int> pi(pattern.length(), 0);
	for (int i = 1; i < pattern.length(); i++) {
		if (j > 0 && pattern[i] != pattern[j]) {
			j = pi[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			pi[i] = ++j;
		}
	}
	return pi;
}
vector<int> KMP(string str, string pattern, vector<int> pi) {
	int j = 0;
	vector<int> ans;
	for (int i = 0; i < str.length(); i++) {
		while (j > 0 && str[i] != pattern[j]) {
			j = pi[j - 1];
		}
		if (str[i] == pattern[j]) {
			if (j == pattern.length() - 1) {
				ans.push_back(i - j);
				j = pi[j];
			}
			else {
				j++;
			}
		}
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	string str;
	string pattern;
	vector<int> pi;
	getline(cin, str);
	getline(cin, pattern);
	pi = getpi(pattern);
	vector<int> ans = KMP(str, pattern, pi);
	cout << ans.size() << "\n";
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] + 1<< " ";
	}
	return 0;
}
