#include "inputHelper.h"


/**
 * Reads in games in PGN format and trims them down to only scores and gameStrings
 *
 * @param filename Input file in PGN format
 * @file output The corresponding output file with scores and gameStrs
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
	// 2. Must not have external comments
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

			// Remove move numbers (ie. 1. 2. 3.) from the string. Every third token, starting from token 0
			int pos = 0;
			int index;
			int tick = 0;
			std::string delim = " ";
			while ((index = sline.find(delim, pos)) != std::string::npos) {
				if (tick == 0)
					sline.erase(pos, index - pos + 1);
				else
					pos = index + 1;
				tick++;
				tick %= 3;
			}

			output << score << "\n";
			output << sline << "\n";
		}
	}
	output.close();
}

/**
 * Reads and inserts Trie nodes from our Trimmed file, which is the output of TrimF
 *
 * @param root Trie root node
 * @param trimFilname The filename of the trimmed file
 */
Trie * loadTrieFromTrim(Trie* root, std::string trimFilename) {
	FILE* input;
	fopen_s(&input, trimFilename.c_str(), "r");

	std::string scoreStr;
	char score = 0;
	char cline[2048];
	std::string gameStr;

	while (std::fgets(cline, 2048, input) != NULL) {
		scoreStr = cline;
		score = std::stoi(scoreStr);
		std::fgets(cline, 2048, input);
		gameStr = cline;
		insert(root, gameStr, score);
	}
	return root;
}

/**
 * Reads and inserts Trie nodes from PGN input file
 * Skips having to use TrimF before inserting to Trie
 * Code structure very similar to trimF
 *
 * @param root Trie root node
 * @param inFilname The filename of the PGN file
 */
Trie* loadTrieFromInput(Trie* root, std::string inFilename) {
	FILE* input;
	fopen_s(&input, inFilename.c_str(), "r");

	char score = 0;
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
			if (sline.substr(0, 10).find("{") != std::string::npos)	
				continue;
			std::string result = sline.substr(sline.length() - 4, 4);
			if (result == "1-0\n") {	// white wins
				score = 2;
				sline = sline.substr(0, sline.length() - 4);
			}
			else if (result == "0-1\n") {		// black wins
				score = 0;
				sline = sline.substr(0, sline.length() - 4);
			}
			else if (result == "1/2\n") {		// draw
				score = 1;
				sline = sline.substr(0, sline.length() - 8);
			}

			int pos = 0;
			int index;
			int tick = 0;
			std::string delim = " ";
			while ((index = sline.find(delim, pos)) != std::string::npos) {
				if (tick == 0)
					sline.erase(pos, index - pos + 1);
				else
					pos = index + 1;
				tick++;
				tick %= 3;
			}

			insert(root, sline, score);
		}
	}
	return root;
}