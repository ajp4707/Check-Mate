#include <chrono>
#include <queue>
#include<string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "Trie.h"
#include "inputHelper.h"
#include "RBTree.h"
#include "Board.h"

#pragma once
using namespace std::chrono;

enum class Result {Running, WhiteWin, BlackWin, Draw};

struct Database {
	Trie* rootTrie;
	RBNode* rootRB;
	long timeLoadTrie;
	long timeLoadRB;
	long timeRatingTrie;
	long timeRatingRB;
	int children;

	Database() {
		rootTrie = new Trie();
		rootRB = nullptr;
		timeRatingTrie = timeRatingRB = timeLoadTrie = timeLoadRB = 0;
		children = 0;
	}

	void loadFromFile(std::string trimFilename) {
		auto start = high_resolution_clock::now();
		rootTrie = loadTrieFromTrim(rootTrie, trimFilename);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		timeLoadTrie = duration.count();

		start = high_resolution_clock::now();
		rootRB = loadRBFromTrim(rootRB, trimFilename);
		stop = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(stop - start);
		timeLoadRB = duration.count();
	}
	float ratingTrie(std::string gameStr) {
		auto start = high_resolution_clock::now();
		Trie* tempTrie = search(rootTrie, gameStr);
		float res;
		if (tempTrie) {
			res = tempTrie->rating();
			children = tempTrie->numChildren;
		}
		else {
			res = 1;
			children = 0;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		timeRatingTrie = duration.count();
		
		return res;
	}
	float ratingRB(std::string gameStr) {
		auto start = high_resolution_clock::now();
		float res = rating(rootRB, gameStr);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		timeRatingRB = duration.count();

		return res;
	}
	std::vector<std::pair<std::string, float>> bestMoves(std::string gameStr, int n, bool whiteMove) {
		Trie* trie = search(rootTrie, gameStr);
		std::vector<std::pair<std::string, float>> moves;
		if (!trie) return moves;

		// If the node is a leaf node
		// Use overlap finding algorithm to find where/if there is a match
		// https://neil.fraser.name/news/2010/11/04/
		if (trie->nextMoves != "") {
			std::string nm = trie->nextMoves;
			int textLength1 = gameStr.size();
			int textLength2 = nm.size();
			// null cases
			if (textLength1 == 0 || textLength2 == 0) {
				if (nm.find(" ") != std::string::npos)
					moves.push_back(std::make_pair(nm.substr(0, nm.find(" ")), trie->rating()));
				return moves;
			}
			if (textLength1 > textLength2)
				gameStr = gameStr.substr(textLength1 - textLength2);
			else if (textLength1 < textLength2)
				nm = nm.substr(0, textLength1);
			if (nm == gameStr)
				return moves;

			// Look for single character match and increase length until no match is found
			int nextIndex = 0;
			int length = 1;
			while (true) {
				std::string pattern = gameStr.substr(textLength1 - length);
				if (nm.find(pattern) == std::string::npos)
					// some logic here to return next string
					break;
				int found = nm.find(pattern);
				length += found;
				if (gameStr.substr(textLength1 - length) == nm.substr(0, length)) {
					nextIndex = length;
					length += 1;
				}
			}

			nm = nm.substr(nextIndex);
			if (nm.find(" ") != std::string::npos)
				moves.push_back(std::make_pair(nm.substr(0, nm.find(" ")), trie->rating()));
			return moves;
		}


		// If the node is a branching node.
		std::priority_queue<std::pair<float, std::string>, std::vector< std::pair<float, std::string>>, std::greater< std::pair<float, std::string>>> pq;
		for (auto iter = trie->children.begin(); iter != trie->children.end(); iter++) {
			
			Trie* child = iter->second;
			// If white, exclude any negative scores, if black, exclude any positive scores.
			if ((whiteMove && child->rating() >= 0) || (!whiteMove && child->rating() <= 0))
				pq.push(std::make_pair(child->numChildren, iter->first));
			if (pq.size() > n)
				pq.pop();
		}
		while (!pq.empty()) {
			std::string tempStr = pq.top().second;
			moves.push_back(std::make_pair(tempStr, trie->getChild(tempStr)->rating()));
			pq.pop();
		}
		return moves;
	}
};

struct ChessGUI {

	ChessBoard cb;
	std::map<std::string, sf::Texture> texMap;
	sf::Sprite* pieceSprites[8][8];
	std::string gameStr;
	const char numToLetter[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	Trie* chessTrie;
	RBNode* chessRB;
	Database database;
	bool whiteTurn = true;

	sf::Font font;
	sf::Text header, scoreText, tTimeText, rbTimeText, childrenText, recsText, bestMoveText, resetText;
	sf::Text recMoves[3] = { sf::Text("", font, 20), sf::Text("", font, 20), sf::Text("", font, 20) };

	ChessGUI() {
		cb = ChessBoard();
		texMap = setUpTextureMap();
		initSprites();
		gameStr = "";
		database = Database();
	}

	void initText() {
		font.loadFromFile("arial.ttf");
		header = sf::Text("White Turn", font);
		header.setFillColor(sf::Color::Black);
		sf::FloatRect textRect = header.getLocalBounds();
		header.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		header.setPosition(sf::Vector2f(656, 50));

		resetText = sf::Text("Reset", font);
		resetText.setFillColor(sf::Color::Black);
		textRect = resetText.getLocalBounds();
		resetText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		resetText.setPosition(sf::Vector2f(656, 465));

		std::string score = "Game Status: " + std::to_string(database.ratingTrie(gameStr));
		database.ratingRB(gameStr);
		scoreText = sf::Text(score, font, 20);
		scoreText.setFillColor(sf::Color::Black);
		scoreText.setPosition(sf::Vector2f(525, 75));

		std::string tTime = "Trie Time: " + std::to_string(database.timeLoadTrie) + " ms";
		tTimeText = sf::Text(tTime, font, 20);
		tTimeText.setFillColor(sf::Color::Black);
		tTimeText.setPosition(sf::Vector2f(525, 150));

		std::string rbTime = "RB Time: " + std::to_string(database.timeLoadRB) + " ms";
		rbTimeText = sf::Text(rbTime, font, 20);
		rbTimeText.setFillColor(sf::Color::Black);
		rbTimeText.setPosition(sf::Vector2f(525, 175));

		childrenText = sf::Text("# Child Games: " + std::to_string(database.rootTrie->numChildren), font, 20);
		childrenText.setFillColor(sf::Color::Black);
		childrenText.setPosition(sf::Vector2f(525, 200));

		recsText = sf::Text("Rec. Moves for White", font, 20);
		recsText.setFillColor(sf::Color::Black);
		recsText.setPosition(sf::Vector2f(525, 250));

		for (int i = 0; i < 3; i++) {
			recMoves[i].setFillColor(sf::Color::Black);
			recMoves[i].setPosition(sf::Vector2f(525, 275 + 25 * i));
		}
	}

	// Make sure to load in databases from main before running GUI
	void runGUI() {
		sf::RenderWindow window(sf::VideoMode(830, 512), "Check-Mate");
		window.setFramerateLimit(60);

		sf::Texture checker;
		checker.loadFromFile("icons/empty-chessboard.png");
		sf::Sprite background(checker);

		sf::RectangleShape resetButton(sf::Vector2f(200, 50));
		resetButton.setFillColor(sf::Color(227, 227, 227));
		resetButton.setOutlineColor(sf::Color(0, 0, 0));
		resetButton.setPosition(sf::Vector2f(512 + 44, 440));
		
		initText();

		bool dragging = false;
		Piece* currPiece = nullptr;
		sf::Sprite* currSprite = nullptr;
		char origX;
		char origY;
		Result status = Result::Running;
		// Window event loop
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonPressed) {
					int xcoord = event.mouseButton.x;
					int ycoord = event.mouseButton.y;
					
					// Drag and drop pieces logic
					if (status == Result::Running && xcoord >= 0 && xcoord < 512 && ycoord >= 0 && ycoord < 512) {
						origX = xcoord / 64;
						origY = 7 - ycoord / 64;
						currPiece = cb.squares[origX][origY];
						if (whiteTurn && currPiece && currPiece->colour == Colour::White || !whiteTurn && currPiece->colour == Colour::Black) {
							dragging = true;
							currSprite = pieceSprites[origX][origY];
						}
					}
					if (resetButton.getGlobalBounds().contains(sf::Vector2f(xcoord, ycoord)))
						reset();
				}
				else if (event.type == sf::Event::MouseButtonReleased) {
					int xcoord = event.mouseButton.x;
					int ycoord = event.mouseButton.y;

					if (status == Result::Running && dragging && xcoord >= 0 && xcoord < 512 && ycoord >= 0 && ycoord < 512 && currPiece) {
						char destX = xcoord / 64;
						char destY = 7 - ycoord / 64;
						MoveData move = cb.moveTo(std::make_tuple(origX, origY), std::make_tuple(destX, destY));

						if (move.validMove) {
							appendGameStr(move);
							std::cout << gameStr << std::endl;
							moveSprites(destX, destY, origX, origY, move);
							whiteTurn = !whiteTurn;

							// Check endgame status
							if (cb.isChecked(Colour::White) && cb.getPossibleMoves(Colour::White).empty()) {
								status = Result::BlackWin;
								header.setString("Black Wins!");
							}
							else if (cb.isChecked(Colour::Black) && cb.getPossibleMoves(Colour::Black).empty()) {
								status = Result::WhiteWin;
								header.setString("White Wins!");
							}
							else if ((whiteTurn && cb.getPossibleMoves(Colour::White).empty()) || (!whiteTurn && cb.getPossibleMoves(Colour::Black).empty())) {
								status = Result::Draw;
								header.setString("Draw!");
							}
							else if (whiteTurn) {
								header.setString("White's Turn");
								float gameStatus = database.ratingTrie(gameStr);
								if (gameStatus > 0) {
									scoreText.setString("Game Status: " + std::to_string(abs(gameStatus)) + " (White)");
								}
								else {
									scoreText.setString("Game Status: " + std::to_string(abs(gameStatus)) + " (Black)");
								}
								database.ratingRB(gameStr);
							}
							else {
								header.setString("Black's Turn");
								float gameStatus = database.ratingTrie(gameStr);
								if (gameStatus > 0) {
									scoreText.setString("Game Status: " + std::to_string(abs(gameStatus)) + " (White)");
								}
								else {
									scoreText.setString("Game Status: " + std::to_string(abs(gameStatus)) + " (Black)");
								}
								database.ratingRB(gameStr);
							}

							if (database.children == 0) {
								scoreText.setString("Game Status: ????");
							}
							
							tTimeText.setString("Trie search: " + std::to_string(database.timeRatingTrie) + " us");
							rbTimeText.setString("R-B search: " + std::to_string(database.timeRatingRB) + " us");
							childrenText.setString("# Child Games: " + std::to_string(database.children));

							if (whiteTurn) {
								recsText.setString("Rec. Moves for White:");
							}
							else {
								recsText.setString("Rec. Moves for Black:");
							}

							for (int i = 0; i < 3; i++)
								recMoves[i].setString("");
							auto bestMoves = database.bestMoves(gameStr, 3, whiteTurn);

							// Filter out best moves for the opposing player
							for (auto it = bestMoves.begin(); it != bestMoves.end(); ++it) {
								if (it->second < 0 && whiteTurn) {
									bestMoves.erase(it);
								}
								else if (it->second > 0 && !whiteTurn) {
									bestMoves.erase(it);
								}
							}

							// Sort the values by magnitude using selection sort
							if (bestMoves.size() > 0) {
								for (int x = 0; x < bestMoves.size() - 1; x++) {
									int biggestElIndex = x;
									for (int y = x + 1; y < bestMoves.size(); y++) {
										if (abs(bestMoves[y].second) > abs(bestMoves[biggestElIndex].second)) {
											biggestElIndex = y;
										}
									}
									auto temp = bestMoves[x];
									bestMoves[x] = bestMoves[biggestElIndex];
									bestMoves[biggestElIndex] = temp;
								}
							}
							for (int i = 0; i < bestMoves.size(); i++)
								recMoves[i].setString(bestMoves[i].first + " (Score: " + std::to_string(abs(bestMoves[i].second)) + ")");
						}

					}
					updateSpriteLocations();
					dragging = false;
					currPiece = nullptr;
					currSprite = nullptr;
				}
			}

			// Dragging a sprite logic
			if (dragging && currSprite) {
				auto mousePos = sf::Mouse::getPosition(window);
				currSprite->setPosition(sf::Vector2f(mousePos.x - 32, mousePos.y - 32));
			}

			window.clear(sf::Color(240, 240, 240));
			window.draw(background);
			window.draw(resetButton);
			window.draw(header);
			window.draw(scoreText);
			window.draw(tTimeText);
			window.draw(rbTimeText);
			window.draw(childrenText);
			window.draw(recsText);
			window.draw(bestMoveText);
			window.draw(resetText);
			for (int i = 0; i < 3; i++)
				window.draw(recMoves[i]);
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (pieceSprites[i][j] != nullptr)
						window.draw(*pieceSprites[i][j]);
			
			if (currSprite) window.draw(*currSprite);
			window.display();
		}
	}
	void moveSprites(char destX, char destY, char origX, char origY, MoveData& move)
	{
		pieceSprites[destX][destY] = pieceSprites[origX][origY];
		pieceSprites[origX][origY] = nullptr;
		if (move.isEnPassant)
			pieceSprites[std::get<0>(move.prevEnPassantPawn)][std::get<1>(move.prevEnPassantPawn)] = nullptr;
		else if (move.isPromotion) {
			if (cb.squares[destX][destY]->colour == Colour::White)
				pieceSprites[destX][destY]->setTexture(texMap["wQueen"]);
			else
				pieceSprites[destX][destY]->setTexture(texMap["bQueen"]);
		}
		else if (move.isWhiteLRookCastling) {
			pieceSprites[3][0] = pieceSprites[0][0];
			pieceSprites[0][0] = nullptr;
		}
		else if (move.isWhiteRRookCastling) {
			pieceSprites[5][0] = pieceSprites[7][0];
			pieceSprites[7][0] = nullptr;
		}
		else if (move.isBlackLRookCastling) {
			pieceSprites[3][7] = pieceSprites[0][7];
			pieceSprites[0][7] = nullptr;
		}
		else if (move.isBlackRRookCastling) {
			pieceSprites[5][7] = pieceSprites[7][7];
			pieceSprites[7][7] = nullptr;
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
			temp.loadFromFile(filename);
			textureMap.emplace(filelist[i], temp);
		}
		return textureMap;
	}
	void updateSpriteLocations() {
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (pieceSprites[i][j] != nullptr)
					pieceSprites[i][j]->setPosition(sf::Vector2f(i * 64, 448 - j * 64));
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
	void appendGameStr(MoveData& move) {
		std::string moveStr = "";

		// Handle casting moves first
		if (move.isWhiteLRookCastling || move.isBlackLRookCastling) {
			gameStr += "O-O-O ";
			return;
		}
		else if (move.isWhiteRRookCastling || move.isBlackRRookCastling) {
			gameStr += "O-O ";
			return;
		}

		// piece symbol
		if (move.pieceMoved->getSymbol() != 'p')
			moveStr += move.pieceMoved->getSymbol();

		// clarify file or rank (or both) in case multiple of that piece can move.
		// First, find if any identical piece has the same move list as this piece.
		if (move.pieceMoved->getSymbol() != 'p') {
			int conflictX = -1;
			int conflictY = -1;
			for (std::tuple<char, char> coords : move.pieceIdentical) {
				// pull piece from cb squares and compare move list
				int x = std::get<0>(coords);
				int y = std::get<1>(coords);
				for (std::tuple<char, char> possible : cb.squares[x][y]->moveList)
					if (possible == move.dest) {
						conflictX = x;
						conflictY = y;
					}
			}
			std::cout << "conflict at " << conflictX << " " << conflictY << std::endl;
			if (conflictX > -1) {
				if (conflictX != std::get<0>(move.orig))
					moveStr += numToLetter[std::get<0>(move.orig)];		//if conflict and files !=, add file to the gamestr
				//else if (conflictY != std::get<1>(move.orig))
				//	moveStr += std::to_string(std::get<1>(move.orig) + 1);
				else {
					moveStr += numToLetter[std::get<0>(move.orig)] + std::to_string(std::get<1>(move.orig) + 1);
				}
			}
		}

		// include "x" if there was a capture
		if (move.pieceTaken != nullptr) {
			if (move.pieceMoved->getSymbol() == 'p')
				moveStr += numToLetter[std::get<0>(move.orig)];
			moveStr += "x";
		}
			
		// Add the dest coordinates
		moveStr += numToLetter[std::get<0>(move.dest)] + std::to_string(std::get<1>(move.dest) + 1);

		// Add promotion
		if (move.isPromotion)
			moveStr += "=Q";

		// Add plus if checked, add hash if checkmate
		if (cb.isChecked(Colour::White) && cb.getPossibleMoves(Colour::White).empty() || cb.isChecked(Colour::Black) && cb.getPossibleMoves(Colour::Black).empty())
			moveStr += "#";
		else if (cb.isChecked(Colour::White) || cb.isChecked(Colour::Black))
			moveStr += "+";
		moveStr += " ";
		gameStr += moveStr;
		return;	
	}
	void reset() {
		cb.resetBoard();
		initSprites();
		gameStr = "";
		whiteTurn = true;
		initText();
	}
};


int main() {
	//trimF("iofiles/in201301.pgn");

	ChessGUI gui;
	gui.database.loadFromFile("iofiles/output.txt");
	gui.runGUI();

	return 0;
}

