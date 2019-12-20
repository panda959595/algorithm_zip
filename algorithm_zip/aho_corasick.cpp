#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;
struct trie {
	trie *go[26];
	trie *fail;
	bool output;
	trie() {
		for (int i = 0; i < 26; i++) {
			go[i] = NULL;
		}
		output = false;
	}
};
class aho_corasick {
public:
	aho_corasick() {
		root = new trie;
	}
	bool aho_check(string str) {
		trie *now = root;
		for (int i = 0; i < str.length(); i++) {
			while (now != root && now->go[str[i] - 'a'] == NULL) {
				now = now->fail;
			}
			if (now->go[str[i] - 'a'] != NULL) {
				now = now->go[str[i] - 'a'];
			}
			if (now->output) {
				return true;
			}
		}
		return false;
	}
	void set_pattern(string str) {
		pattern.push_back(str);
		trie_set(str);
	}
	void trie_set(string str) {
		trie *now = root;
		for (int i = 0; i < str.length(); i++) {
			if (now->go[str[i] - 'a'] == NULL) {
				trie *temp = new trie;
				now->go[str[i] - 'a'] = temp;
				now = temp;
			}
			else {
				now = now->go[str[i] - 'a'];
			}
		}
		now->output = true;
	}
	void set_fail() {
		queue<trie*> que;
		que.push(root);
		while (!que.empty()) {
			trie *now = que.front();
			que.pop();
			for (int i = 0; i < 26; i++) {
				trie *next = now->go[i];
				if (next == NULL) {
					continue;
				}
				if (now == root) {
					next->fail = root;
				}
				else {
					trie *fail_temp = now->fail;
					while (fail_temp != root && fail_temp->go[i] == NULL) {
						fail_temp = fail_temp->fail;
					}
					if (fail_temp->go[i] != NULL) {
						fail_temp = fail_temp->go[i];
					}
					next->fail = fail_temp;
				}
				if (next->fail->output) {
					next->output = true;
				}
				que.push(next);
			}
		}
	}
private:
	vector<string> pattern;
	trie *root;
};
int main() {
	aho_corasick aho;
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string temp;
		cin >> temp;
		aho.set_pattern(temp);
	}
	aho.set_fail();
	cin >> m;
	for (int i = 0; i < m; i++) {
		string temp;
		cin >> temp;
		if (aho.aho_check(temp)) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	return 0;
}
