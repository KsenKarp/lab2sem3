#pragma once
#include <iostream>
#ifndef TABLE
#define TABLE

template <class V, class K>
class HashTable {
public:
	struct Node {
		K key;
		V value;
		bool is_used;
		bool is_deleted;
		Node(const V& val, const K& key_) :key(key_), value(val), is_used(true), is_deleted(false) {};
		Node() : key(K()), value(V()), is_used(false), is_deleted(false) {};
	};
	Node** arr;	  //массивчик  - из указателей на ноды???
	
	//int (*hash_function)(K, int); //int for size
	int capacity; //с учётом deleted
	int size;
	HashTable(int size);
	~HashTable();
	void insert(int (*hash_function)(K, int), K key, V val);
	V find(int (*hash_function)(K, int), K key);
	V delete_elem(int (*hash_function)(K, int), K key);
	void resize(int (*hash_function)(K, int));
};

#endif