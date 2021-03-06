/** We did not produce this file. This API was provided by Baran Can Oner
*	Source: https://github.com/BaranCanOener/ConsoleChess
*	We only use his Chess board and piece framework
*	All other code (GUI, data structures) is ours
*/
#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

enum class Colour { None, White, Black };
enum class PieceType { None, Pawn, Rook, Bishop, Knight, Queen, King };

//Generic piece implementation - to be overridden by child
class Piece {
private:
	static const char symbol = ' ';
	static const int value = 0; //the material value of the piece
	static const PieceType pieceType = PieceType::None;
public:
	Colour colour;
	int moveCount = 0;
	std::vector<std::tuple<char, char>> moveList; //storage of all possible moves after call of getMoveList
	std::vector<std::tuple<char, char>> captureMoveList; //storage of all possible capture moves after call of getCaptureMoveList
	Piece(Colour colour);
	virtual std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y);
	virtual std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y);
	virtual char getSymbol();
	virtual int getValue();
	virtual PieceType getPieceType();
	virtual int getPositionalScore(char x, char y);
};

class Pawn : public Piece {
private:
	static const char symbol = 'p';
	static const int value = 100;
	static const PieceType pieceType = PieceType::Pawn;
	int scoreBoard[8][8] = {
		{ 0,  0,  0,  0,  0,  0,  0,  0},
		{50, 50, 50, 50, 50, 50, 50, 50},
		{10, 10, 20, 30, 30, 20, 10, 10},
		{5,  5, 10, 25, 25, 10,  5,  5},
		{0,  0,  0, 20, 20,  0,  0,  0},
		{5, -5,-10,  0,  0,-10, -5,  5},
		{5, 10, 10,-20,-20, 10, 10,  5},
		{0,  0,  0,  0,  0,  0,  0,  0}
	};
public:
	Pawn(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};

class Knight : public Piece {
private:
	static const char symbol = 'N';
	static const int value = 320;
	static const PieceType pieceType = PieceType::Knight;
	int scoreBoard[8][8] = {
		{-50,-40,-30,-30,-30,-30,-40,-50},
		{-40,-20,  0,  0,  0,  0,-20,-40},
		{-30,  0, 10, 15, 15, 10,  0,-30},
		{-30,  5, 15, 20, 20, 15,  5,-30},
		{-30,  0, 15, 20, 20, 15,  0,-30},
		{-30,  5, 10, 15, 15, 10,  5,-30},
		{-40,-20,  0,  5,  5,  0,-20,-40},
		{-50,-40,-30,-30,-30,-30,-40,-50}
	};
public:
	Knight(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};

class Rook : public Piece {
private:
	static const char symbol = 'R';
	static const int value = 500;
	static const PieceType pieceType = PieceType::Rook;
	int scoreBoard[8][8] = { { 0, 0, 0, 0, 0, 0, 0, 0},
		{5, 10, 10, 10, 10, 10, 10, 5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{0, 0, 0, 5, 5, 0, 0, 0}
	};
public:
	Rook(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};

class Bishop : public Piece {
private:
	static const char symbol = 'B';
	static const int value = 330;
	static const PieceType pieceType = PieceType::Bishop;
	int scoreBoard[8][8] = { {-20, -10, -10, -10, -10, -10, -10, -20},
		{-10, 0, 0, 0, 0, 0, 0, -10},
		{-10, 0, 5, 10, 10, 5, 0, -10},
		{-10, 5, 5, 10, 10, 5, 5, -10},
		{-10, 0, 10, 10, 10, 10, 0, -10},
		{-10, 10, 10, 10, 10, 10, 10, -10},
		{-10, 5, 0, 0, 0, 0, 5, -10},
		{-20, -10, -10, -10, -10, -10, -10, -20}
	};
public:
	Bishop(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};

class Queen : public Piece {
private:
	static const char symbol = 'Q';
	static const int value = 900;
	static const PieceType pieceType = PieceType::Queen;
	int scoreBoard[8][8] = { { 0, 0, 0, 0, 0, 0, 0, 0},
		{5, 10, 10, 10, 10, 10, 10, 5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{-5, 0, 0, 0, 0, 0, 0, -5},
		{0, 0, 0, 5, 5, 0, 0, 0}
	};
public:
	Queen(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};

class King : public Piece {
private:
	static const char symbol = 'K';
	static const int value = 30000;
	static const PieceType pieceType = PieceType::King;
	int scoreBoard[8][8] = { {-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-30, -40, -40, -50, -50, -40, -40, -30},
		{-20, -30, -30, -40, -40, -30, -30, -20},
		{-10, -20, -20, -20, -20, -20, -20, -10},
		{20, 20, 0, 0, 0, 0, 20, 20},
		{20, 30, 10, 0, 0, 10, 30, 20}
	};
public:
	King(Colour colour);
	std::vector<std::tuple<char, char>> getMoveList(Piece* squares[8][8], char x, char y) override;
	std::vector<std::tuple<char, char>> getCaptureMoveList(Piece* squares[8][8], char x, char y) override;
	char getSymbol() override;
	int getValue() override;
	PieceType getPieceType() override;
	int getPositionalScore(char x, char y) override;
};