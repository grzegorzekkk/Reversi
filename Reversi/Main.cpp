#define _CRT_SECURE_NO_WARNINGS

#include<iostream>  // streams
#include<cstdlib> // system()
#include<ctime> // srand, rand
#include<conio.h>	// getch()
#include"Board.h"  // board of game
#include"Human.h"  
#include"Computer.h"  

using namespace std;

bool chooseGamemode();
int chooseColor();

template<typename T>
int selectMenu(T existsSave);

void showResults(Player &black, Player &white, Board *game);
void showRules();
void showLeaderboard();

void save(Player &black, Player &white, Board *game); // Saves current game state to file
bool existsFile(string name); // Checks if file exists
vector<Player*> load(Board *game); // Loads save and return vector of players
//

int main()
{
	srand(time(NULL));  // Random numbers seed

	// gameloops
	//
	bool quit = false;
	bool inGame = false;
	bool loadGame = false;
	int chosenColor = 1;
	static const int blackColor = 1;
	static const int whiteColor = 2;

	Board game(8, 8); // Standard size board
	game.setPlayerTurn(blackColor); // Black player starts the game.

	Player *black = NULL;
	Player *white = NULL;

	while (!quit)
	{
		system("cls");
		switch (selectMenu<bool>(existsFile("save.txt")))
		{
		case 0: // selected load game
			inGame = true;
			loadGame = true;
			break;
		case 1: // selected new game
			inGame = true;
			loadGame = false;
			game.setGamemode(chooseGamemode());
			if (game.getGamemode() == 1)	chosenColor = chooseColor();
			break;
		case 2: // selected rules
			showRules();
			break;
		case 3:	// selected leaderboards
			showLeaderboard();
			break;
		case 5: // selected end of application
			quit = true;
			break;
		}

		// Prepare board and players to game
		bool validTurnBlack, validTurnWhite;
		if (inGame)
		{
			game.regen(); // Clear board and initial setup

			if (loadGame)
			{
				vector<Player*> save = load(&game); // Load board and get playerdata
				black = save[0];						 
				white = save[1];
			}
			// Prepare players to new game
			else
			{
				if (game.getGamemode()) // If selected singleplayer
				{
					if (chosenColor == blackColor)
					{
						black = new Human(&game, blackColor);
						white = new Computer(&game, whiteColor);
					}
					else
					{
						white = new Human(&game, whiteColor);
						black = new Computer(&game, blackColor);
					}
				}
				else  // If selected multiplayer
				{
					black = new Human(&game, blackColor);
					white = new Human(&game, whiteColor);
				}

				// get and set player names
				black->setNick();
				white->setNick();
			}
			
			// If game is loaded and its time for white player turn
			if (loadGame)
			{
				if (game.getPlayerTurn() == whiteColor)
				{
					system("cls");
					game.print();
					save(*black, *white, &game);
					validTurnWhite = white->move();
					game.setPlayerTurn(blackColor);
				}
			}
		}
		// Game time
		while (inGame)
		{
			system("cls");
			game.print();
			save(*black, *white, &game);
			validTurnBlack = black->move();
			game.setPlayerTurn(whiteColor);

			system("cls");
			game.print();
			save(*black, *white, &game);
			validTurnWhite = white->move();
			game.setPlayerTurn(blackColor);

			// If both players cant move its time to stop the game
			if (!validTurnBlack && !validTurnWhite)
			{
				showResults(*black, *white, &game);
				inGame = false;
			}

		}
	}

	delete(black); 
	delete(white); 	   

	return 0;
}

// Gamemode menu
bool chooseGamemode()
{
	system("cls");
	cout << "Which gamemode do you choose?" << endl;
	cout << "1. You vs Computer" << endl;
	cout << "2. You vs other player" << endl;
	cout << "Press 1 or 2 to choose." << endl;
	while (true)
	{
		switch (_getch())
		{
		case '1':
			return true;
			break;
		case '2':
			return false;
			break;
		}
	}
}

// Choose color menu
int chooseColor()
{
	string answer;
	bool validAnswer = false;

	cout << endl;
	while (true)
	{
		cout << "Which color do you choose? Type: black or white" << endl;
		cin >> answer;
		cin.ignore();
		cin.clear();

		if (answer == "black")
		{
			return 1;
		}
		else if (answer == "white")
		{
			return 2;
		}
	}
}

// Show main menu
template<typename T>
int selectMenu(T existsSave) 
{
	cout << "Reversi" << endl;
	if (existsSave)
	{
		cout << "1. Load game" << endl;
		cout << "2. New game" << endl;
		cout << "3. Rules" << endl;
		cout << "4. Leaderboard" << endl;
		cout << "5. Quit" << endl;
	}
	else
	{
		cout << "1. New game" << endl;
		cout << "2. Rules" << endl;
		cout << "3. Leaderboard" << endl;
		cout << "4. Quit" << endl;
	}
	cout << "Press one of the numbers to choose" << endl;

	if (existsSave)
	{
		switch (_getch())
		{
		case '1':
			return 0;
			break;
		case '2': 
			return 1;
			break;
		case '3':
			return 2;
			break;
		case '4': 
			return 3;
			break;
		case '5': 
			return 5;
			break;
		case 27:  
			return 5;
			break;
		}
	}
	else
	{
		switch (_getch())
		{
		case '1':
			return 1;
			break;
		case '2': 
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4': 
			return 5;
			break;
		case 27: 
			return 5;
			break;
		}
	}
	return -1;
}

// Show game rules
void showRules()
{
	system("cls");
	cout << "Reversi game is designed for 2 players." << endl;
	cout << "The standard board size is 8x8." << endl;
	cout << "The goal is to collect the most number of pawns on the board." << endl;
	cout << "To achieve that, player must place and conquer enemys pawns." << endl;
	cout << "More rules of the game are available here: https://en.wikipedia.org/wiki/Reversi" << endl << endl;

	cout << "Press ESC, to go back to menu" << endl;
	while (true)
	{
		if (_getch() == 27)
			break;
	}
}

void showLeaderboard()
{
	system("cls");

	if (!existsFile("leaderboard.txt"))
	{								 
		cout << "No games played before" << endl;
		cout << "Play at least one round to check your statistics" << endl;
	}
	else
	{
		ifstream loadFile("leaderboard.txt");
		string line;
		int i = 1;

		cout << "Games statistics from oldest to newest: " << endl;
		while (!loadFile.eof())
		{
			getline(loadFile, line);
			cout << i << ". " << line << endl;
			i++;
		}
		loadFile.close();
	}

	cout << "Press ESC, to go back to menu" << endl;
	while (true)
	{
		if (_getch() == 27)
			break;
	}
}


void showResults(Player &black, Player &white, Board *game)
{
	ofstream results;
	results.open("leaderboard.txt", fstream::app);

	time_t timeRaw;
	struct tm * timeFormatted;
	char buffer[100];

	time(&timeRaw);
	timeFormatted = localtime(&timeRaw);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeFormatted);
	string timeString(buffer);
	//

	int blackPawns = black.getPossesessedPawns();
	int whitePawns = white.getPossesessedPawns();

	system("cls");

	cout << "Round ended!" << endl;
	if (blackPawns > whitePawns)
	{
		cout << "Round has been won by " << black.getNick() << " with black pawns, collected: " << blackPawns << endl;
		cout << "Player " << white.getNick()<< " with white pawns collected: " << whitePawns << endl;
		results << timeString << " Black player won (" << black.getNick() << " " << blackPawns
			<< " pawns) " << "Defeated player (" << white.getNick() << " " << whitePawns << " pawns)" << endl;
	}
	else if (whitePawns > blackPawns)
	{
		cout << "Round has been won by " << white.getNick() << " with white pawns, collected: " << whitePawns << endl;
		cout << "Player " << black.getNick() << " with black pawns collected: " << blackPawns << endl;
		results << timeString << " White player won (" << white.getNick() << " " << whitePawns
			<< " pawns) " << "Defeated player (" << black.getNick() << " " << blackPawns << " pawns)" << endl;
	}
	else
	{
		cout << "Draw! Both of opponents collected " << blackPawns << " pawns." << endl;
		results << timeString << " Draw! Black player (" << black.getNick() << " " << blackPawns
			<< " pawns) " << " white player (" << white.getNick() << " " << whitePawns << " pawns)" << endl;
	}

	results.close();

	cout << "Press ESC, to go back to menu"<< endl;
	while (true)
	{
		if (_getch() == 27)
			break;
	}
}

void save(Player &black, Player &white, Board *game)
{
	ofstream save;

	save.open("save.txt");
	save << "This file is savedata file of Reversi game" << endl;
	save << "Do not modify content of this file!" << endl << endl;

	save << game->getGamemode() << " " << game->getPlayerTurn() << endl << endl;

	save << "Black:" << endl;
	save << black.getNick() << endl;
	save << "White:" << endl;
	save << white.getNick() << endl<< endl;

	for (int i = 0; i < game->getHeight(); i++)
		for (int j = 0; j < game->getWidth(); j++)
			save << game->pawns[i][j].free << " " << game->pawns[i][j].color << endl;

	save.close();
}

bool existsFile(string filename)
{
	ifstream load(filename);

	if (!load.good())
		return false;

	load.close();

	return true;
}

vector<Player*> load(Board *game)
{
	ifstream file("save.txt");
	vector<Player*> players;
	Player *black = NULL;
	Player *white = NULL;

	bool gamemode;
	int playerTurn;
	string nick;

	string line;

	getline(file, line);
	getline(file, line);
	getline(file, line);

	file >> gamemode >> playerTurn;
	getline(file, line);
	getline(file, line);

	getline(file, line);
	file >> nick;
	if (nick != "Computer")
	{
		black = new Human(game, 1);
		black->setNick(nick);
	}
	else
	{
		black = new Computer(game, 1);
		black->setNick();
	}

	getline(file, line);
	getline(file, line);
	file >> nick;
	if (nick != "Computer")
	{
		white = new Human(game, 2);
		white->setNick(nick);
	}
	else
	{
		white = new Computer(game, 2);
		white->setNick();
	}

	players.push_back(black);
	players.push_back(white);

	game->setGamemode(gamemode);
	game->setPlayerTurn(playerTurn);
	getline(file, line);
	for (int i = 0; i < game->getWidth(); i++)
		for (int j = 0; j < game->getHeight(); j++)
			file >> game->pawns[i][j].free >> game->pawns[i][j].color;

	return players;
}