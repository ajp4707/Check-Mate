#include "Game.h"
#include "Trie.h"
#include "inputHelper.h"
#include <iostream>
#include "RBTree.h"


int main() {
	Trie* root = new Trie();
	////trimF("in201301.pgn");
	loadTrieFromTrim(root, "output.txt");

	//std::string a = "a b c d e f g a a a ";
	//std::string b = "b b c d e f ";
	//std::string c = "a d g e f l ";
	//std::string d = "a d g r ";
	//std::string e = "c b e ";
	//std::string f = "d4 Nf6 c4 g6 Nc3 d5 Qb3 Bg7 cxd5 O-O e4 c6 dxc6 Nxc6 d5 Nd4 Qd1 Nd7 Be3 e5 dxe6 Nxe6 Nf3 Ndc5 Be2 Bxc3+ bxc3 Nxe4 Qc2 Ne4c5 O-O Qa5 Bh6 Rd8 Rfd1 b6 Rxd8+ Nxd8 Qe4 Nde6 Qxa8 ";
	////insert(root, a, 2);
	////std::cout << "NumChild: " << root->numChildren << ", moveStr: " << root->nextMoves << std::endl;

	////insert(root, b, 2);
	////insert(root, c, 2);
	////insert(root, d, 2);
	////insert(root, e, 2);

	////printTrie(root);
	//std::cout << "NumChild: " << root->numChildren << ", moveStr: " << root->nextMoves << std::endl;
	//std::cout << "Trie rating e4 = " << root->rating() << std::endl;
	Trie* aa = search(root, "e4 e5 Nf3 Nc6 Bc4 Nf6 ");

	//auto game = search(root, f);
	//std::cout << "0 if nullptr: " << (game != nullptr) << std::endl;
	////game = search(root, "a b ");
	//std::cout << "0 if nullptr: " << (game != nullptr) << std::endl;

	RBNode* RB = nullptr;
	RB = loadRBFromTrim(RB, "output.txt");
	std::string popo;
	std::cin >> popo;


	std::cout << "Trie e4 rating: " << aa->rating() << std::endl;
	std::cout << "RB e4 rating: " << rating(RB, "e4 e5 Nf3 Nc6 Bc4 Nf6 ") << std::endl;

	//std::cout << "total games " << count(RB);
	// Pseudo code for Trie Initialization.
	// Read in data line by line to create graph
	// Insert graph into trie

	return 0;
}

