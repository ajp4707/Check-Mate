#include<string>
#include<unordered_map>
#include "Game.h"
#pragma once
struct Trie {
	bool leaf;
	std::string key;
	std::unordered_map<std::string, Trie*> children;
	int points;

	Trie();
	Trie(std::string _key);
	float rating();
};

void insert(Trie * root, Game g);
// insert the game properly
// increment score of all nodes passed.

Trie* search(Trie* root, std::string);	// Searches the entire Trie given the entire word string
Trie* srchOneLvl(Trie* root, std::string);	// Searches just one level at a time