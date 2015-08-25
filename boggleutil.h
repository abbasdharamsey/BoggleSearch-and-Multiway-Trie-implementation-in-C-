#define NUM_OF_ALPHABET 26
#include <string>
#include <iostream>

using namespace std;

class MWTrieNode {
public:
    bool isValidWord(); /* returns the isWord bool */
    void setValidWord(); /* sets the isWord bool */

    MWTrieNode* children[NUM_OF_ALPHABET];
private:
    bool isWord = false;
};

class MWTrie {
public:
    MWTrie() {
        root = new MWTrieNode();
    }

    ~MWTrie() {
        if (root) {
            deleteAll(root);
        }
        root = NULL;
    }
    
    void deleteAll(MWTrieNode* head); /* Helper method for destructor */
    void insert(string word); // Inserts word into the lexicon
    bool find(string word); // Returns true if word passed in exists in lexicon

    /* used by GAVW/findAllWords to see if the current word exists in the lexicon.
       If it exists, returns the pointer. Else, returns NULL */
    MWTrieNode* findPointer(MWTrieNode* head, string& word, int index);

private:
    MWTrieNode* root;
};
