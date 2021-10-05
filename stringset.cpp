/*
 * Name: Lucas Boyer
 * Date Submitted: 10-10-21
 * Lab Section: 002
 * Assignment Name: Spell Checker Using a Hash Table
 */

#include "stringset.h"
#include <algorithm>
using namespace std;

//helper function that takes in word and length of vector table
//hashes the word mod size of vector and returns its position to be inserted
int hashString(const string word, const int tSize) {
    hash<string> stringHash;
    int hashed = stringHash(word) % tSize;
    return hashed;
}

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

//inserts string into list after hashing it
//if num_elems equals size it increases the size of the vector by size * 2
void Stringset::insert(string word)
{
    hash<string> stringHash;

    //if old table is full, make new one and rehash data
    if (num_elems == size) {
        size *= 2;
        vector<list<string>> temp(size); //makes temp table
        for (int i = 0; i < size / 2; i++) {
            for (auto itr : table[i]) {
                int hashed = stringHash(itr) % size; //rehashes everything in old table
                temp[hashed].push_back(itr); //adds it to temp table
            }
        }
        table.clear(); //clears old table
        table = temp; //puts temp in table
        temp.clear(); //clears temp
    }

    int hashed = hashString(word, size);

    //if not already in list add it
    if (!find(word)) {
        table[hashed].push_front(word);
        num_elems++;
    }
}

//This function will return a Boolean Will return true if the word is in the list, otherwise it will return false
//searches list by using hash function
bool Stringset::find(string word) const {
    int hashed = hashString(word, size);

    for (auto iter : table[hashed]) {
        if (iter == word) {
            return true;
        }
    }
    return false;
}

//removes word if in list
//uses hash function to find
void Stringset::remove(string word)
{
    int hashed = hashString(word, size);
    if(find(word)) {
        for (auto iter : table[hashed]) {
            if (iter == word) {
                table[hashed].remove(iter);
                num_elems--;
                break;
            }
        }
    }
}