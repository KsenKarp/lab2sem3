#include <iostream>
#include "HashTable.cpp"
using namespace std;

int hash_function(int key, int size) {
	return key % size;
}

int main() {
	HashTable<int, int> hash = HashTable<int, int>(2);
	hash.insert((*hash_function), 1, 2);
	//cout << hash.find((*hash_function), 1) << endl;
	hash.delete_elem((*hash_function), 1);
	hash.insert((*hash_function), 0, 3);
	//cout << hash.find((*hash_function), 1) << endl;
	hash.insert((*hash_function), 3, 4);
	return 0;
}