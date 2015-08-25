#include "baseboggleplayer.h"
#include "boggleutil.h"

using namespace std;

class BogglePlayer: public BaseBogglePlayer {
  public:
    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word_to_check);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
    ~BogglePlayer() {
        delete lexicon;
        lexicon = NULL;
    }

  private: 
    vector<vector<string>> boggleBoard;
    bool boardSet = false;
    int rows; 
    int cols;
    unsigned int numOfCharactersOnBoard = 0; 
    
    /* Used by isOnBoard/findWord to see if the number of characters visited equals the number of 
     * characters in the word_to_check */
    unsigned int numOfCharactersFound = 0;


    /* This is a helper method used by isOnBoard which recursively visits surrounding nodes
     * that haven't been visited and contain the correct letters in the word_to_check. It
     * returns true if the word is found, false if it is not.
     */
    bool findWord(const string& word_to_check, int indexInWord, int coordinateRow, int coordinateCol, vector<int>& path,
                  vector<vector<int>> &visited);

    /* This is a helper method used by getAllValidWords which recursively visits surrounding
     * nodes, checks if the concatination of the node passed in GAVW and what it visits
     * on the board is in the lexicon, if it is it passes in that concatination recursively. 
     */
    void findAllWords(unsigned int minimum_word_length, int coordinateRow, int coordinateCol, vector<vector<int>> &visited,
                      set<string>* words, MWTrieNode* head, int index, string data);

    /* The multi-way trie data structure */
    MWTrie* lexicon;
};
