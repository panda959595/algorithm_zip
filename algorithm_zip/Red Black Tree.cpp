#include <iostream>
#define BLACK 0
#define RED 1
using namespace std;
struct node {
	bool color;// 0 : BLACK, 1 : RED
	int key;
	node *left;
	node *right;
	node *parent;
	int size;// 자기자신 포함 자식수
};
class RBtree {
public:
	RBtree() {
		root = new node;
		NIL = new node;
		root->color = BLACK;
		root->key = 0;
		root->left = NIL;
		root->right = NIL;
		root->parent = NIL;
		root->size = 0;
		NIL->color = BLACK;
		NIL->size = 0;
	}
	node *find_min(node *now) {
		node *ret = now;
		while (now->left == NIL) {
			ret = now->left;
		}
		return ret;
	}
	node *find_max(node *now) {
		node *ret = now;
		while (now->right == NIL) {
			ret = now->right;
		}
		return ret;
	}
	node *find(node *now, int num) {
		while (now != NIL) {
			if (now->key == num) {
				return now;
			}
			else if (now->key > num) {
				now = now->left;
			}
			else {
				now = now->right;
			}
		}
		return NIL;
	}
	void left_rotate(node *x) {// 부모기준
		node *y = x->right;
		x->right = y->left;
		if (x->right != NIL) {
			(x->right)->parent = x;
		}
		y->parent = x->parent;
		if (y->parent == NIL) {
			root = y;
		}
		else if (x == (x->parent)->left) {
			(x->parent)->left = y;
		}
		else {
			(x->parent)->right = y;
		}
		y->left = x;
		x->parent = y;
		y->size = x->size;
		x->size = (x->left)->size + (x->right)->size + 1;
	}
	void right_rotate(node *x) {//부모기준
		node *y = x->left;
		x->left = y->right;
		if (x->left != NIL) {
			(x->left)->parent = x;
		}
		y->parent = x->parent;
		if (y->parent == NIL) {
			root = y;
		}
		else if (x == (x->parent)->left) {
			(x->parent)->left = y;
		}
		else {
			(x->parent)->right = y;
		}
		y->right = x;
		x->parent = y;
		y->size = x->size;
		x->size = (x->left)->size + (x->right)->size + 1;
	}
	void push_restore(node *now) {// after push
		if (now->color == BLACK) {
			return;
		}
		while ((now->parent)->color == RED) {
			node *gp = (now->parent)->parent;
			if ((gp->left)->color == (gp->right)->color) {//parent and uncle is RED
				gp->left->color = BLACK;
				gp->right->color = BLACK;
				gp->color = RED;
				now = gp;
			}
			else {//uncle is BLACK
				if (now == (now->parent)->left) {
					if (now->parent == gp->left) {
						(now->parent)->color = BLACK;
						gp->color = RED;
						right_rotate(gp);
					}
					else {
						now = now->parent;
						left_rotate(now);
					}
				}
				else {//now is right child
					if (now->parent == gp->left) {
						right_rotate((now->parent)->parent);
						now = gp;
					}
					else {
						(now->parent)->color = BLACK;
						gp->color = RED;
						left_rotate(gp);
					}
				}
			}
		}
		root->color = BLACK;
	}
	void push(int num) {
		if (root->size == 0) {
			root->key = num;
			root->size = 1;
			return;
		}
		node *now = root;
		node *temp = new node;
		while (1) {
			now->size++;
			if (now->key > num) {
				if (now->left != NIL) {
					now = now->left;
				}
				else {
					now->left = temp;
					break;
				}
			}
			else {
				if (now->right != NIL) {
					now = now->right;
				}
				else {
					now->right = temp;
					break;
				}
			}
		}
		temp->color = RED;
		temp->key = num;
		temp->parent = now;
		temp->right = NIL;
		temp->left = NIL;
		temp->size = 1;
		push_restore(temp);
	}
	void pop(int num) {
		//z : 지워지는 노드, y : z의 원래 위치로 올노드, x : y의 원래 위치로 올 노드
		node *z = find(root, num);
		if (z == NIL) {
			return;
		}
		node *y = z;
		node *x;
		bool y_origin_color = y->color;
		if (z->left == NIL) {
			x = z->right;
			if (z == root) {
				root = x;
			}
			else if (z == (z->parent)->right) {
				(z->parent)->right = x;
				(z->parent)->size--;
			}
			else {
				(z->parent)->left = x;
				(z->parent)->size--;
			}
			x->parent = z->parent;
		}
		else if (z->right == NIL) {
			x = z->left;
			if (z == root) {
				root = x;
			}
			else if (z == (z->parent)->right) {
				(z->parent)->right = x;
				(z->parent)->size--;
			}
			else {
				(z->parent)->left = x;
				(z->parent)->size--;
			}
			x->parent = z->parent;
		}
		else {
			y = find_min(z->right);
			y_origin_color = y->color;
			x = y->right;
			if (y->parent != z) {
				(y->parent)->left = x;
				(y->parent)->size--;
				x->parent = y->parent;
				y->right = z->right;
			}
			if (z == root) {
				root = x;
			}
			else if (z == (z->parent)->right) {
				(z->parent)->right = y;
				(z->parent)->size--;
			}
			else {
				(z->parent)->left = y;
				(z->parent)->size--;
			}
			y->left = z->left;
			(y->left)->parent = y;
			y->color = z->color;
			y->size = z->size - 1;
		}
		if (y_origin_color == BLACK) {
			pop_restore(x);
		}
	}
	void pop_restore(node *now) {
		while (now != root && now->color == BLACK) {
			if ((now->parent)->color == RED) {// brother is RED
				if (now == (now->parent)->left) {//now is left, right rotate
					node *bro = (now->parent)->right;
					bro->color = BLACK;
					(now->parent)->color = RED;
					right_rotate(now->parent);
				}
				else {//now is right, left rotate
					node *bro = (now->parent)->left;
					bro->color = BLACK;
					(now->parent)->color = RED;
					left_rotate(now->parent);
				}
			}
			else {//brother is BLACK
				if (now == (now->parent)->left) {//now is left
					node *bro = (now->parent)->right;
					if ((bro->left)->color == BLACK && (bro->right)->color == BLACK) {//bro's child all BLACK
						bro->color = RED;
						now = now->parent;
					}
					else if ((bro->right)->color == BLACK) {//bro's left child RED, right child BLACK
						(bro->right)->color = BLACK;
						bro->color = RED;
						right_rotate(bro);
					}
					else {//bro's right child RED
						bro->color = RED;
						(now->parent)->color = BLACK;
						(bro->right)->color = BLACK;
						left_rotate(now->parent);
						now = root;
					}
				}
				else {//now is right
					node *bro = (now->parent)->left;
					if ((bro->left)->color == BLACK && (bro->right)->color == BLACK) {//bro's child all BLACK
						bro->color = RED;
						now = now->parent;
					}
					else if ((bro->left)->color == BLACK) {//bro's left child BLACK, right child RED
						(bro->left)->color = BLACK;
						bro->color = RED;
						right_rotate(bro);
					}
					else {//bro's right child RED
						bro->color = RED;
						(now->parent)->color = BLACK;
						(bro->left)->color = BLACK;
						left_rotate(now->parent);
						now = root;
					}
				}
			}
		}
		now->color = BLACK;
	}
	int rank(int num) {
		node* now = root;
		int ret = 0;
		while (now->key != num) {
			if (now->key > num) {
				now = now->left;
			}
			else {
				ret += (now->left)->size + 1;
				now = now->right;
			}
		}
		ret += (now->left)->size;
		return ret;
	}
private:
	node *root;
	node *NIL;
};
int main() {
	RBtree a;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		a.push(temp);
	}
	return 0;
}