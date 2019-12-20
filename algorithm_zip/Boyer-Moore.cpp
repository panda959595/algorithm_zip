#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int BCS[128];
int suffix[1005];
int GSS[1005];
vector<int> ans;
void make_BCS(string pattern) {
	for (int i = 0; i < 128; i++) {
		BCS[i] = -1;
	}
	for (int i = 0; i < pattern.length(); i++) {
		BCS[pattern[i]] = i;
	}
}
void make_GSS(string pattern) {
	int len = pattern.length();
	int i = len;
	int j = len + 1;
	suffix[len] = j;
	while (i > 0) {
		while (j >= len && pattern[i - 1] != pattern[j - 1]) {
			if (GSS[j] == 0) {
				GSS[j] = j;
			}
			j = suffix[j];
		}
		i--;
		j--;
		suffix[i] = j;
	}
	j = suffix[0];
	for (i = 0; i <= len; i++) {
		if (GSS[i] == 0) {
			GSS[i] = j;
		}
		if (i == j) {
			j = suffix[j];
		}
	}
}
void BMA(string body, string pattern) {
	int len_pattern = pattern.length();
	int len_body = body.length();
	int i = pattern.length() - 1;
	int j = pattern.length() - 1;
	while (i < len_body) {
		if (j == -1) {
			ans.push_back(i + 1);
			i += len_pattern + 1;
			j = len_pattern - 1;
		}
		if (body[i] == pattern[j]) {
			i--;
			j--;
		}
		else {
			i += max(GSS[j + 1], len_pattern - BCS[body[i]] - 1);
			j = len_pattern - 1;
		}
	}
}
int main() {
	string body;
	string pattern;
	getline(cin, body);
	getline(cin, pattern);
	make_BCS(pattern);
	make_GSS(pattern);
	BMA(body, pattern);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}
	return 0;
}