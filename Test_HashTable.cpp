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
			hash.insert(1, 2);
			hash.insert(8, 3);
			hash.insert(3, 4);
			hash.insert(9, 2);
			hash.insert(6, 10);
			assert(hash.find(1) == 2);
			assert(hash.find(8) == 3);
			assert(hash.find(3) == 4);
		}
		TEST_METHOD(KeyExists) {
			HashTable<string, string> phonebook(5);
			string names[5] = { "Dmitriy", "Alyona", "Pavel", "Anya", "Ludmila" };
			string phone_numbers[5] = { "89512813455", "89235114430", "8532604529", "87415352086", "89116654201" };
			for (int i = 0; i < 5; i++) phonebook.insert(names[i], phone_numbers[i]);
			assert(phonebook.key_exists("Anya") == true);
			assert(phonebook.key_exists("Ann") == false);
			assert(phonebook.key_exists("Ludmila") == true);
			assert(phonebook.key_exists("Alyona") == true);
		}
		TEST_METHOD(TestDelete) {
			HashTable<string, string> phonebook(5);
			string names[5] = { "Dmitriy", "Alyona", "Pavel", "Anya", "Ludmila" };
			string phone_numbers[5] = { "89512813455", "89235114430", "8532604529", "87415352086", "89116654201" };
			for (int i = 0; i < 5; i++) phonebook.insert(names[i], phone_numbers[i]);
			assert(phonebook.key_exists("Dmitriy") == true);
			phonebook.delete_elem("Dmitriy");
			assert(phonebook.key_exists("Dmitriy") == false);
			assert(phonebook.get_capacity() == 4);
		}
		TEST_METHOD(TestResize) {
			HashTable<int, int> hash = HashTable<int, int>(3);
			hash.insert(1, 2);
			hash.insert(8, 3);
			hash.insert(3, 4);
			assert(hash.get_size() == 3);
			assert(hash.get_capacity() == 3);
			hash.insert(9, 2);
			assert(hash.get_size() == 6);
			assert(hash.get_capacity() == 4);
		}
		TEST_METHOD(Insert) {
			HashTable<int, int> hash = HashTable<int, int>(5);
			hash.insert(1, 2);
			hash.insert(8, 3);
			hash.insert(3, 4);
			hash.insert(6, 2);
			hash.insert(6, 10);
			assert(hash.find(6) == 2);
		}
		TEST_METHOD(OPERATOR) {
			HashTable<int, int> hash = HashTable<int, int>(5);
			hash.insert(1, 2);
			hash.insert(8, 3);
			hash.insert(3, 4);
			hash.insert(6, 2);
			hash[6] = 20;
			assert(hash.find(6) == 20);
			assert(hash[6] == 20);
			assert(hash[1] == 2);
		}
	};
}
