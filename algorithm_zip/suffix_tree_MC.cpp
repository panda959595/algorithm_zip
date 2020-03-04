#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>
using namespace std;
struct node {
	int s, e;//가르키는 문자열 시작, 끝
	int index;
	list<node*> child;
	node* parent;//부모 노드
	node* suffix_link;//xa->a
	bool check;
	node() {
		parent = NULL;
		suffix_link = NULL;
		check = false;
	}
};
struct String {
	int s, e;
};
string str;//입력 문자열
bool bigyo(node* a, node* b) {
	int i = a->s;
	int j = b->s;
	while (1) {
		if (i > a->e) {
			return true;
		}
		if (j > b->e) {
			return false;
		}
		if (str[i] != str[j]) {
			return str[i] < str[j];
		}
		i++;
		j++;
	}
}
void insert_node(node* new_node, node* temp_node, int size) {
	new_node->s = temp_node->s;
	new_node->e = new_node->s + size - 1;
	temp_node->s = new_node->e + 1;
	new_node->child.push_back(temp_node);
	new_node->parent = temp_node->parent;
	bool flag = true;
	for (list<node*>::iterator ite = temp_node->parent->child.begin(); ite != temp_node->parent->child.end(); ite++) {
		if (!bigyo(*ite, new_node)) {
			temp_node->parent->child.insert(ite, new_node);
			flag = false;
			break;
		}
	}
	if (flag) {
		temp_node->parent->child.insert(temp_node->parent->child.end(), new_node);
	}
	temp_node->parent->child.remove(temp_node);
	temp_node->parent = new_node;
}
int main() {
	cin >> str;//길이 n
	str += "~";
	cout << str << endl;
	int len = str.length();
	node* root = new node;
	node* new_node = new node;
	new_node->s = 0;
	new_node->e = len - 1;
	new_node->parent = root;
	new_node->index = 0;
	root->child.push_back(new_node);
	String x, a, b, c;
	String head_now;
	String head_pre;
	node* head_pre_contracted_locus = NULL;
	node* now;
	int step_flag;//0 1 2
	now = root;
	head_pre.s = 1;
	head_pre.e = 0;
	for (int i = 1; i < len - 1; i++) {
 		head_now.s = i;
		head_now.e = i;
		if (head_pre.e - head_pre.s < 0) {
			now = root;
			step_flag = 2;
		}
		if (step_flag == 0) {//step A
			if (a.e - a.s < 0) {
				now = root;
			}
			else {
				now = now->suffix_link;
			}
			if (b.e - b.s < 0) {
				step_flag += 2;
			}
			else {
				step_flag++;
			}
			head_now.e += x.e - x.s + 1;
			head_now.e += a.e - a.s + 1;
		}
		if (step_flag == 1) {//step B
			while (1) {
				node* child_temp = NULL;// child_temp가 무조건 존재
				for (auto k : now->child) {
					if (str[b.s] == str[k->s]) {
						child_temp = k;
						break;
					}
				}
				if (b.e - b.s > child_temp->e - child_temp->s) {
					b.s = child_temp->e + 1;
					now = child_temp;
				}
				else if (b.e - b.s == child_temp->e - child_temp->s) {
					now = child_temp;
					step_flag = 2;
					break;
				}
				else {
					new_node = new node;
					insert_node(new_node, child_temp, b.e - b.s + 1);
					now = new_node;
					if (now->e != len - 1) {
						new_node = new node;
						new_node->s = now->e + 1;
						new_node->e = len - 1;
						new_node->parent = now;
						now->child.push_back(new_node);
					}
					new_node->index = i;
					head_pre_contracted_locus = now;
					step_flag = 0;
					break;
				}
			}
			head_pre_contracted_locus->suffix_link = now;
		}
		if (step_flag == 2) {//step C
			node* child_temp;
			while (1) {
				// child_temp가 존재 안 할수도
				child_temp = NULL;
				for (auto k : now->child) {
					if (str[head_now.e] == str[k->s]) {
						child_temp = k;
						break;
					}
				}
				if (child_temp == NULL) {
					new_node = new node;
					new_node->s = head_now.e;
					new_node->e = len - 1;
					new_node->parent = now; 
					bool flag = true;
					for (list<node*>::iterator ite = now->child.begin(); ite != now->child.end(); ite++) {
						if (!bigyo(*ite, new_node)) {
							now->child.insert(ite, new_node);
							flag = false;
							break;
						}
					}
					new_node->index = i;
					if (flag) {
						now->child.insert(now->child.end(), new_node);
					}
					now = new_node;
					break;
				}
				bool end_flag = false;
				for (int i = child_temp->s; i <= child_temp->e; i++) {
					if (str[i] != str[head_now.e]) {
						end_flag = true;
						break;
					}
					head_now.e++;
				}
				if (end_flag) {
					new_node = new node;
					insert_node(new_node, child_temp, head_now.e - head_now.s);
					now = new_node;
					if (now->e != len - 1) {
						new_node = new node;
						new_node->s = head_now.e;
						new_node->e = len - 1;
						new_node->parent = now;
						bool flag = true;
						for (list<node*>::iterator ite = now->child.begin(); ite != now->child.end(); ite++) {
							if (!bigyo(*ite, new_node)) {
								now->child.insert(ite, new_node);
								flag = false;
								break;
							}
						}
						if (flag) {
							now->child.insert(now->child.end(), new_node);
						}
					}
					new_node->index = i;
					head_pre_contracted_locus = now;
					step_flag = 0;
					break;
				}
				now = child_temp;
			}
		}
		//x a b 결정
		now = now->parent;
		//x
		if (head_now.e - head_now.s < 0) {
			x.s = 1;
			x.e = 0;
		}
		else {
			x.s = x.e = head_now.s;
		}
		//a
		if (now == root) {
			a.s = 1;
			a.e = 0;
		}
		else {
			a.s = now->s + x.e - x.s + 1;
			a.e = now->e;
		}
		//b
		b.e = head_now.e;
		b.s = head_now.s;
		b.s += x.e - x.s + 1;
		b.s += a.e - a.s + 1;
	}
	now = root;
	stack<node*> sta;
	sta.push(now);
	root->check = true;
	while (!sta.empty()) {
		node* now = sta.top();
		if (now->child.size() == 0) {
			sta.pop();
			continue;
		}
		list<node*>::iterator ite = now->child.end();
		ite--;
		if ((*ite)->s == len - 1 && !((*ite)->check)) {
			(*ite)->check = true;
			cout << (*ite)->index<<" ";
		}
		for (auto k : now->child) {
			if (k->check) {
				continue;
			}
			k->check = true;
			if (k->index >= 0) {
				cout << k->index << " ";
			}
			sta.push(k);
			break;
		}
		if (sta.top() == now) {
			sta.pop();
		}
	}
	return 0;
}