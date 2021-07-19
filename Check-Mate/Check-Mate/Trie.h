#include<string>
#include<unordered_map>
#include "Game.h"
#pragma once
struct Trie {
	bool isLeaf;
	std::unordered_map<std::string, Trie*> children;
	float points;
	int numChildren;

	Trie();
	//Trie(std::string _key);
	float rating();
	Trie* getChild(std::string key);
};

Trie* insert(Trie* root, std::string gameStr, char points);
Trie* insertHelp(Trie* root, std::string& gameStr, char points);

Trie* search(Trie* root, std::string gameStr);	// Searches the entire Trie given the entire word string
Trie* srchOneLvl(Trie* root, std::string key);	// Searches just one level at a time