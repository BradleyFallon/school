#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
// ====================================================================
// Homework 2 for CS162
// Bradley Fallon
// bfallon@pdx.edu
// 10/22/2018
// ====================================================================
// Written Questions
// ====================================================================
/*
   ========Question 1:

   The example that I use to define data parallelism, is that an array can be split into multiple smaller arrays,
   then multiple processes can act for each smaller array. This is opposed to the process acting on the whole array all at once.
   In this assignment, I could theoretically apply data parallelism to the scrambling portion. Sometimes when I shuffle a big deck
   of cards, I shuffle it in sections, because it is too think to hold in one hand. I then loosely shuffle the sections togther.
   The same concept could apply to scrambling a very very long word, but it seems totally unnecessary at this scale.

   ========Question 2:

   Sentinel controlled loop
   A sentinel controlled loop should be a while loop. It contiues iterations until a
   condition is evaluated to indicate the looping should be complete. This is useful
   especially when there is no straightforward way to know up front how many times a
   loop should iterate. 
   Counter controlled loop
   This is a loop that runs a number of times by monitoring the value of a counter variable.
   A simple use case, is to increment a counter in a loop while using the counter to reference
   an item at a certain index of an array. Usually you would be looping until the counter is
   the length of the array.
   Side effects
   Side effects are something a function or block of code does outside of returning the value it was called for.
   For example, a function can make a change to a global variable, and that a side effect.
   Prefix vs. Postfix increment
   When incrementing and getting the value of the variable being incremented in the same line,
   this affects whether the variablae is evaluated before or after icrementing.
   I think it is probably best to just use separate lines though.

   ========Question 3:

   Here are some ways that software can protect people's data:
   If data is transfered to other locations, scramble (encrypt) the data before trasport.
   If sensitive data is on screen, be aware of making it as easy to hide as possible.
   Don't leave sensitive data on screen unless it needs to be there.
   Don't ask for sensitive data if you don't need it.
   Let someone know ahead of time what risks are taken when entering data in to the software.

*/
// ====================================================================
// THE PROGRAM
// ====================================================================
/*
   ========PURPOSE:
   This is a text based guessing game for two players. One player is to enter a word, then the word will be scrambled.
   The other player is presented the scrambled word. If this player can guess what the original word
   was in one try, then they get a point. The players swap roles after each turn, and the first to five points wins.

   ========ALGORITHM:
   Welcome the players to the game.
   :   Print a welcome message and instructions.
   :   Clear the instructions.
   Play a game
   :   Play a turn
   :   :   Switch to guesser view.
   :   :   :   Clear the Screen.
   :   :   :   Display overall game status.
   :   :   :   Display message for word source player to take over.
   :   :   Get the word.
   :   :   :   Prompt for a word.
   :   :   :   Validate the entered word.
   :   :   :   :   Check that is longer than 3 letters.
   :   :   :   If validation failed, keep trying.
   :   :   Make all characters lowercase.
   :   :   Make a copy of the word for scrambling.
   :   :   Scramble the word.
   :   :   :   If first letter is less than last letter:
   :   :   :   :   Swap first and last letters.
   :   :   :   :   :   Put first letter in placeholder.
   :   :   :   :   :   First letter copies value of last letter.
   :   :   :   :   :   Last letter copies value of placeholder.
   :   :   :   If the second letter is a vowel:
   :   :   :   :   Swap second and third letters.
   :   :   :   :   :   Put second letter in placeholder.
   :   :   :   :   :   Second letter copies value of third letter.
   :   :   :   :   :   Third letter copies value of placeholder.
   :   :   :   If the third letter is in range 'a' through 'k':
   :   :   :   :   Swap third and fourth letters.
   :   :   :   :   :   Put third letter in placeholder.
   :   :   :   :   :   Third letter copies value of fourth letter.
   :   :   :   :   :   Fourth letter copies value of placeholder.
   :   :   :   :   :   Get the length of the word.
   :   :   :   If there are an even number of letters in the word:
   :   :   :   :   Swap the two central letters.
   :   :   :   :   :   Put (length/2)-1 letter in placeholder.
   :   :   :   :   :   Letter at (length/2)-1 copies value of length/2 letter.
   :   :   :   :   :   Letter at length/2 copies value of placeholder.
   :   :   Switch to guesser view.
   :   :   :   Clear the Screen.
   :   :   :   Display overall game status.
   :   :   :   Display message for word guesser player to take over.
   :   :   Display the scrambled word.
   :   :   Prompt for play or pass.
   :   :   If play is chosen:
   :   :   :   Prompt for guess.
   :   :   :   Make all characters lowercase.
   :   :   :   Check if guess matches original word.
   :   :   :   If guess was correct:
   :   :   :   :   Add one point to current guesser score.
   :   :   :   :   Check if a player wins:
   :   :   :   :   :   Does a player have a score of five or greater.
   :   :   :   :   If a player won:
   :   :   :   :   :   Congratulate the winner
   :   :   :   :   :   Ask to play again
   :   :   :   :   :   If they want to play again:
   :   :   :   :   :   :   Play a new game
   :   :   :   :   :   If they are done playing:
   :   :   :   :   :   :   Done!
   :   :   :   :   If no player has won:
   :   :   :   :   :   switch players and play another turn
   */
// ====================================================================
//GLOBAL CONSTANTS
// ====================================================================
char PLAYER1[8] = "Player1";
char PLAYER2[8] = "Player2";
int MAXLEN = 20;
int MINLEN = 4;
// ====================================================================
//FUNCTION PROTOTYPES
// ====================================================================
// Display a welcome message and instructions.
void display_welcome();
// Clear the screen by printing many new lines
void clear();
// Prompt for feedback that a player is ready
bool prompt_for_payer(char player_name[]);
// Clear screen and print info about who is to be using the screen
void setup_maker_screen(char player_name[]);
// Clear screen and print info about who is to be using the screen
// Switch to guesser view.
// Display the scrambled word.
// Prompt for play or pass.
void setup_guesser_screen(char player_name[], char scrambled_word[]);
// Check if the secret word is compliant with game rules
bool validate_word_ok(char []);
// Get a word from the user and store it as lower case in the array argument
void get_word_standard(char []);
// Take a character array and scramble it according to the game rules of scrambling
void scramble_word(char []);
// Prompt the user for a yes or no boolean
bool prompt_bool();
//
// ====================================================================
//FUNCTION DEFINITIONS
// ====================================================================
// Display a welcome message and instructions.
void display_welcome()
{
	cout <<
		"Welcome to the game." <<
		"\nThis is a game for two players sharing a keyboard." <<
		"\nThe players take turns making a secret word." <<
		"\nWhile one player is entering a secret word, the other player is to look away." <<
		"\nThe word is then scrambled and displayed." <<
		"\nIf the other player can guess what secret the word was in one try, they get a point." <<
		"\nThis goes on until the first player to earn five points wins." <<
		"\n" <<
		"\nBe safe and have fun!\n\n" <<
		endl;
}
// Clear the screen by printing many new lines
void clear()
{
	for (int i = 0; i < 25; ++i)
	{
		cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
	}
}
// Prompt for feedback that a player is ready
bool prompt_for_payer(char player_name[])
{
	cout << "\n\n\n" << player_name << ": Are you ready?" << endl;
	return prompt_bool();
}
// Clear screen and print info about who is to be using the screen
void setup_maker_screen(char player_name[])
{
	while (!prompt_for_payer(player_name));
	clear();
	cout <<
		"\n" << player_name << "..." <<
		"\nMake a secret word for the other player to guess." <<
		"\n\n" <<
		endl;
}
// Clear screen and print info about who is to be using the screen
// Switch to guesser view.
// Display the scrambled word.
// Prompt for play or pass.
void setup_guesser_screen(char player_name[], char scrambled_word[])
{
	while (!prompt_for_payer(player_name));
	clear();
	cout <<
		"\n" << player_name << "..." <<
		"\nIt is time for you to guess what the secret word is." <<
		"\n\n" <<
		scrambled_word <<
		"\n\n" <<
		endl;
}
// Check if the secret word is compliant with game rules
bool validate_word_ok(char word[])
{
	int len; // This is the length of the word
	len = strlen(word);
	// The word must be between at least MINLEN and less that MAXLEN characters long
	if (len >= MINLEN && len < MAXLEN)
	{
		// If any char is not a letter, then reject the word
		for (int i = 0; i < len; ++i)
		{
			if (!isalpha(word[i])) {
				return false;
			}
		}
		// The word passed all checks
		return true;
	}
	// The word was not a valid length
	return false;
}
// Get a word from the user and store it as lower case in the array argument
void get_word_standard(char word[])
{
	int len; // This is the length of the word
	cin.get(word, MAXLEN, '\n');
	len = strlen(word);
	for (int i = 0; i < len; ++i)
	{
		// If this character is upper, replace it with lower version
		if (isupper(word[i]))
		{
			word[i] = tolower(word[i]);
		}
	}
}
// Take a character array and scramble it according to the game rules of scrambling
void scramble_word(char word[])
{
	int len; // The length of the word
	char swap; // Used as a carrier for swapping characters
	len = strlen(word);
	// If first letter is less than last letter:
	// Swap first and last letters.
	if (word[0] < word[len-1])
	{
		// Put first letter in placeholder.
		swap = word[0];
		// First letter copies value of last letter.
		word[0] = word[len-1];
		// Last letter copies value of placeholder.
		word[len-1] = swap;
	}
	// If the second letter is a vowel:
	// Swap second and third letters.
	if (word[1] == 'a' || word[1] == 'e' || word[1] == 'i' || word[1] == 'o' || word[1] == 'u')
	{
		// Put second letter in placeholder.
		swap = word[1];
		// Second letter copies value of last letter.
		word[1] = word[2];
		// Third letter copies value of placeholder.
		word[2] = swap;
	}
	// If the fourth letter is in range 'a' through 'k':
	// Swap third and fourth letters.
	if (word[3] >= 'a' && word[3] <= 'k' )
	{
		// Put third letter in placeholder.
		swap = word[2];
		// Third letter copies value of fourth letter.
		word[2] = word[3];
		// Fourth letter copies value of placeholder.
		word[3] = swap;
	}
	// If there are an even number of letters in the word:
	// Swap the two central letters.
	if ( (len % 2) == 0)
	{
		// Put (length/2)-1 letter in placeholder.
		swap = word[len/2];
		// Letter at (length/2)-1 copies value of length/2 letter.
		word[len/2] = word[(len/2)+1];
		// Letter at length/2 copies value of placeholder.
		word[(len/2)+1] = swap;
	}
}
bool prompt_bool()
{
	// This repeatedly prompts the user for a yes or no response until valid input is provided.
	int i = 0;
	char response;
	while (i=0, i++, i<5)
	{
		// Prompt user for boolean response.
		cout << "Please respond with 'y' (yes) or 'n' (no)." << endl;
		cin >> response;
		cin.ignore(100, '\n');
		// Process input and return true or false if input was valid.
		if (response=='y')
		{
			return true;
		} else if (response=='n')
		{
			return false;
		} else
		{
			// Invalid response. Inform user and try again.
			cout << "Invalid response..." << endl;
		}
	}
	// Give up because user has exceeded tries limit. Assume the assignment was graded.
	cout << "This is taking too long. I'll answer for you... 'y'." << endl;
	return true;
}

int main(){
	int score_p1 = 0; //Score of player 1
	int score_p2 = 0; //Score of player 2
	char player_name[8]; // Used to prompt fo player1 or player2
	char secret_word[MAXLEN]; // The secret word to be scrambled and guessed
	char scrambled_word[MAXLEN]; // Used to store the scrambled version of the secret word
	char guess_word[MAXLEN]; // Used to store the guesser's response
	bool p1_is_guesser = false; // Track which player is in guesser role

	bool running = true; // This is a boolean to switch off the main function looping.

	// Restart process as long as user wants. Loop condition "running" will be made false
	// if the user indicates they are finished after a final result is given.
	while (running)
	{
		// Reset score
		score_p1 = 0;
		score_p2 = 0;
		// Welcome the players to the game
		clear();
		display_welcome();
		while(score_p1 < 5 && score_p2 < 5)
		{
			// 	Play a turn
			// Determining the name of the active player...
			// This is now to be the name of the the secret word maker.
			if (p1_is_guesser){
				strcpy(player_name, PLAYER2);
			} else 
			{
				strcpy(player_name, PLAYER1);
			}
			// Switch to word-maker view.
			setup_maker_screen(player_name);
			// Clear the secret word in case there is old data from another round
			secret_word[0] = '\0'; 
			// Get the word. Make all characters lowercase.
			// Validate the entered word. Check that is longer than 3 letters.
			// If validation failed, keep trying.
			while (!validate_word_ok(secret_word))
			{
				get_word_standard(secret_word);
			}
			// Make a copy of the word for scrambling.
			strcpy(scrambled_word, secret_word);
			// Scramble the word.
			scramble_word(scrambled_word);
			// Determining the name of the active player...
			// This is now to be the name of the the guesser.
			if (p1_is_guesser){
				strcpy(player_name, PLAYER1);
			} else 
			{
				strcpy(player_name, PLAYER2);
			}
			// Clear the screen, but make note that word was accepted.
			clear();
			cout << "Secret word accepted!\n\n\n" << endl;
			// Switch to guesser view.
			// Display the scrambled word.
			setup_guesser_screen(player_name, scrambled_word);
			// Prompt for play or pass
			cout << "\nDo you want to make a guess?" << endl;
			if (prompt_bool())
				//If play is chosen:
			{
				// Prompt for guess. Make all characters lowercase.
				cout << "Enter your guess:" << endl;	
				get_word_standard(guess_word);
				// Check if guess matches original word.
				if (strcmp(guess_word, secret_word) == 0)
					// If guess was correct:
				{
					cout << "\n\nThat was correct! You scored a point!" << endl;
					// Add one point to current guesser score.
					if (p1_is_guesser){
						score_p1++;
					} else
					{
						score_p2++;
					}
				} else
				{
					cout << "\n\nSorry, that was not correct." << endl;
				}
			}
			cout << "\n\nThe secret word was: " << secret_word << endl;
			// Display the score
			cout << "\n\nThe score is:" <<
				"\n\t" << PLAYER1 << "\t" << score_p1 <<
				"\n\t" << PLAYER2 << "\t" << score_p2 <<
				endl;
			// Swap the player roles
			p1_is_guesser = !p1_is_guesser;
		}
		// If we exit the loop above, then a player has won!
		// Determining the name of the winning player
		if (score_p1 == 5){
			strcpy(player_name, PLAYER1);
		} else 
		{
			strcpy(player_name, PLAYER2);
		}
		// Congratulate the winner
		cout <<
			"\n\nCongratulations, we have a winner!\n" <<
			player_name << " wins!\n" << endl;
		// Game is over.
		// If they want to play again: Play a new game.
		// Ask user if they want to try again. This will kill main loop if false.
		cout << "\n" <<
			"Would you like to play again?" << endl;
		running = prompt_bool();
	}
	return 0;
}
