#include<string>
#include<unordered_map>
#include "Game.h"
#pragma once
struct Trie {
	std::unordered_map<std::string, Trie*> children;
	float points;
	int numChildren;
	std::string nextMoves;

	Trie();
	//Trie(std::string _key);
	float rating();
	Trie* getChild(std::string key);
	bool isLeaf();
};

Trie* insert(Trie* root, std::string gameStr, char points);
void printTrie(Trie* root, std::string offset = "");

Trie* search(Trie* root, std::string gameStr);	// Searches the entire Trie given the entire word string
Trie* srchOneLvl(Trie* root, std::string key);	// Searches just one level at a time