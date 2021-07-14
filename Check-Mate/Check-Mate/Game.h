#include<string>
#include<iostream>
#include<fstream>

#pragma once
struct Game
{
	char score; // White = 2. Draw = 1. Black = 0.
	std::string game;

	Game();

};

/*
void trim(std::string filename) {
	std::ifstream input;
	input.open(filename);

	std::ofstream output;
	output.open("output.txt", std::ofstream::out | std::ofstream::trunc);

	// Read in PGN format. 
	// Verify that the chess game meets the following criteria before adding to output file
	// 1. Game must have terminated normally (ie. checkmate)
	// 2. Must not have external commented
	std::string score;
	std::string line;

	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			if (line == "[Termination \"Normal\"]") {
				// Pass by one empty line
				getline(input, line);
				getline(input, line);
				if (line.substr(0, 10).find("{") != std::string::npos)		// if there are comments, abort
					continue;
				std::string result = line.substr(line.length() - 3, 3);
				if (result == "1-0") {	// white wins
					score = "2";
					line = line.substr(0, line.length() - 3);
				}
				else if (result == "0-1") {		// black wins
					score = "0";
					line = line.substr(0, line.length() - 3);
				}
				else if (result == "1/2") {		// draw
					score = "1";
					line = line.substr(0, line.length() - 7);
				}
				output << score << "\n";
				output << line << "\n";
			}
		}
		input.close();
		output.close();
	}

}
*/


// Source for fopen_s usage syntax: https://comp.lang.cpp.moderated.narkive.com/HfegujV0/fgets-vs-std-getline-performance#post2
// Function that quickly trims unecessary information from the PGN file
// Output.txt contains simplified chess games with the following format
// On the first line, the score from 0-2. 0 is a black win, 1 is draw, 2 is white win
// ON the second line is the algebraic notation of the game.
void trimF(std::string filename) {
	FILE* input;
	fopen_s(&input, filename.c_str(), "r");

	std::ofstream output;
	output.open("output.txt", std::ofstream::out | std::ofstream::trunc);

	// Read in PGN format. 
	// Verify that the chess game meets the following criteria before adding to output file
	// 1. Game must have terminated normally (ie. checkmate)
	// 2. Must not have external commented
	std::string score;
	char cline[2048];
	std::string sline;

	while (std::fgets(cline, 2048, input) != NULL)
	{
		sline = cline;
		if (sline == "[Termination \"Normal\"]\n") {
			// Pass by one empty line
			std::fgets(cline, 2048, input);
			std::fgets(cline, 2048, input);
			sline = cline;
			if (sline.substr(0, 10).find("{") != std::string::npos)		// if there are comments, abort
				continue;
			std::string result = sline.substr(sline.length() - 4, 4);
			if (result == "1-0\n") {	// white wins
				score = "2";
				sline = sline.substr(0, sline.length() - 4);
			}
			else if (result == "0-1\n") {		// black wins
				score = "0";
				sline = sline.substr(0, sline.length() - 4);
			}
			else if (result == "1/2\n") {		// draw
				score = "1";
				sline = sline.substr(0, sline.length() - 8);
			}
			output << score << "\n";
			output << sline << "\n";
		}
	}
	output.close();


}