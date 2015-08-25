/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  string wordA("a");
  string wordAG("ag");
  string wordLAG("lag");
  string wordBAGEL("bagel");
  string wordSAG("sag");
  string wordSAAGSRR("saagsrr");
  string wordSAGA("SAgapgg");
  string wordDAL("dal");
  string wordX("x");
  lex.insert(wordA);
  lex.insert("z");
  lex.insert("blah");
  lex.insert("bla");
  lex.insert("blh");
  string row0[] = {"D","l","g","A"};
  string row1[] = {"b","A","g","pg"};
  string row2[] = {"S","a","s","w"};
  string row3[] = {"f","r","r","v"};
  string* board[] = {row0,row1,row2,row3};
  set<string> words;
  vector<int> locations;

  p->buildLexicon(lex);

  p->setBoard(4,4,board);

  // if(p->isInLexicon(wordX)) {
  //   std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
  //   return -1;
  // }
  // if(!p->isInLexicon(wordA)) {
  //   std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
  //   return -1;
  // }

  // 3 column tests:
  // if(p->isOnBoard(wordX).size() > 0) {
  //   std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordA);
  // if(locations.size() != 1 || locations[0] != 4) {
  //   std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordAG);
  // if(locations.size() != 2 || locations[0] != 4 || locations[1] != 5) {
  //   std::cerr << "Apparent problem with isOnBoard #3." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordLAG);
  // if(locations.size() != 3 || locations[0] != 2 || locations[1] != 4 || locations[2] != 5) {
  //   std::cerr << "Apparent problem with isOnBoard #4." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordBAGEL);
  // if(locations.size() != 5 || locations[0] != 3 || locations[1] != 4 || locations[2] != 5 || locations[3] != 1 || locations[4] != 2) {
  //   std::cerr << "Apparent problem with isOnBoard #5." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordSAG);
  // if(locations.size() != 3 || locations[0] != 6 || locations[1] != 4 || locations[2] != 5) {
  //   std::cerr << "Apparent problem with isOnBoard #6." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordSAAGSRR);
  // if(locations.size() != 7 || locations[0] != 6 || locations[1] != 4 || locations[2] != 7 || locations[3] != 5 || locations[4] != 8 || locations[5] != 10 || locations[6] != 11) {
  //   std::cerr << "Apparent problem with isOnBoard #7." << std::endl;
  //   return -1;
  // }


  // 4 column tests:
  locations.clear();
  locations = p->isOnBoard(wordSAGA);
  if(locations.size() != 6 || locations[0] != 8 || locations[1] != 5 || locations[2] != 2 || locations[3] != 3 || locations[4] != 7 || locations[5] != 6){
    std::cerr << "Apparent problem with isOnBoard #8." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordDAL);
  if(locations.size() != 3 || locations[0] != 0 || locations[1] != 5 || locations[2] != 1){
    std::cerr << "Apparent problem with isOnBoard #9." << std::endl;
    return -1;
  }
  
  // if(!p->getAllValidWords(0,&words)) {
  //   std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
  //   return -1;
  // };
  // if(words.size() != 1 || words.count(wordA) != 1) {
  //   std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
  //   return -1;
  // }

  delete p;
  return 0;

}
