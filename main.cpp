/*
* Name: Lucas Boyer
* Date Submitted: 10-5-21
* Lab Section: 002
* Assignment Name: Spell Checker Using a Hash Table
*/

#include "stringset.h"

void testStringset(Stringset& words);
void loadStringset(Stringset& words, string filename);
vector<string> spellcheck(const Stringset& words, string word);
bool dup(const vector<string>& matches, string newOne);

//Helper function I made to make sure I don't add duplicates when making
//the spellchecker list suggestions
//if the new string is already in list then return true
bool dup(const vector<string>& matches, string newOne) {
    for (auto itr : matches) {
        if (newOne == itr)
            return true;
    }
    return false;
}

int main()
{
    Stringset wordlist;
    testStringset(wordlist);
    return 0;
}

//useful functions for testing whether stringset works
void testStringset(Stringset& words)
{
    string choice;
    string word;
    do
    {
        cout << "I: insert word" << endl;
        cout << "E: load stringset from file" << endl;
        cout << "C: spellcheck word" << endl;
        cout << "F: find word" << endl;
        cout << "R: remove word" << endl;
        cout << "P: print words in stringset" << endl;
        cout << "Q: quit" << endl;
        cin >> choice;
        switch (choice[0])
        {
            case 'I':
            case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
            case 'E': //added to help test adding from file
            case 'e':
                cout << "Enter filename: ";
                cin >> word;
                loadStringset(words, word);
                break;
            case 'C': //added to help test spellchecking
            case 'c': {
                cout << "Enter word to spellcheck: ";
                cin >> word;
                vector<string> suggestions = spellcheck(words, word);
                for (auto itr : suggestions) {
                    cout << itr << endl;
                }
                break;
            }
            case 'F':
            case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
            case 'R':
            case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
            case 'P':
            case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
        }
    } while (choice[0] != 'Q' && choice[0] != 'q');
}

//this opens from filename and inserts the words into the table
void loadStringset(Stringset& words, string filename)
{
    ifstream infile(filename); 
    string word;
    while(getline(infile, word)) {
        words.insert(word);
    }
}

//this makes a new vector to add all the matching words then adds them and returns
vector<string> spellcheck(const Stringset& words, string word)
{
    auto table = words.getTable(); //so i can iterate through words
    vector<string> match;

    for (int i = 0; i < words.getSize(); i++) { //iterates through vector
        for (auto const iter : table[i]) { //iter through each linked list
            //this increases efficiency by cutting down the num of searches by checking word size and
            // that it starts with the same first or second letter
            if (word.size() == iter.size() && (iter[0] == word[0] || iter[1] == word[1])) {
                //these two loops generate potential suggestion words by
                //slicing the word at each point and replacing it with
                //every letter in the alphabet to generate all pos. words
                for (long unsigned int i = 0; i < word.size(); i++) {
                    string sliceL = word.substr(0,i);
                    string sliceR = word.substr(i+1, word.length());
                    for (char c = 97; c < 123; c++) {
                        string suggestionWord = sliceL + c + sliceR;
                        //if not the same word as inputed and not a duplicate and found in the table
                        //add to spellcheck
                        if (word != suggestionWord && !dup(match, suggestionWord) && words.find(suggestionWord))
                            match.push_back(suggestionWord);
                    }
                }
            }
        }
    }
    return match;
}