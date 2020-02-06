#include <iostream>
#include <string>
using namespace std;
struct node {
	int s, e;//가르키는 문자열 시작, 끝
	node* left_sibling;//형제 노드
	node* right_sibling;
	node* child;//자식 노드
	node* parent;//부모 노드
	node* suffix_link;//xa->a
	node() {
		parent = NULL;
		left_sibling = NULL;
		right_sibling = NULL;
		child = NULL;
		suffix_link = NULL;
	}
};
int main() {
	string str;//입력 문자열
	cin >> str;//길이 n
	str += "$";
	cout << str << endl;
	node* root = new node;
	node* temp = new node;
	//1~n suffix 입력
	temp->s = 0;
	temp->e = str.length() - 1;
	root->child = temp;
	temp->parent = root;
	node* now;//현재 이동중
	node* head_locus = root;//전 단계 contracted locus of head
	int head_s = -1, head_e = -2;//전 단계 head
	int x;//-1 : NULL
	int a_s, a_e;
	int b_s, b_e;
	int c_s, c_e;
	int index;//현재단계 suffix
	int head_index;//전 단계 head suffix
	for (int i = 1; i < str.length(); i++) {
		index = i;
		b_s = head_s;
		b_e = head_e;
		if (head_s <= head_e) {//head not null
			b_s++;
		}
		//step A
		if (head_locus == root) {
			now = head_locus;
		}
		else {
			now = head_locus->suffix_link;
			b_s = now->e + 1;
		}
		head_s = i;
		//step B
		while (1) {
			if (b_e - b_s > (now->child->e) - (now->child->s)) {
				b_s = now->child->e + 1;
				now = now->child;
			}
			else if (b_e - b_s == (now->child->e) - (now->child->s)) {
				now = now->child;
				c_s = now->s;
				head_locus->suffix_link = now;
				c_e = c_s;
				index += now->e;
				//step C

				break;
			}
			else {
				//step C

			}
		}
		temp = new node;
		temp->parent = now;
	}
	return 0;
}