#pragma once
#include <iostream>
#include <string>
#ifndef TABLE
#define TABLE

template <class V, class K>
class HashTable {
private:
	struct Node {
		K key;
		V value;
		bool is_used;
		bool is_deleted;
		Node(const V& val, const K& key_) :key(key_), value(val), is_used(true), is_deleted(false) {};
		Node() : key(K()), value(V()), is_used(false), is_deleted(false) {};
	};
	Node** arr;	//массивчик  - из указателей на ноды
	int capacity; //с учётом deleted
	int size;
	void resize(int (*hash_function)(K, int));
	void resize(int (*hash_function)(K, int), int new_size);

public:
	HashTable(int size);
	~HashTable();
	void insert(int (*hash_function)(K, int), K key, V val);
	const V& find(int (*hash_function)(K, int), K key);
	const V& delete_elem(int (*hash_function)(K, int), K key);
	int get_size() const;
	int get_capacity() const;
	void output_all();
	void output();
	bool key_exists(int (*hash_function)(K, int), K key);

	K hash_word_count(const char* filename, int (*hash_function)(K, int));
};

#endif