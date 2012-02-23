#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
#define RED 1
#define BLACK 0
struct Node {
	Node *lc, *rc, *pa;
	int color;
	int key;
	Node(){ }
	Node(int val){
		lc = rc = pa = NULL;
		key = val;
		color = RED;
	}
};

class RBTree {
	public:
	Node *root;

	RBTree(){
		root = NULL;
	}

	void print(){
		_print(root, 0);
		cout << endl << endl;
	}

	void insert(int val){
		_insert(new Node(val));
	}

	Node *search(int key){
		return _search(root, key);
	}

	Node *minimum(Node *u){
		if (u == NULL){
			return NULL;
		}
		while (u->rc != NULL){
			u = u->rc;
		}
		return u;
	}

	void remove(Node *z){
		Node *y = z, *x;
		int color;
		if (z == NULL){
			return ;
		}
		color = y->color;
		if (z->lc == NULL && z->rc == NULL){
			if (z->pa == NULL){
				root = NULL;
			} else if (z == z->pa->lc){
				z->pa->lc = NULL;
			} else {
				z->pa->rc = NULL;
			}
			x = NULL;
		} else if (z->lc == NULL){
			x = z->rc;
			transplant(z, z->rc);
		} else if (z->rc == NULL){
			x = z->lc;
			transplant(z, z->lc);
		} else {
			y = minimum(z->rc);
			color = y->color;
			x = y->rc;
			if (y->pa == z){
				if (x){
					x->pa = y;
				}
			} else {
				transplant(y, y->rc);
				y->rc = z->rc;
				y->rc->pa = y;
			}
			transplant(z, y);
			y->lc = z->lc;
			y->lc->pa = y;
			y->color = z->color;
		}
		if (color == BLACK && root != NULL){
			puts("Fixup");
			remove_fixup(x);
		}
		delete z;
	}

	private:

	void left_rotate(Node *x){
		Node *y = x->rc;
		x->rc = y->lc;
		if (y->lc != NULL){
			y->lc->pa = x;
		}
		y->pa = x->pa;
		if (x->pa == NULL){
			root = y;
		} else if (x == x->pa->lc) {
			x->pa->lc = y;
		} else {
			x->pa->rc = y;
		}
		y->lc = x;
		x->pa = y;
	}

	void right_rotate(Node *x){
		Node *y = x->lc;
		x->lc = y->rc;
		if (y->rc != NULL){
			y->rc->pa = x;
		}
		y->pa = x->pa;
		if (x->pa == NULL){
			root = y;
		} else if (x == x->pa->lc){
			x->pa->lc = y;
		} else {
			x->pa->rc = y;
		}
		y->rc = x;
		x->pa = y;
	}

	void transplant(Node *u, Node *v){
		if (u->pa == NULL){
			root = v;
		} else if (u == u->pa->lc){
			u->pa->lc = v;
		} else {
			u->pa->rc = v;
		}
		v->pa = u->pa;
	}

	void _print(Node *node, int dep){
		if (node == NULL) return ;
		if (node->lc) _print(node->lc, dep + 1);
		printf("%d: col %d -- dep %d\n", node->key, node->color, dep);
		if (node->rc) _print(node->rc, dep + 1);
	}

	void _insert(Node *z){
		Node *y = NULL, *x = root;
		while (x != NULL){
			y = x;
			if (z->key < x->key){
				x = x->lc;
			} else {
				x = x->rc;
			}
		}
		z->pa = y;
		if (y == NULL){
			root = z;
		} else if (z->key < y->key){
			y->lc = z;
		} else {
			y->rc = z;
		}
		z->lc = z->rc = NULL;
		z->color = RED;
		insert_fixup(z);
		// puts("**** _insert done");
	}

	void insert_fixup(Node *z){
		Node *y;
		if (z == root){
			z->color = BLACK;
			return ;
		}
		// printf("insert_fixup %d\n", z->pa->color);
		while (z != root && z->pa->color == RED){
			if (z->pa == z->pa->pa->lc){
				y = z->pa->pa->rc;
				if (y != NULL && y->color == RED){
					z->pa->color = BLACK;
					y->color = BLACK;
					z->pa->pa->color = RED;
					z = z->pa->pa;
				} else if (z == z->pa->rc){
					z = z->pa;
					left_rotate(z);
				} else {
					z->pa->color = BLACK;
					z->pa->pa->color = RED;
					right_rotate(z->pa->pa);
				}
			} else {
				y = z->pa->pa->lc;
				if (y != NULL && y->color == RED){
					z->pa->color = BLACK;
					y->color = BLACK;
					z->pa->pa->color = RED;
					z = z->pa->pa;
				} else if (z == z->pa->lc){
					z = z->pa;
					right_rotate(z);
				} else {
					z->pa->color = BLACK;
					z->pa->pa->color = RED;
					left_rotate(z->pa->pa);
				}
			}
		}
		root->color = BLACK;
	}

	Node *_search(Node *rt, int key){
		if (rt == NULL || rt->key == key){
			return rt;
		}
		if (key < rt->key){
			return _search(rt->lc, key);
		} else {
			return _search(rt->rc, key);
		}
	}

	void remove_fixup(Node *x){
		Node *w;
		if (x == NULL) return ;
		printf("--- %d\n", x->key);
		while (x != root && x->color == BLACK){
			if (x == x->pa->lc){
				w = x->pa->rc;
				if (w->color == RED){
					w->color = BLACK;
					x->pa->color = RED;
					left_rotate(x->pa);
					w = x->pa->rc;
				}
				if (w->lc->color == BLACK && w->rc->color == BLACK){
					w->color = RED;
					x = x->pa;
				} else if (w->rc->color == BLACK){
					w->lc->color = BLACK;
					w->color = RED;
					right_rotate(w);
					w = x->pa->rc;
				} else {
					w->color = x->pa->color;
					x->pa->color = BLACK;
					w->rc->color = BLACK;
					left_rotate(x->pa);
					x = root;
				}
			} else {
				w = x->pa->lc;
				if (w->color == RED){
					w->color = BLACK;
					x->pa->color = RED;
					right_rotate(x->pa);
					w = x->pa->lc;
				}
				if (w->rc->color == BLACK && w->lc->color == BLACK){
					w->color = RED;
					x = x->pa;
				} else if (w->lc->color == BLACK){
					w->rc->color = BLACK;
					w->color = RED;
					left_rotate(w);
					w = x->pa->lc;
				} else {
					w->color = x->pa->color;
					x->pa->color = BLACK;
					w->lc->color = BLACK;
					right_rotate(x->pa);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
};

int main(){
	int cmd, v;
	RBTree rb;
	srand(time(NULL));
	for (int i = 0; i < 5; i++){ rb.insert(rand() % 100 + 1); }
	rb.print();

	while (cin >> cmd){
		if (cmd == 0){
			// insert
			cin >> v;
			rb.insert(v);
			puts("Insert done");
		} else if (cmd == 1){
			// search
			cin >> v;
			Node *p = rb.search(v);
			if (p) printf("Found %d\n", v);
			else printf("Not Found\n");
		} else if (cmd == 2){
			// remove
			cin >> v;
			Node *p = rb.search(v);
			puts("Removing");
			if (p) rb.remove(p);
			puts("Remove done");
		} else {
			rb.print();
			puts("");
		}
	}
}
