#include "Trie.h"
#include <iostream>
#pragma once
Trie::Trie() 
{
	points = 0;
	numChildren = 0;
}

/**
 * Calculate rating of a particular point in the game
 *
 * @return score
 */
float Trie::rating() {

	std::cout << "Trie sum: " << points << ". count: " << numChildren << std::endl;
	return points / numChildren;
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

/**
 * Indicates if node is a leaf node
 *
 * @return boolean for if the node is a leaf node
 */
bool Trie::isLeaf() {
	return nextMoves != "";
}

/**
 * Inserts a game into the trie
 *
 * @param root The Trie root node
 * @param key An entire gameString followed by a space
 * @return pointer to root node
 */
Trie* insert(Trie* root, std::string gameStr, char points) {
	int ind = gameStr.find(" ");

	if (ind == std::string::npos) {
		// Do something
		root->points = points;
		return root;
	}

	std::string key = gameStr.substr(0, ind);
	if (root->nextMoves == "" && root->numChildren == 0) {		// Insertng into a brand new node
		root->nextMoves = gameStr;
	}
	else if (root->nextMoves == "") {		// Inserting into a node with branches
		if (root->children.find(key) != root->children.end()) {		// if this key exists
			root->children[key] = insert(root->children[key], gameStr.substr(ind + 1), points);
		}
		else {
			root->children[key] = new Trie();
			root->children[key] = insert(root->children[key], gameStr.substr(ind + 1), points);
		}
	}
	else {		// Inserting into a leaf node
		std::string oldLeaf = root->nextMoves;
		int oldPoints = int(root->points);
		root->nextMoves = "";
		insert(root, oldLeaf, oldPoints);
		insert(root, gameStr, points);
		root->numChildren -= 2;
		root->points -= oldPoints;
	}

	root->numChildren++;
	root->points += points;
	return root;
}

/**
 * Prints preorder traversal of entire Trie
 *
 * Please do not run this function with big datasets
 */
void printTrie(Trie* root, std::string offset) {
	std::cout << offset << root->nextMoves << std::endl;
	offset = offset + "  ";
	std::unordered_map<std::string, Trie*>::iterator iter = root->children.begin();
	for (; iter != root->children.end(); iter++) {
		std::cout << offset << "Key: " << iter->first << std::endl;
		printTrie(iter->second, offset);
	}
}

/**
 * Searches for a single Trie node's child. Not guaranteed to work on Leaf nodes.
 * We need to develop some logic to handle when we encounter a leaf node while searching lvl by 
 * This will be in the Board's logic handler
 * 
 * @param root The Trie root node
 * @param key A single moveString. (e4, Bxe5)
 * @return pointer to child Node, or nullptr if not found
 */
Trie* srchOneLvl(Trie* root, std::string key) {
	if (root->nextMoves.find(key) == 0)
		return root;
	if (root->children.find(key) == root->children.end())
		return nullptr;
	return root->children[key];
}

/**
 * Search for game trie node as described by a string.
 *
 * @param root The Trie root node
 * @param gamestr The complete gameString for the game. (must be followed by a space)
 * @return pointer to Node, or nullptr if not found
 */
Trie* search(Trie* root, std::string gameStr) {

	if (gameStr == root->nextMoves) {
		//std::cout << "Found it! Leaf" << std::endl;
		return root;
	}

	int ind = gameStr.find(" ");

	if (ind == std::string::npos) {
		return root;
	}

	std::string key = gameStr.substr(0, ind);
	std::string rest = gameStr.substr(ind + 1);

	if (root->children.find(key) != root->children.end()) { // if key exists
		//std::cout << key << " Key does exist " << std::endl;
		return search(root->children[key], rest);
	}
	return nullptr;
}


// -------------------- OLD FUNCTIONS TO REWRITE -----------------------------------
/**
 * Inserts a game into the trie
 *
 * @param root The Trie root node
 * @param key An entire gameString followed by a space
 * @return pointer to root node
 */
//	Trie * insert(Trie* root, std::string gameStr, char points) {
//		return insertHelp(root, gameStr, points);
//}

/**
* Helps insert() by passing gamestrings as references
*
* @param root The Trie root node
* @param key An entire gameString followed by a space
* @return pointer to root node
*/
//Trie* insertHelp(Trie* root, std::string &gameStr, char points) {
//	
//	int ind = gameStr.find(" ");
//
//	if (ind == std::string::npos) {
//		// Do something
//		root->isLeaf = true;
//		root->points = points;
//		return root;
//	}
//
//	std::string key = gameStr.substr(0, ind);
//	//std::cout << "Inserting " << key;
//	gameStr = gameStr.substr(ind + 1);
//	if (root->children.find(key) != root->children.end()) {		// if this key exists
//		//std::cout << " Key exists" << std::endl;
//		root->children[key] = insertHelp(root->children[key], gameStr, points);
//	}
//	else {
//		//std::cout << " Need new key" << std::endl;
//		root->children[key] = new Trie();
//		root->children[key] = insertHelp(root->children[key], gameStr, points);
//	}
//	root->numChildren++;
//	root->points += points;
//	return root;
//}

/**
 * Calculate rating of a particular point in the game
 *
 * @return score
 */
//float Trie::rating() {
//	return points / numChildren;
//}


/**
 * Searches for a single Trie node's child
 *
 * @param root The Trie root node
 * @param key A single moveString. (e4, Bxe5)
 * @return pointer to child Node, or nullptr if not found
 */
//Trie* srchOneLvl(Trie* root, std::string key) {
//	if (root->children.find(key) == root->children.end())
//		return nullptr;
//	else return root->children[key];
//}

/**
 * Search and for game trie node as described by a string.
 *
 * @param root The Trie root node
 * @param gamestr The complete gameString for the game. (must be followed by a space)
 * @return pointer to Node, or nullptr if not found
 */
//Trie* search(Trie* root, std::string gameStr) {
//	int ind = gameStr.find(" ");
//
//	if (ind == std::string::npos) {
//		return root;
//	}
//
//	std::string key = gameStr.substr(0, ind);
//	std::string rest = gameStr.substr(ind + 1);
//
//	if (root->children.find(key) != root->children.end()) // if key exists
//		return search(root->children[key], rest);
//	else
//		return nullptr;
//}

