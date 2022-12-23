#include "HashTable.h"
using namespace std;

template <class V, class K>
HashTable<V, K>::HashTable(int size_) : size(size_), capacity(0) {
	arr = new Node* [size_];
	for (int i = 0; i < size_; i++) arr[i] = new Node();
}

template <class V, class K>
HashTable<V, K>::~HashTable() {
	if (arr) delete[] arr;
}

template <class V, class K>
void HashTable<V, K>::insert(int (*hash_function)(K, int), K key, V item) {
	Node* tmp = new Node(item, key);
	if (capacity + 1 >= size) {
		this->resize((*hash_function)); //увеличит размер + переставит все элементы
	}
	int index = hash_function(key, this->size);
	while (arr[index]->is_used != 0 && arr[index]->key != key) { //второе условие дабы избежать коллизий - линейное зондирование
		index++;
		index = index % size;
	}
	//Нашли индекс для вставки
	if (arr[index]->is_used == false) capacity++;
	arr[index] = tmp;
	return;
}

template <class V, class K>
V HashTable<V, K>::find(int (*hash_function)(K, int), K key) {
	try {
		int index = (*hash_function)(key, this->size);
		V res;
		if (arr[index]->is_used == true) {
			res = arr[index]->value;
			return res;
		}
		else {
			throw(index);
		}	
	}
	catch (int index) {
		cout << "An item with such a key doesn't exist!";
	}
}

template <class V, class K>
V HashTable<V, K>::delete_elem(int (*hash_function)(K, int), K key) {
	int index = hash_function(key, this->size);
	while (arr[index]->key != key) {
		if (index + 1 < size) ++index;
		else index = 0;
	}
	arr[index]->is_deleted = true;
	arr[index]->is_used = false;
	capacity--;
	return arr[index]->value;
}

template <class V, class K>
void HashTable<V, K>::resize(int (*hash_function)(K, int)) {
	Node** new_arr = new Node*[this->size * 2];
	for (int i = 0; i < this->size; i++) {
		int idx = hash_function(arr[i]->key, this->size*2);
		/*new_arr[idx]->value = arr[i]->value;
		new_arr[idx]->key = idx;
		new_arr[idx]->is_used = true;*/
		Node* tmp = new Node(arr[i]->value, arr[i]->key);
		new_arr[idx] = tmp;
	}
	for (int i = this->size; i < size * 2; i++) new_arr[i] = new Node();
	delete[] arr;
	this->size = this->size * 2;
	return;
}