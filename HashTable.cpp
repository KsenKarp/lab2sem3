#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
int HashTable<V, K>::hash_function(K key, int size) {
	stringstream ss;
	ss << key;
	string str = ss.str();
	int hashCode = 0;
	for (int i = 0; i < str.length(); i++) {
		hashCode += str[i] * pow(5, i);
	}
	return hashCode % size;
}

template <class V, class K>
void HashTable<V, K>::insert(K key, V item) {
	try {
		Node* tmp = new Node(item, key);
		bool exists = key_exists(key);
		if (exists == true) {
			throw(exists);
			return;
		}
		if (capacity + 1 > size) {
			this->resize(); //увеличит размер + переставит все элементы
		}
		int index = this->hash_function(key, this->size);
		while (arr[index]->is_used != 0 && arr[index]->key != key) { //второе условие дабы избежать коллизий - линейное зондирование
			index++;
			index = index % size;
		}
		//Нашли индекс для вставки
		capacity++;
		arr[index] = tmp;
		return;
	}
	catch (bool exists) {
		if (exists == true) cout << "An item with similar key already exists, please, chage the key" << endl;
	}
}

template <class V, class K>
const V& HashTable<V, K>::find(K key) {
	try {
		int index = this->hash_function(key, this->size);
		int beg_index = index;
		while (arr[index]->key != key) {
			index++;
			index = index % size;
			if (index == beg_index) throw (index);
		}
		return arr[index]->value;
	}
	catch (int idx) {
		cout << "An item with such a key doesn't exist!";
		return NULL;
	}
}

template <class V, class K>
const V& HashTable<V, K>::delete_elem(K key) {
	try {
		int index = this->hash_function(key, this->size);
		int beg_index = index;
		while (arr[index]->key != key) {
			index++;
			index = index % size;
			if (index == beg_index) throw (key);
		}
		arr[index]->is_deleted = true;
		arr[index]->is_used = false;
		capacity--;
		return arr[index]->value;
	}
	catch (K key) {
		cout << "An item with index " << key << " doesn't exist ";
	}
}

template <class V, class K>
void HashTable<V, K>::resize() {
	Node** new_arr = new Node*[this->size * 2];
	for (int i = 0; i < size * 2; i++) new_arr[i] = new Node();
	for (int i = 0; i < this->size; i++) {
		int idx = this->hash_function(arr[i]->key, this->size*2);
		while (new_arr[idx]->is_used != 0 && new_arr[idx]->key != arr[i]->key) {
			idx++;
			idx = idx % (size*2);
		}
		Node* tmp = new Node(arr[i]->value, arr[i]->key);
		new_arr[idx] = tmp;
	}
	delete[] arr;
	arr = new_arr;
	this->size = this->size * 2;
	return;
}

template <class V, class K>
void HashTable<V, K>::resize(int new_size) {
	Node** new_arr = new Node * [new_size];
	for (int i = 0; i < new_size; i++) new_arr[i] = new Node();
	for (int i = 0; i < this->size; i++) {
		int idx = this->hash_function(arr[i]->key, new_size);
		while (new_arr[idx]->is_used != 0 && new_arr[idx]->key != arr[i]->key) {
			idx++;
			idx = idx % (new_size);
		}
		Node* tmp = new Node(arr[i]->value, arr[i]->key);
		new_arr[idx] = tmp;
	}
	delete[] arr;
	arr = new_arr;
	this->size = new_size;
	return;
}

template <class V, class K>
int HashTable<V, K>::get_size() const {
	return this->size;
}

template <class V, class K>
int HashTable<V, K>::get_capacity() const {
	return this->capacity;
}

template <class V, class K>
void HashTable<V, K>::output_all() {
	cout << "key->value content of a hash_table" << endl;
	for (int i = 0; i < size; i++) cout << arr[i]->key << "  -  " << arr[i]->value << endl;
	return;
}

template <class V, class K>
void HashTable<V, K>::output() {
	cout << "key->value content of a hash_table" << endl;
	for (int i = 0; i < size; i++) {
		if (arr[i]->is_used)
			cout << arr[i]->key << "  -  " << arr[i]->value << endl;
	}
	return;
}

template <class V, class K>
bool HashTable<V, K>::key_exists(K key_) {
	int index = this->hash_function(key_, this->size);
	int beg_index = index;
	while (arr[index]->key != key_) {
		index++;
		index = index % size;
		if (index == beg_index) return false;
	}
	if (arr[index]->is_used == true) return true;
	else return false;
}

template <class V, class K>
V& HashTable<V, K>::operator[] (K key) {
	int index = this->hash_function(key, this->size);
	int beg_index = index;
	try {	
		while (arr[index]->key != key) {
			index++;
			index = index % size;
			if (index == beg_index) throw(index);
		}
		return arr[index]->value;
	}
	catch (int index) {
		cout << "The key " << key << " doesn't exist";
	}
}

template <class V, class K>
K HashTable<V, K>::hash_word_count(const char* filename) {  //Вроде как даже O(n) с хорошей хэш-функцией
	ifstream book(filename);
	int booksize = 0;
	char tabula[] = { '.' , ',' , '?' , '!' , ';' , ':' , ')' };
	if (this->size < booksize) this->resize(booksize);
	while(!book.eof()) {
		string line;
		string str;
		std::getline(book, line);
		std::istringstream ss(line);
		while (std::getline(ss, str, ' ')) { //А хотя не, не O(n) :(  Но в целом, если абзацы >> их количества...
			booksize++;
			if (str.back() == tabula[0] || str.back() == tabula[1] || str.back() == tabula[2] ||
				str.back() == tabula[3] || str.back() == tabula[4] || str.back() == tabula[5] ||
				str.back() == tabula[6] || str.back() == tabula[7]) str.pop_back();
			if (key_exists(str) == false) {
				insert(str, 1);
			}
			else {
				int index = hash_function(str, booksize);
				while (arr[index]->key != str) {
					index++;
					index = index % size;
				}
				arr[index]->value++;
			}
		}
	}
	int most_pop_freq = arr[0]->value;
	int idx_most_pop = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i]->is_used) {
			if (arr[i]->value > most_pop_freq) {
				most_pop_freq = arr[i]->value;
				idx_most_pop = i;
			}
		}
	}
	book.close();
	return arr[idx_most_pop]->key;
}