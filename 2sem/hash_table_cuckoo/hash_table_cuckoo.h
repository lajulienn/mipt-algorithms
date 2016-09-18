#ifndef HASH_TABLE_CUCKOO_
#define HASH_TABLE_CUCKOO_

#include <string>
#include <cstdlib>
#include <cstring>
#include <utility>

#define INIT_CAPACITY 4

template <typename V>
class HashTable{
	using K = std::string;
public:
	HashTable(int capacity = INIT_CAPACITY) : capacity_(capacity), size_(0) {
		hash_constant1_ = rand();
		hash_constant2_ = rand();
		table_ = new Node[capacity];
	}
	~HashTable() { delete[] table_; }

	int size() const { return size_; }
	bool empty() const { return size_ == 0; }
	V &operator[](K key);
	void erase(K key);
	void clear();
	//void dump();
	bool exist(K key) { return find(key) != end(); }
private:
	//friend class Node;
	struct Node {
		friend class HashTable;
		K key;
		V value;
	private:
		Node() : is_empty(true) {}
		bool is_empty;
	};

	unsigned hash_function(K str, unsigned hash_constant);
	void new_constant();
	void rehash();
	void incr_capacity();
	Node *next(Node *current);

	int capacity_;
	int size_;
	Node *table_;
	unsigned hash_constant1_;
	unsigned hash_constant2_;

	friend class Iterator;
public:
	class Iterator {
		friend class HashTable;
	private:
		Iterator(HashTable *ht, Node *n) : hash_table(ht), node(n) {}

		HashTable *hash_table;
		Node *node;
	public:
		Iterator &operator++() { node = hash_table->next(node); return *this; }
		bool operator==(const Iterator &other) { return other.node == node; }
		bool operator!=(const Iterator &other) { return other.node != node; }
		const Node &operator*() { return *node; }
		const Node *operator->() { return node; }
	};
	Iterator begin();
	Iterator end();
	Iterator insert(K key, V value);
private:
	Iterator find(K key);
};

template <typename V>
unsigned HashTable<V>::hash_function(K str, unsigned hash_constant) {
	unsigned y = 0;
	for (unsigned i = 0; i < str.size(); ++i) {
		y += str[i];
		y *= hash_constant;
	}
	return y % capacity_;
}

template <typename V>
void HashTable<V>::incr_capacity() {
	Node *old = table_;
	capacity_ *= 2;
	table_ = new Node[capacity_];
	size_ = 0;
	for (int i = 0; i < capacity_ / 2; ++i) {
		if (!old[i].is_empty)
			insert(old[i].key, old[i].value);
	}
	delete[] old;
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::insert(K key, V value) {
	Iterator it = find(key);
	if (it != end()) {
		return it;
	}
	if (size_ * 2 >= capacity_)
		incr_capacity();
	K remembered_key = key;
	V remembered_value = value;
	++size_;
	bool *visited = new bool[capacity_];
	memset(visited, false, capacity_);
	//inserting first element
	unsigned hash[2] = { hash_function(remembered_key, hash_constant1_), hash_function(remembered_key, hash_constant2_) };
	for (int i = 0; i < 2; ++i) {
		if (table_[hash[i]].is_empty) {
			table_[hash[i]].key = remembered_key;
			table_[hash[i]].value = remembered_value;
			table_[hash[i]].is_empty = false;
			delete[] visited;
			return Iterator(this, &table_[hash[i]]);
		}
	}
	std::swap(remembered_key, table_[hash[0]].key);
	std::swap(remembered_value, table_[hash[0]].value);
	unsigned remembered_hash = hash[0];

	while (true) {
		unsigned hash_constant;
		if (hash_function(remembered_key, hash_constant1_) == remembered_hash)
			hash_constant = hash_constant2_;
		else
			hash_constant = hash_constant1_;
		unsigned hash_ = hash_function(remembered_key, hash_constant);
		if (table_[hash_].is_empty) {
			table_[hash_].key = remembered_key;
			table_[hash_].value = remembered_value;
			table_[hash_].is_empty = false;
			++size_;
			delete[] visited;
			return Iterator(this, &table_[hash_]);
		}
		if (visited[hash_]) {
			new_constant();
			rehash();
			continue;
		}
		visited[hash_] = true;

		std::swap(remembered_key, table_[hash_].key);
		std::swap(remembered_value, table_[hash_].value);
		remembered_hash = hash_;
	}
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::find(K key) {
	unsigned i = hash_function(key, hash_constant1_);
	if (!table_[i].is_empty && table_[i].key == key) {
		return Iterator(this, &table_[i]);
	} 
	i = hash_function(key, hash_constant2_);
	if (!table_[i].is_empty && table_[i].key == key) {
		return Iterator(this, &table_[i]);
	}
	return end();
}

template <typename V>
void HashTable<V>::new_constant() {
	hash_constant1_ = rand();
	hash_constant2_ = rand();
}

template <typename V>
void HashTable<V>::rehash() {
	Node *old = table_;
	Node *table_ = new Node[capacity_];
	for (int i = 0; i < capacity_; ++i) {
		if (!old[i].is_empty)
			insert(old[i].key, old[i].value);
	}
	delete[] old;
}

template <typename V>
void HashTable<V>::erase(K key) {
	Iterator it = find(key);
	if (it == end())
		return;
	const_cast<bool &>(it->is_empty) = true;
	--size_;
}

template <typename V>
V &HashTable<V>::operator[](K key) {
	Iterator it = find(key);
	if (it == end())
		it = insert(key, V());
	return const_cast<V &>(it->value);
}

template <typename V>
void HashTable<V>::clear() {
	for (int i = 0; i < capacity_; ++i) {
		table_[i].is_empty = true;
	}
	size_ = 0;
}

template <typename V>
typename HashTable<V>::Node *HashTable<V>::next(Node *current) {
	Node *end = table_ + capacity_;
	if (current == end) {
		return end;
	}
	Node *next = current + 1;
	while (next != end && next->is_empty) {
		++next;
	}
	return next;
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::begin() {
	Node *first = &table_[0];
	if (first->is_empty)
		first = next(first);
	return Iterator(this, first);
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::end() {
	return Iterator(this, table_ + capacity_);
}

//template <typename V>
//void HashTable<V>::dump() {
//	for (auto x : *this)
//		cout << x.key << " " << x.value << endl;
//}

#endif