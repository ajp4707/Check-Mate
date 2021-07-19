#include "Game.h"
#include "Trie.h"
#include "inputHelper.h"
#include <iostream>


int main() {
	////trimF("in201301.pgn");
	//std::string gameStr = "e4 e6 d4 b6 a3 Bb7 ";
	//std::string gameStr2 = "e4 e5 d4 b6 e5 test1 90 ";
	//std::string gameSub = "e4 e5 d4 b6 e5 test1 ";

	//Trie* root = new Trie();
	//insert(root, gameStr, 2);
	//insert(root, gameStr2, 1);
	//
	//std::cout << "Child count " << root->numChildren << std::endl;
	//std::cout << "points " << root->points;
	//std::cout << "rating " << root->rating() << std::endl;

	//std::cout << root->numChildren << std::endl;
	//Trie * child = search(root, gameStr);
	//std::cout << "0 if nullptr " << (child != nullptr) << std::endl;

	//child = search(root, gameSub);
	//std::cout << "0 if nullptr " << (child != nullptr) << std::endl;
	//std::cout << "Numchildren " << child->numChildren << std::endl;

	//Trie* ban = root->children["e4"];
	//std::cout << "0 if nullptr " << (ban != nullptr) << std::endl;
	//std::cout << "Numchildren " << ban->numChildren << std::endl;
	//Trie* nex = ban->children["e5"];
	//std::cout << "0 if nullptr " << (nex != nullptr) << std::endl;
	//std::cout << "Numchildren " << nex->numChildren << std::endl;

	Trie* root = new Trie();
	//trimF("in201301.pgn");
	loadTrieFromTrim(root, "output.txt");

	std::cout << "Num children " << root->numChildren << std::endl;
	Trie* e4 = root->getChild("e4");
	std::cout << "Num children " << e4->numChildren << std::endl;
	// Pseudo code for Trie Initialization.
	// Read in data line by line to create graph
	// Insert graph into trie
	std::string popo;
	std::cin >> popo;
	return 0;
}

