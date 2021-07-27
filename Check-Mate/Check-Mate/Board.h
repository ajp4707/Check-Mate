/** We did not produce this file. This API was provided by Baran Can Oner
*	Source: https://github.com/BaranCanOener/ConsoleChess
*	We only use his Chess board and piece framework
*	All other code (GUI, data structures) is ours
*/

#pragma once
#include "pieces.h"
#include <tuple>
#include <vector>
#include <iostream>

struct MoveData
{
	std::tuple<char, char> orig;
	std::tuple<char, char> dest;
	std::tuple<char, char> prevEnPassantPawn;
	Piece* pieceMoved = nullptr;
	Piece* pieceTaken = nullptr;
	std::vector<std::tuple<char, char>> pieceIdentical = std::vector<std::tuple<char,char>>();
	bool isWhiteLRookCastling = false;
	bool isWhiteRRookCastling = false;
	bool isBlackLRookCastling = false;
	bool isBlackRRookCastling = false;
	bool isPromotion = false;
	bool isEnPassant = false;
	bool validMove = false;
};

class ChessBoard
{
private:
	void initializeOriginalSquares();
	Piece* originalSquares[8][8];
	int plyCount;
	std::vector<Piece*> promotedQueens;
	std::tuple<char, char> kingWhiteLocation;
	std::tuple<char, char> kingBlackLocation;
	std::tuple<char, char> enPassantPawn = std::tuple<char, char>(127, 127); //stores the location of a pawn allowing for an en passant capture
public:
	bool allowIllegalMoves = false;
	bool whiteCastled = false;
	bool blackCastled = false;
	Piece* squares[8][8];
	void resetToDebugBoard();
	void resetBoard();
	int getPlyCount();
	bool isChecked(Colour colour);
	bool squareAttackedBy(std::tuple<char, char> square, Colour colour);
	std::vector<std::tuple<char, char, char, char>> getPossibleCaptures(Colour colour);
	std::vector<std::tuple<char, char, char, char>> getPossibleMoves(Colour colour);
	MoveData moveTo(std::tuple<char, char> orig, std::tuple<char, char> dest);
	void undoMove(MoveData move);
	ChessBoard();
};