#ifndef HASH_TABLE_OPEN_ADDR_
#define HASH_TABLE_OPEN_ADDR_

#include <string>

#define INIT_CAPACITY 4

template <typename V> // consider K - string
class HashTable {
	using K = std::string;
public:
	HashTable(int capacity = INIT_CAPACITY) : capacity_(capacity), size_(0) { table_ = new Node[capacity]; }
	~HashTable() { delete[] table_; }

	int size() { return size_; }
	bool empty() { return size_ == 0; }
	V &operator[](K key);
	void erase(K key);
	void clear();
	void dump();
	bool exist(K key) { return find(key) != end(); }
private:
	friend class Node;
	struct Node {
		friend class HashTable;
		K key;
		V value;
	private:
		Node() : is_deleted(false), is_empty(true) {}
		bool is_deleted;
		bool is_empty;
	};

	unsigned RSHash(char *str, unsigned len);
	void incr_capacity();
	Node *next(Node *current);

	int capacity_;
	int size_;
	Node *table_;

	friend class Iterator;
public:
	class Iterator {
		friend class HashTable;
	private:
		Iterator(HashTable *ht, Node *n) : hash_table(ht), node(n) {}

		HashTable *hash_table;
		Node *node;
	public:
		Iterator(const Iterator &it) : node(it.node) {}
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
unsigned HashTable<V>::RSHash(char *str, unsigned len) {
	unsigned b = 378551;
	unsigned a = 63689;
	unsigned hash = 0;
	unsigned i = 0;

	for (i = 0; i < len; ++str, ++i) {
		hash = hash * a + (unsigned char)(*str);
		a = a * b;
	}
	return hash % capacity_;
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::insert(K key, V value) {
	Iterator it = find(key);
	if (it != end())
		return it;
	if (size_ * 2 >= capacity_)
		incr_capacity();
	unsigned hash = RSHash((char *)key.c_str(), key.size());
	unsigned i = hash;
	while (!table_[i].is_empty) {
		i = (i + 1) % capacity_;
	}
	table_[i].key = key;
	table_[i].value = value;
	table_[i].is_deleted = false;
	table_[i].is_empty = false;
	++size_;
	return Iterator(this, &table_[i]);
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
V &HashTable<V>::operator[](K key) {
	Iterator it = find(key);
	if (it == end()) 
		it = insert(key, V());
	return const_cast<V &>(it->value);
}

template <typename V>
void HashTable<V>::erase(K key) {
	Iterator it = find(key);
	if (it == end())
		return;
	const_cast<bool &>(it->is_empty) = true;
	const_cast<bool &>(it->is_deleted) = true;
	--size_;
}

template <typename V>
typename HashTable<V>::Iterator HashTable<V>::find(K key) {
	unsigned hash = RSHash((char *)key.c_str(), key.size());
	unsigned i = hash;
	while (!table_[i].is_empty || table_[i].is_deleted) {
		if (table_[i].key == key && !table_[i].is_empty) {
			return Iterator(this, &table_[i]);
		}
		i = (i + 1) % capacity_;
		if (i == hash) {
			return end();
		}
	}
	return end();
}

template <typename V>
void HashTable<V>::clear() {
	for (int i = 0; i < capacity_; ++i) {
		table_[i].is_deleted = false;
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

template <typename V>
void HashTable<V>::dump() {
	for (auto x : *this)
		cout << x.key << " " << x.value << endl;
}

#endif
