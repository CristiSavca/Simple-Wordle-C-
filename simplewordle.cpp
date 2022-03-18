//
/*
@Author: Cristi Savca
Attempt at creating my own simple version of Wordle

3/17/22 created game
3/18/22 added colors and design

TO DO: ensure input checks if 5 letters & converts to uppercase

*/
#include <iostream> //necessary libs
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;

//list of 5 letter words
string wordlist[] = { "HELLO","HURTS","BEAMS","ABUSE","CROWD","DRINK","APPLY","DROWN","LEGAL","RUBLE","BLOOD","PAUSE","BINGO","FLEAS","HORNY","CANDY","SCENE","WORLD" };

string word[5]; // array that will hold chars of word chosen for current game
string arrguess[5]; // array for holding chars of user inputted guess word
string check[5]; // array for holding "V, X, and ?" symbols determined by how chars in guess[] relate to word[]
//----------------------------------------------------------------------------------------------------------------------------------------------------------
void color(int x, string text) // this function right here is the drip - it can cout << things in any color
{
	HANDLE h; // name this whatever you want. Here I put "h" 
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, x);
	cout << text;
	//This next part makes it normal again
	int normal = 15;
	SetConsoleTextAttribute(h, normal);
}

void transform(string& word) { // this function transforms inputted word into array guess[] array
	for (int i = 0; i < word.length(); i++) {
		arrguess[i] = word[i];
	}
}

int main()//------------------------------------------------------------------------------------------------------------------------------------------------
{
	srand(time(NULL));                 // this section here generates random number from length of word list
	int arrSize = sizeof(wordlist) / sizeof(wordlist[0]);
	int random = rand() % (arrSize);
	for (int i = 0; i < 5; i++) {      // then loads the letters of the chosen word into word[] array
		string chosen = "";
		chosen = wordlist[random];
		word[i] = chosen[i];
	}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	color(002, "@~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@"); cout << endl;
	color(9, " **       **   *******   *******   *******   **       ********"); cout << endl;
	color(9, "/**      /**  **/////** /**////** /**////** /**      /**///// "); cout << endl;
	color(9, "/**   *  /** **     //**/**   /** /**    /**/**      /**      "); cout << endl;
	color(9, "/**  *** /**/**      /**/*******  /**    /**/**      /******* "); cout << endl;
	color(9, "/** **/**/**/**      /**/**///**  /**    /**/**      /**////  "); cout << endl;
	color(9, "/**** //****//**     ** /**  //** /**    ** /**      /**      "); cout << endl;
	color(9, "/**/   ///** //*******  /**   //**/*******  /********/********"); cout << endl;
	color(9, "//       //   ///////   //     // ///////   //////// //////// "); cout << endl;
	color(002, "@~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@"); cout << endl;

	color(5, "   ____  __  __  __    ____  ____"); cout << endl;
	color(13, "  / _ / / / / / / /   / __/ / __/"); color(2, " V"); color(9, " = is in word"); cout << endl;
	color(14, " / , / / /_/ / / /__ / _/  _| |  "); color(6, " ?"); color(9, " = is in word but wrong place"); cout << endl;
	color(11, "/_/|_| |____/ /____//___/ /___/  "); color(12, " X"); color(9, " = not in word"); cout << endl;
	cout << endl;

	color(75, "ENTER A WORD 5 LETTERS LONG"); cout << endl;
	color(75, "TYPE ALL WORDS IN UPPERCASE"); cout << endl;
	//color(12, ""); cout << endl;
	color(7, "'''''"); cout << endl;
//----------------------------------------------------------------------------------------------------------------------------------------------------------
	string guess;  // initialize guess string & ask for input
	int tries = 6; // initialize the amount of tries user has to guess word
	do {
		getline(cin, guess);

		transform(guess);

		for (int i = 0; i < 5; i++) {
			for (int i2 = 0; i2 < 5; i2++) {
				if (word[i] != arrguess[i2] && arrguess[i] != word[i]) { // checks which letters are not in the word first
					check[i] = "X";
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int i2 = 0; i2 < 5; i2++) {
				if (arrguess[i] == word[i2]) {  // checks if letter is in word but wrong place and possibly overrides previous check for X
					check[i] = "?";
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			if (arrguess[i] == word[i]) { // checks if letter is in word and correct place and possibly overrides the previous check for ?
				check[i] = "V";
			}
		}

		for (int i = 0; i < 5; i++) {  // print out check[] symbols with correct color under inputted word to show which letters were right/wrong
			if (check[i] == "X") {
				color(12, "X");
			}
			else if (check[i] == "?") {
				color(6, "?");
			}
			else {
				color(2, "V");
			}
		}
		cout << endl;

		if (check[0] == "V" && check[1] == "V" && check[2] == "V" && check[3] == "V" && check[4] == "V") { // check if word was guessed entirely
			color(2, "YOU GUESSED CORRECT"); cout << endl;
			color(2, "CONGRATULATIONS !!!"); cout << endl;
			break;
		}

		tries -= 1; // reduce tries counter by 1 each time the do loop completes
	} while (tries != 0);
	
	if (tries == 0) {
		color(4, "OUT OF TRIES !!!"); cout << endl; color(4, "the word was "); // print out what the word is if it wasn't guessed
		for (int i = 0; i < 5; i++) {
			cout << word[i];
		}
		cout << endl; color(9, "Better luck next time ;)");
	}

	return 0;

}