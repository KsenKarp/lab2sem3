#include <iostream>
#include "HashTable.cpp"
#include <string>
#include <cmath>
using namespace std;

const int PRIME_CONST = 31;

int hash_function(int key, int size) {
	return key % size;
}

int hash_string(string key, int size) {
	int hashCode = 0;
	for (int i = 0; i < key.length(); i++) {
		hashCode += key[i] * pow(5, i); //Должно быть PRIME_CONST, но тогда получаются слишком большие числа и вылетает
	}
	return hashCode%size;
}

int main() {
	HashTable<int, int> hash = HashTable<int, int>(6);
	hash.insert(1, 2);
	hash.insert(8, 3);
	hash.insert(3, 4);
	hash.insert(9, 2);
	hash.insert(6, 10);
	hash[8] = 30;
	cout << hash[3] << endl;
	hash.output_all();
	cout << endl;

	HashTable<string, string> phonebook(5);
	string names[5] = { "Dmitriy", "Alyona", "Pavel", "Anya", "Ludmila" };
	string phone_numbers[5] = { "89512813455", "89235114430", "8532604529", "87415352086", "89116654201" };
	for (int i = 0; i < 5; i++) phonebook.insert(names[i], phone_numbers[i]);
	cout << endl;
	phonebook.output();
	cout << endl;

	HashTable<int, string> book_t(5);
	string word = book_t.hash_word_count("file.txt");
	book_t.output();
	cout << endl << endl << "The most popular word in the book is: \"" << word << "\"" <<endl;
	return 0;
}