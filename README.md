# Check-Mate

Given a current chess board state and a database of expertly-played chess games, this program will determine the current odds of winning from that position, and determine moves that are most likely to result in a win for the current player.

## How to use

For this release, open Check-Mate.sln in Visual Studio. Ensure the VS project has been configured with SFML. Run main.cpp. After a brief loading period, a GUI will appear with draggable chess pieces and an information tab on the right. 

The game status number is a float ranging from -1 to 1 which indicates the average win rate of children games. A 1 represents a 100% white win rate, and a -1 represets a 100% black win rate. After a move is played, the most popular next moves from up to 3 children games will be presented.

On startup (and after a GUI reset), the number after "R-B Load:" is how many milliseconds it took to load in the chess game database. Likewise for "Trie Load". After a move has been made, the number after "R-B Search:" is how many microseconds it took to calculate the current game status.

## References

Lichess Database - https://database.lichess.org/ (The database we used is January 2013 with 100k + games)

SFML Reference - https://www.sfml-dev.org/documentation/2.5.1/

Setting up SMFL with Visual Studio - https://www.sfml-dev.org/tutorials/2.5/start-vc.php

Chess assets - https://game-icons.net/

Chess Framework (Board.h/.cpp and Piece.h/.cpp) - https://github.com/BaranCanOener/ConsoleChess

Chess Algebraic Notation - https://en.wikipedia.org/wiki/Algebraic_notation_(chess)

PGN File Format - https://www.net-chess.com/sanfaq.html

Red-Black Trees - Ms. Cheryl Resch lectures on Canvas + Mediasite: https://mediasite.video.ufl.edu/Mediasite/Play/dd2c7230add6482e87e0c371fb3988931d

Red-Black Tree rotations - https://www.programiz.com/dsa/red-black-tree and https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/

Tries - https://www.geeksforgeeks.org/trie-insert-and-search/

Fast file I/O using buffers - https://comp.lang.cpp.moderated.narkive.com/HfegujV0/fgets-vs-std-getline-performance#post2

String overlap finding algorithms - https://neil.fraser.name/news/2010/11/04/
