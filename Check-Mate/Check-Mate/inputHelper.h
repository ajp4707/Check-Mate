#include<string>
#include<fstream>
#include "Trie.h"
#include "RBTree.h"
#pragma once


void trimF(std::string filename);
Trie* loadTrieFromTrim(Trie* root, std::string trimFilename);
//Trie* loadTrieFromInput(Trie* root, std::string inFilename);
RBNode* loadRBFromTrim(RBNode* root, std::string trimFilename);