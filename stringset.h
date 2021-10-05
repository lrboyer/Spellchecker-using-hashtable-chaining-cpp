/*
 * Name: Lucas Boyer
 * Date Submitted: 10-10-21
 * Lab Section: 002
 * Assignment Name: Spell Checker Using a Hash Table
 */

#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
};

int hashString(const string word, const int tSize);