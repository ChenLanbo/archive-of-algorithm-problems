#include <iostream>
#include <cstdlib>
#include <ctime>

template <class Key, class Value>
class SkipList {
public:
	SkipList(int height, const Key min_key, const Value default_value) {
		this->max_height = height;
		this->current_height = 0;
		this->min_key = min_key;
		this->default_value = default_value;
		this->head = new Node(this->min_key, this->default_value, this->max_height);
		srand(time(NULL));
	}

	~SkipList() {
	}

	Value search(const Key &key) const {
		return search_internal(head, key, current_height);
	}

	void inseart(const Key &key, const Value &value) {
		insert_internal(this->head, new Node(key, value, this->rand_size_gen()), this->current_height);
	}

private:

	struct Node {
		Key key;
		Value value;
		int size;
		Node **next;

		Node(const Key key, const Value value, int size) {
			this->key = key;
			this->value = value;
			this->size = size;
			this->next = new Node*[size];
			for (int i = 0; i < size; ++i) {
				this->next[i] = 0;
			}
		}
	};

	typedef Node* const Link;

	Link head;
	int max_height;
	int current_height;
	Key min_key;
	Value default_value;

	int rand_size_gen() {
		int i, j, r = rand();
		for (i = 0, j = 1; i < this->max_height; ++i, j <<= 1)
			if (r > RAND_MAX / (j << 1)) break;
		if (current_height < i) current_height = i;
		return i;
	}

	Value search_internal(const Link link, const Key &key, const int level) const {
		if (link->key == key) {
			return link->value;
		}

		Link n = link->next[level];
		if (n == 0) {
			if (level == 0) return default_value;
			return search_internal(link, key, level - 1);
		} else if (n->key > key ) {
			return search_internal(link, key, level - 1);
		}

		return search_internal(n, key, level);
	}

	void insert_internal(Link r, Link new_link, int level) {
		Link n = r->next[level];
		
		if (n == 0 || new_link->key < n->key) {
			if (level < new_link->size) {
				new_link->next[level] = n;
				r->next[level] = new_link;
			}
			if (level == 0) return ;

			insert_internal(r, new_link, level - 1);
			return ;
		}
		insert_internal(n, new_link, level);
	}

	void remove_internal(Link r, const Key &key, int level) {
		if (r == 0) return ;
		Link n = r->next[level];

		if (n != 0 && key <= n->key) {
			if (key == n->key) {
				r->next[level] = n->next[level];
				if (level == 0) {
					delete n;
				}
			}
			if (level == 0) return ;
			remove_internal(r, key, level - 1);
		}
		remove_internal(r->next[level], key, level);
	}
};

int main() {
	;
}
