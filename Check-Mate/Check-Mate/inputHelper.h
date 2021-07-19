#include<string>
#include<fstream>
#include "Trie.h"
#pragma once


void trimF(std::string filename);
Trie* loadTrieFromTrim(Trie* root, std::string trimFilename);
Trie* loadTrieFromInput(Trie* root, std::string inFilename);