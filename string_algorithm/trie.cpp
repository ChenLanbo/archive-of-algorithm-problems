#include <iostream>
#include <cstring>
using namespace std;
struct Node {
	int end;
	Node *next[26];
	Node(){
		end = 0;
		memset(next, 0, sizeof(next));
	}
};

class Trie {
	public:
		Trie(){
			root = new Node();
		}

		void insert(char str[]){
			Node *r = root;
			for (int i = 0; str[i] != '\0'; i++){
				if (r->next[str[i] - 'a'] == NULL){
					Node *p = new Node();
					r->next[str[i]-'a'] = p;
				}
				r = r->next[str[i]-'a'];
			}
			r->end = 1;
		}

		bool query(char str[]){
			Node *r = root;
			for (int i = 0; str[i] != '\0'; i++){
				if (r->next[str[i] - 'a'] == NULL){
					return false;
				}
				r = r->next[str[i] - 'a'];
			}
			if (r->end == 0){
				return false;
			} else {
				return true;
			}
		}

		~Trie(){
			dealloc(root);
		}

	private:
		void dealloc(Node *rt){
			for (int i = 0; i < 26; i++){
				if (rt->next[i]){
					dealloc(rt->next[i]);
				}
			}
			delete rt;
		}

		Node *root;
};

int main(){
	Trie trie;
	trie.insert("abc");
	trie.insert("abd");
	trie.insert("uva");
	cout << "INSERT DONE" << endl;
	cout << trie.query("ab") << endl;
	cout << trie.query("abc") << endl;
}
