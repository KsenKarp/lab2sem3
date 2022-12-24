#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>
#include "..\lab2sem3\HashTable.cpp"
#include <string>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

int hash_function(int key, int size) {
	return key % size;
}

int hash_string(string key, int size) {
	int hashCode = 0;
	for (int i = 0; i < key.length(); i++) {
		hashCode += key[i] * pow(5, i);
	}
	return hashCode % size;
}

namespace TestHashTable
{
	TEST_CLASS(TestHashTable)
	{
	public:
		
		TEST_METHOD(TestConstructors)
		{
			HashTable<int, int> hash = HashTable<int, int>(5);
			hash.insert((*hash_function), 1, 2);
			hash.insert((*hash_function), 8, 3);
			hash.insert((*hash_function), 3, 4);
			hash.insert((*hash_function), 9, 2);
			hash.insert((*hash_function), 6, 10);
			assert(hash.find(1) == 2);
			assert(hash.find(8) == 3);
			assert(hash.find(3) == 4);
		}
		TEST_METHOD(KeyExists) {
			HashTable<string, string> phonebook(5);
			string names[5] = { "Dmitriy", "Alyona", "Pavel", "Anya", "Ludmila" };
			string phone_numbers[5] = { "89512813455", "89235114430", "8532604529", "87415352086", "89116654201" };
			for (int i = 0; i < 5; i++) phonebook.insert((*hash_string), names[i], phone_numbers[i]);
			assert(phonebook.key_exists((*hash_string), "Anya") == true);
			assert(phonebook.key_exists((*hash_string), "Ann") == false);
			assert(phonebook.key_exists((*hash_string), "Ludmila") == true);
			assert(phonebook.key_exists((*hash_string), "Alyona") == true);
		}
		TEST_METHOD(TestDelete) {
			HashTable<string, string> phonebook(5);
			string names[5] = { "Dmitriy", "Alyona", "Pavel", "Anya", "Ludmila" };
			string phone_numbers[5] = { "89512813455", "89235114430", "8532604529", "87415352086", "89116654201" };
			for (int i = 0; i < 5; i++) phonebook.insert((*hash_string), names[i], phone_numbers[i]);
			assert(phonebook.key_exists((*hash_string), "Dmitriy") == true);
			phonebook.delete_elem((*hash_string), "Dmitriy");
			assert(phonebook.key_exists((*hash_string), "Dmitriy") == false);
			assert(phonebook.get_capacity() == 4);
		}
		TEST_METHOD(TestResize) {
			HashTable<int, int> hash = HashTable<int, int>(3);
			hash.insert((*hash_function), 1, 2);
			hash.insert((*hash_function), 8, 3);
			hash.insert((*hash_function), 3, 4);
			assert(hash.get_size() == 3);
			assert(hash.get_capacity() == 3);
			hash.insert((*hash_function), 9, 2);
			assert(hash.get_size() == 6);
			assert(hash.get_capacity() == 4);
		}
		TEST_METHOD(Insert) {
			HashTable<int, int> hash = HashTable<int, int>(5);
			hash.insert((*hash_function), 1, 2);
			hash.insert((*hash_function), 8, 3);
			hash.insert((*hash_function), 3, 4);
			hash.insert((*hash_function), 6, 2);
			hash.insert((*hash_function), 6, 10);
			assert(hash.find((*hash_function), 6) == 2);
		}
	};
}
