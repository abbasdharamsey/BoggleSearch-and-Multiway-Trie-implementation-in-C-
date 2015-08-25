#include "boggleutil.h"
#include <iostream>
#include <string>
#include <algorithm>

void MWTrie::insert(string word) {
    MWTrieNode* head = this->root;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for (unsigned int i = 0; i < word.length(); i++) {
        // If head (current) node has a child pointer to the next letter in word, set head to it
        if (head->children[word[i] - 'a']) {
            head = head->children[word[i] - 'a'];
        }

        // If head (current) node has no child pointer, create a new node and set head to it
        else {
            head->children[word[i] - 'a'] = new MWTrieNode();
            head = head->children[word[i] - 'a'];
        }   
    }
    
    // Set the isWord value to true
    head->setValidWord();
}

bool MWTrie::find(string word) {
    MWTrieNode* head = this->root;
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    for (unsigned int i = 0; i < word.length(); i++) {
        if ( head->children[word[i] - 'a']) 
            head = head->children[word[i] - 'a'];

        else return false;
    }

    return head->isValidWord();
}

/* 
 * This function is passed in a MWTrieNode pointer, a word, and an index in the word.
 * The index in the word is represented by the pointer to where we are in 
 * the lexicon. 
 */
MWTrieNode* MWTrie::findPointer(MWTrieNode* head, string& word, int index) {
    if (!head) head = this->root;
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    for (unsigned int i = index; i < word.length(); i++) {
        if (head->children[word[i] - 'a']) 
            head = head->children[word[i] - 'a'];

        else return NULL;
    }
    
    return head;
}

void MWTrie::deleteAll(MWTrieNode * head) {
    if (!head)
        return;

    for (auto child : head->children) {
        if (child) {
            deleteAll(child);
        }
    }
    delete head;
    head = NULL;
}

bool MWTrieNode::isValidWord() {
    return this->isWord;
}

void MWTrieNode::setValidWord() {
    this->isWord = true;
}
