#include <iostream>
#include <string>
using namespace std;
struct node {
	int s, e;//가르키는 문자열 시작, 끝
	node* next_sibling;//형제 노드
	node* pre_sibling;
	node* child;//자식 노드
	node* parent;//부모 노드
	node* suffix_link;//xa->a
	node() {
		parent = NULL;
		next_sibling = NULL;
		pre_sibling = NULL;
		child = NULL;
		suffix_link = NULL;
	}
};
struct String {
	int s, e;
};
int main() {
	string str;//입력 문자열
	cin >> str;//길이 n
	str += "$";
	cout << str << endl;
	int len = str.length();
	node* root = new node;
	node* new_node = new node;
	new_node->s = 0;
	new_node->e = len - 1;
	new_node->parent = root;
	root->child = new_node;
	String x, a, b, c;
	String head_now;
	String head_pre;
	node* head_pre_contracted_locus;
	node* now;
	int step_flag;//0 1 2
	now = root;
	head_pre.s = 1;
	head_pre.e = 0;
	for (int i = 1; i < len; i++) {
		head_now.s = i;
		head_now.e = i;
		if (head_pre.e - head_pre.s < 0) {
			step_flag = 2;
		}
		if (step_flag == 0) {
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
		if (step_flag == 1) {
			node* child_temp;
			while (1) {
				child_temp = now->child;
				while (str[child_temp->s] != str[b.s]) {
					child_temp = child_temp->next_sibling;
				}
				if (b.e - b.s > child_temp->e - child_temp->s) {
					b.s = child_temp->e + 1;
					now = child_temp;
				}
				else if (b.e - b.s == child_temp->e - child_temp->s) {

				}
			}
		}
		if (step_flag == 2) {
			node* child_temp;
			while (1) {
				child_temp = now->child;
				bool end_flag = false;
				while (str[child_temp->s] != str[head_now.e]) {
					if (child_temp->next_sibling == NULL) {
						end_flag = true;
						break;
					}
					child_temp = child_temp->next_sibling;
				}
				if (end_flag) {
					break;
				}
				for (int i = child_temp->s; i <= child_temp->e; i++) {
					if (str[i] != str[head_now.e]) {
						end_flag = true;
						break;
					}
					head_now.e++;
				}
				if (end_flag) {
					break;
				}
				now = child_temp;
			}
			new_node = new node;//head_now
			if (child_temp->pre_sibling == NULL) {//첫째자식에 넣을때
				new_node->s = child_temp->s;
				new_node->e = child_temp->s + head_now.e - head_now.s + 1;
				child_temp->s = child_temp->s + head_now.e - head_now.s + 2;
				new_node->child = child_temp;
				new_node->parent = child_temp->parent;
				new_node->next_sibling = child_temp->next_sibling;
				child_temp->parent->child = new_node;
				child_temp->parent = new_node;
				child_temp->next_sibling = NULL;
			}
			else {//형제사이에 넣을때
				new_node->s = child_temp->s;
				new_node->e = child_temp->s + head_now.e - head_now.s + 1;
				child_temp->s = child_temp->s + head_now.e - head_now.s + 2;
				new_node->next_sibling = child_temp->next_sibling;
				new_node->pre_sibling = child_temp->next_sibling;
				new_node->child = child_temp;
				child_temp->pre_sibling->next_sibling = new_node;
				if (child_temp->next_sibling != NULL) {
					child_temp->next_sibling->pre_sibling = new_node;
				}
				child_temp->pre_sibling = child_temp->next_sibling = NULL;
			}
			now = new_node;
			new_node = new node;
			new_node->s = head_now.e + 1;
			new_node->e = len - 1;
			new_node->pre_sibling = child_temp;
			child_temp->next_sibling = new_node;
		}

		//x a b 결정
		while (now->pre_sibling != NULL) {
			now = now->pre_sibling;
		}
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

	return 0;
}