#include "Game.h"
#include "Trie.h"
#include "inputHelper.h"
#include <iostream>
#include "RBTree.h"
#include <map>
#include "Board.h"

struct GUI {

	ChessBoard cb;
	std::map<std::string, sf::Texture> texMap;
	sf::Sprite* pieceSprites[8][8];

	GUI() {
		cb = ChessBoard();
		texMap = setUpTextureMap();
		initSprites();
	}

	void runGUI() {
		sf::RenderWindow window(sf::VideoMode(800, 512), "Check-Mate");
		sf::Texture checker;
		checker.loadFromFile("icons/empty-chessboard.png");
		//checker.loadFromFile("icons/wBish.png");
		sf::Sprite background(checker);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(background);
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (cb.squares[i][j] != nullptr)
						window.draw(*pieceSprites[i][j]);
			window.display();
		}
	}

	std::map<std::string, sf::Texture> setUpTextureMap()
	{
		std::vector<std::string> filelist = { "bPawn", "bKnight", "bBish", "bRook", "bQueen", "bKing", "wPawn", "wKnight", "wBish", "wRook", "wQueen", "wKing" };
		std::map<std::string, sf::Texture> textureMap;
		for (int i = 0; i < filelist.size(); i++)
		{
			sf::Texture temp;
			std::string filename = "icons/" + filelist[i] + ".png";
			std::cout << filename << std::endl;
			temp.loadFromFile(filename);
			textureMap.emplace(filelist[i], temp);
		}
		return textureMap;
	}
	void updateSpriteLocations() {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (pieceSprites[i][j] != nullptr)
					pieceSprites[i][j]->setPosition(sf::Vector2f(i * 64, j * 64));
	}
	void initSprites() {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				if (cb.squares[i][j] == nullptr)
					pieceSprites[i][j] = nullptr;
				else {
					Piece* p = cb.squares[i][j];

					if (p->getSymbol() == 'p') {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wPawn"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bPawn"]);
					}
					else if (p->getSymbol() == 'N') {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wKnight"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bKnight"]);
					}
					else if (p->getSymbol() == 'R') {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wRook"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bRook"]);
					}
					else if (p->getSymbol() == 'B') {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wBish"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bBish"]);
					}
					else if (p->getSymbol() == 'Q') {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wQueen"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bQueen"]);
					}
					else {
						if (p->colour == Colour::White)
							pieceSprites[i][j] = new sf::Sprite(texMap["wKing"]);
						else
							pieceSprites[i][j] = new sf::Sprite(texMap["bKing"]);
					}
				}
			}
		updateSpriteLocations();
	}

};


int main() {
	Trie* root = new Trie();
	////trimF("in201301.pgn");
	//loadTrieFromTrim(root, "output.txt");

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

	//RBNode* RB = nullptr;
	//RB = loadRBFromTrim(RB, "output.txt");
	//std::string popo;
	//std::cin >> popo;


	//std::cout << "Trie e4 rating: " << aa->rating() << std::endl;
	//std::cout << "RB e4 rating: " << rating(RB, "e4 e5 Nf3 Nc6 Bc4 Nf6 ") << std::endl;

	//graphics();

	GUI gui;
	gui.runGUI();


	//std::cout << "total games " << count(RB);
	// Pseudo code for Trie Initialization.
	// Read in data line by line to create graph
	// Insert graph into trie

	return 0;
}

