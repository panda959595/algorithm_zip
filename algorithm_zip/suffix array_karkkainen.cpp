#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n;
string str;
vector<int> radix_sort12(vector<int> str, int len) {
	vector<int> ret;
	for (int i = 0; i < len; i++) {
		if (i % 3 == 0) {
			continue;
		}
		ret.push_back(i);
	}
	vector< queue<int> > que(max(1000, (int)str.size()));
	for (int i = 2; i >= 0; i--) {
		for (auto k : ret) {
			if (k + i >= str.size()) {
				que[0].push(k);
			}
			else {
				que[str[k + i]].push(k);
			}
		}
		int index = 0;
		for (int j = 0; j < que.size(); j++) {
			while (!que[j].empty()) {
				ret[index++] = que[j].front();
				que[j].pop();
			}
		}
	}
	return ret;
}
vector<int> radix_sort0(vector<int> str, vector<int> rank12, int len) {
	vector<int> ret;
	for (int i = 0; i * 3 < len; i++) {
		ret.push_back(i * 3);
	}
	vector< queue<int> >que(max(1000, len));
	for (int i = 2; i >= 1; i--) {
		for (auto k : ret) {
			que[rank12[k + i]].push(k);
		}
		int index = 0;
		for (int j = 0; j < que.size(); j++) {
			while (!que[j].empty()) {
				ret[index++] = que[j].front();
				que[j].pop();
			}
		}
	}
	for (auto k : ret) {
		que[str[k]].push(k);
	}
	int index = 0;
	for (int j = 0; j < que.size(); j++) {
		while (!que[j].empty()) {
			ret[index++] = que[j].front();
			que[j].pop();
		}
	}
	return ret;
}
vector<int> merge_sa(vector<int> str, vector<int> sa0, vector<int> sa12, vector<int> rank12) {
	vector<int> ret;
	int i, j;
	i = j = 0;
	while (1) {
		if (i < sa0.size() && j < sa12.size()) {
			if (str[sa0[i]] != str[sa12[j]]) {
				if (str[sa0[i]] < str[sa12[j]]) {
					ret.push_back(sa0[i++]);
				}
				else {
					ret.push_back(sa12[j++]);
				}
			}
			else {
				if (sa12[j] % 3 == 1) {
					if (rank12[sa0[i] + 1] < rank12[sa12[j] + 1]) {
						ret.push_back(sa0[i++]);
					}
					else {
						ret.push_back(sa12[j++]);
					}
				}
				else {
					if (str[sa0[i]+1] != str[sa12[j]+1]) {
						if (str[sa0[i] + 1] < str[sa12[j] + 1]) {
							ret.push_back(sa0[i++]);
						}
						else {
							ret.push_back(sa12[j++]);
						}
					}
					else {
						if (rank12[sa0[i] + 2] < rank12[sa12[j] + 2]) {
							ret.push_back(sa0[i++]);
						}
						else {
							ret.push_back(sa12[j++]);
						}
					}
				}
			}
		}
		else if (i < sa0.size()) {
			ret.push_back(sa0[i++]);
		}
		else if (j < sa12.size()) {
			ret.push_back(sa12[j++]);
		}
		else {
			break;
		}
	}
	return ret;
}
vector<int> recursive_func(vector<int> str) {
	int len = str.size();
	str.push_back(0);
	str.push_back(0);

	vector<int> vec12 = radix_sort12(str, len);
	vector<int> sa12(vec12.size());
	int order_temp = 1;

	for (int i = 0; i < vec12.size(); i++) {
		int index;
		if (vec12[i] % 3 == 1) {
			index = vec12[i] / 3;
		}
		else {
			index = vec12[i] / 3 + (len + 1) / 3;
		}
		if (i == 0) {
			sa12[index] = order_temp;
			continue;
		}
		bool flag = true;
		for (int j = 0; j < 3; j++) {
			if (str[vec12[i] + j] != str[vec12[i - 1] + j]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			sa12[index] = order_temp;
		}
		else {
			sa12[index] = ++order_temp;
		}
	}
	if (order_temp != sa12.size()) {
		sa12 = recursive_func(sa12);
		for (int i = 0; i < (len + 1) / 3; i++) {
			vec12[sa12[i]] = i * 3 + 1;
		}
		for (int i = (len + 1) / 3; i < sa12.size(); i++) {
			vec12[sa12[i]] = (i - (len + 1) / 3) * 3 + 2;
		}
	}

	vector<int> rank12(len + 2, 0);
	for (int i = 0; i < (len + 1) / 3; i++) {
		rank12[i * 3 + 1] = sa12[i] + 1;
	}
	for (int i = (len + 1) / 3; i < sa12.size(); i++) {
		rank12[(i - (len + 1) / 3) * 3 + 2] = sa12[i] + 1;
	}
	vector<int> vec0 = radix_sort0(str, rank12, len);
	vector<int> vec = merge_sa(str, vec0, vec12, rank12);
	vector<int> sa(len);
	for (int i = 0; i < len; i++) {
		sa[vec[i]] = i;
	}
	return sa;
}
vector<int> sa_func(vector<int> str) {
	int len = str.size();
	str.push_back(0);
	str.push_back(0);

	vector<int> vec12 = radix_sort12(str, len);
	vector<int> sa12(vec12.size());
	int order_temp = 1;

	for (int i = 0; i < vec12.size(); i++) {
		int index;
		if (vec12[i] % 3 == 1) {
			index = vec12[i] / 3;
		}
		else {
			index = vec12[i] / 3 + (len + 1) / 3;
		}
		if (i == 0) {
			sa12[index] = order_temp;
			continue;
		}
		bool flag = true;
		for (int j = 0; j < 3; j++) {
			if (str[vec12[i] + j] != str[vec12[i - 1] + j]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			sa12[index] = order_temp;
		}
		else {
			sa12[index] = ++order_temp;
		}
	}
	if (order_temp != sa12.size()) {
		vector<int> temp;
		for (int i = 0; i < (len + 1) / 3; i++) {
			temp.push_back(sa12[i]);
		}
		temp.push_back(0);
		for (int i = (len + 1) / 3; i < sa12.size(); i++) {
			temp.push_back(sa12[i]);
		}
		temp = sa_func(temp);
		int flag = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] == (len + 1) / 3) {
				flag = 1;
				continue;
			}
			if (temp[i] > (len + 1) / 3) {
				sa12[temp[i] - 1] = i - flag;
			}
			else {
				sa12[temp[i]] = i - flag;
			}
		}
		
		for (int i = 0; i < (len + 1) / 3; i++) {
			vec12[sa12[i]] = i * 3 + 1;
		}
		for (int i = (len + 1) / 3; i < sa12.size(); i++) {
			vec12[sa12[i]] = (i - (len + 1) / 3) * 3 + 2;
		}
	}
	
	vector<int> rank12(len + 2, 0);
	for (int i = 0; i < (len + 1) / 3; i++) {
		rank12[i * 3 + 1] = sa12[i] + 1;
	}
	for (int i = (len + 1) / 3; i < sa12.size(); i++) {
		rank12[(i - (len + 1) / 3) * 3 + 2] = sa12[i] + 1;
	}
	vector<int> vec0 = radix_sort0(str, rank12, len);
	vector<int> vec = merge_sa(str, vec0, vec12, rank12);

	return vec;
}
int main() {
	cin >> str;
	if (str.length() == 1) {
		cout << str << endl;
		return 0;
	}
	vector<int> vec;
	for (int i = 0; i < str.length(); i++) {
		vec.push_back(str[i]);
	}
	vec = sa_func(vec);
	vector<string> temp(str.length());
	string t = "";
	for (int i = str.length() - 1; i >= 0; i--)
	{
		t = str[i] + t;
		temp[i] = t;
	}
	for (int i = 0; i < vec.size(); i++) {
		cout << temp[vec[i]] << endl;
	}
	return 0;
}