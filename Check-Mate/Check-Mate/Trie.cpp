#include "Trie.h"
#include <iostream>
#pragma once
Trie::Trie() 
{
	isLeaf = false;
	points = 0;
	numChildren = 0;
}

/**
 * Inserts a game into the trie
 *
 * @param root The Trie root node
 * @param key An entire gameString followed by a space
 * @return pointer to root node
 */
	Trie * insert(Trie* root, std::string gameStr, char points) {
		return insertHelp(root, gameStr, points);
}

/**
* Helps insert() by passing gamestrings as references
*
* @param root The Trie root node
* @param key An entire gameString followed by a space
* @return pointer to root node
*/
Trie* insertHelp(Trie* root, std::string &gameStr, char points) {
	
	int ind = gameStr.find(" ");

	if (ind == std::string::npos) {
		// Do something
		root->isLeaf = true;
		root->points = points;
		return root;
	}

	std::string key = gameStr.substr(0, ind);
	//std::cout << "Inserting " << key;
	gameStr = gameStr.substr(ind + 1);
	if (root->children.find(key) != root->children.end()) {		// if this key exists
		//std::cout << " Key exists" << std::endl;
		root->children[key] = insertHelp(root->children[key], gameStr, points);
	}
	else {
		//std::cout << " Need new key" << std::endl;
		root->children[key] = new Trie();
		root->children[key] = insertHelp(root->children[key], gameStr, points);
	}
	root->numChildren++;
	root->points += points;
	return root;
}

/**
 * Calculate rating of a particular point in the game
 *
 * @return score
 */
float Trie::rating() {
	return points / numChildren;
}

/**
 * Searches for a single Trie node's child
 *
 * @param root The Trie root node
 * @param key A single moveString. (e4, Bxe5)
 * @return pointer to child Node, or nullptr if not found
 */
Trie* srchOneLvl(Trie* root, std::string key) {
	if (root->children.find(key) == root->children.end())
		return nullptr;
	else return root->children[key];
}

/**
 * Search and for game trie node as described by a string.
 *
 * @param root The Trie root node
 * @param gamestr The complete gameString for the game. (must be followed by a space)
 * @return pointer to Node, or nullptr if not found
 */
Trie* search(Trie* root, std::string gameStr) {
	int ind = gameStr.find(" ");

	if (ind == std::string::npos) {
		return root;
	}

	std::string key = gameStr.substr(0, ind);
	std::string rest = gameStr.substr(ind + 1);

	if (root->children.find(key) != root->children.end()) // if key exists
		return search(root->children[key], rest);
	else
		return nullptr;
}

/**
 * Get a child of a trie node
 *
 * @param key The key of the child you want to find. A single moveString
 * @return pointer to Node, or nullptr if not found
 */
Trie* Trie::getChild(std::string key) {
	if (children.find(key) == children.end())
		return nullptr;
	else
		return children[key];
}