#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include "boggleplayer.h"

using namespace std;

void BogglePlayer::buildLexicon(const set<string>& word_list) {
    if (lexicon) {
        delete lexicon;
        lexicon = NULL;
    }

    lexicon = new MWTrie();

    for (string head : word_list) {
        lexicon->insert(head);
    }

}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
    numOfCharactersOnBoard = 0;

    if(boardSet) {
        boggleBoard.clear();
    }

    for (unsigned int i = 0; i < rows; i++) {
        vector<string> currRow;
        for (unsigned int j = 0; j < cols; j++) {
            string data = diceArray[i][j];
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            currRow.push_back(data);
            numOfCharactersOnBoard += diceArray[i][j].length();
        }

        boggleBoard.push_back(currRow);
    }

    this->rows = rows;
    this->cols = cols;
    boardSet = true;
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
    // Error checks
    if (!lexicon || !boardSet) 
        return false;

    vector<vector<int>> visited;
    visited.resize(rows, vector<int>(cols, 0));

    /* loop through the entire board */
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // The string which will be concatenatinated to find words
            string word = boggleBoard[i][j];

            MWTrieNode* head = lexicon->findPointer(NULL, word, 0);
             // If the characters on the die (i,j) exist in the lexicon, call findAllWords
            if (!head)
                continue;

            /* Passing in to findAllWords: 
             *     the minimum_word_legnth,
             *     the board row and column we are currently on,
             *     the visited vector
             *     the set words which contain all valid (words in the lexicon) found on the board
             *     a pointer to where the characters in the string are stored in the lexicon, 
             *     the index of where to append the next character(s),
             *     and the current concatinated string that will be checked to see if it is a word 
            */
            findAllWords(minimum_word_length, i, j, visited, words, head, boggleBoard[i][j].length(), word);

            // Unvisit the current board (i, j) and move on to the next one
            visited[i][j]--;
        }
    }

    return true;
}

void BogglePlayer::findAllWords(unsigned int minimum_word_length, int coordinateRow, int coordinateCol, vector<vector<int>> &visited,
                                set<string>* words, MWTrieNode * head, int index, string word) {
    string currWord = word;
    visited[coordinateRow][coordinateCol]++;

    if (currWord.length() >= minimum_word_length && head->isValidWord()) {
        words->insert(currWord);
    }

    // Loop through the surrounding dice
    for (int i = coordinateRow - 1; i <= coordinateRow + 1; i++) {
        if (i < 0 || i >= rows) continue;
        for (int j = coordinateCol - 1; j <= coordinateCol + 1; j++) {
            if (j < 0 || j >= cols) continue; 
            if (visited[i][j]) continue;

            unsigned int currIndex = currWord.length();
            currWord += boggleBoard[i][j];

            MWTrieNode * currNode = lexicon->findPointer(head, currWord, currIndex);
            if (!currNode) {
                currWord = currWord.substr(0, currIndex);
                continue;
            }

            findAllWords(minimum_word_length, i, j, visited, words, currNode, currWord.length(), currWord);
            visited[i][j]--;
            currWord = currWord.substr(0, currIndex);
        }
    }
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
    if(!lexicon) return false;
    return lexicon->find(word_to_check);
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check) {
    numOfCharactersFound = 0;
    vector<int> path;
    vector<vector<int>> visited;
    visited.resize(rows, vector<int>(cols, 0));

    if (!boardSet || word_to_check.size() > numOfCharactersOnBoard) return path;

    string wordToCheck = word_to_check;
    transform(wordToCheck.begin(), wordToCheck.end(), wordToCheck.begin(), ::tolower);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            numOfCharactersFound = 0;   

            //If the current dice's character(s) is at least in the beginning of word_to_check,
            if (!boggleBoard[i][j].compare(wordToCheck.substr(0, boggleBoard[i][j].length()))) {
                
                /* Passing in to findWord: 
                 *      the word to look for 
                 *      the index of where we are in the word
                 *      the current dice we are at (i, j)
                 *      the path vector, and the visited vector
                 */
                bool found = findWord(wordToCheck, boggleBoard[i][j].length(), i, j, path, visited);

                if (found) {
                    visited[i][j]--;
                    return path;
                }  
            }
        }
    }
    return path;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {

}

bool BogglePlayer::findWord(const string& word_to_check, int indexInWord, int coordinateRow, int coordinateCol, vector<int>& path, 
                            vector<vector<int>> &visited) {
    bool findWordRet = false;

    path.push_back(coordinateRow*cols + coordinateCol);
    numOfCharactersFound += boggleBoard[coordinateRow][coordinateCol].length();

    visited[coordinateRow][coordinateCol]++;

    if (word_to_check.length() == numOfCharactersFound) return true;

    // loop through the surrounding dice
    for (int i = coordinateRow - 1; i <= coordinateRow + 1; i++) {
        if (i < 0 || i >= rows) continue;
        for (int j = coordinateCol - 1; j <= coordinateCol + 1; j++) {
            if (j < 0 || j >= cols) continue; 
            if (visited[i][j]) continue;

            unsigned int diceStringLength = boggleBoard[i][j].length();

            // If the die on the board matches the word at the index, pass it in recursively
            if (!boggleBoard[i][j].compare(word_to_check.substr(indexInWord, diceStringLength))) { 
                findWordRet = findWord(word_to_check, indexInWord + diceStringLength, i, j, path, visited);

                if (!findWordRet) {
                    visited[i][j]--;
                    numOfCharactersFound -= boggleBoard[i][j].length();
                    continue;
                }

                return findWordRet;
            }
        }
    }

    if(!findWordRet) path.pop_back();
    return findWordRet;
}
