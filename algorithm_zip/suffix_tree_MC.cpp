#include <iostream>
#include <string>
using namespace std;
struct node {
	int s, e;//����Ű�� ���ڿ� ����, ��
	node* left_sibling;//���� ���
	node* right_sibling;
	node* child;//�ڽ� ���
	node* parent;//�θ� ���
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
	string str;//�Է� ���ڿ�
	cin >> str;//���� n
	str += "$";
	cout << str << endl;
	node* root = new node;
	node* temp = new node;
	//1~n suffix �Է�
	temp->s = 0;
	temp->e = str.length() - 1;
	root->child = temp;
	temp->parent = root;
	node* now;//���� �̵���
	node* head_locus = root;//�� �ܰ� contracted locus of head
	int head_s = -1, head_e = -2;//�� �ܰ� head
	int x;//-1 : NULL
	int a_s, a_e;
	int b_s, b_e;
	int c_s, c_e;
	int index;//����ܰ� suffix
	int head_index;//�� �ܰ� head suffix
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