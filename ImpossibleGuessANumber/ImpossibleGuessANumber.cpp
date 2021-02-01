// PROG 111 Trevor Tang 1/29/2021
#include <iostream>
#include <string>
#include <algorithm> // Used for my lowercase string function  
#include <cstdio> // For random numbers
#include <ctime> // For seeding 

using namespace std;

// --- FUNCTION PROTOTYPES --- //

string lowercase(string);
void mainProgram(int guesses = 3, int min = 1, int max = 10); // I used default arguments to simplify code if user does not want to input range
void checkGuess(int, int&, int&, int&);
int getMysteryNum(int, int, int);

// --------------------------- //

int main()
{
	// ------------- VARIABLE INITIALIZATION ---------------- //

	unsigned seed = time(0);
	srand(seed);

	string choice;
	bool goodInput = false; // Boolean used to check until good input is received where it will turn true 

	int max;
	int min;

	// ------------- PRE-ASSIGNING BEFORE GUESSING GAME STARTS ------ //

	while (!goodInput) {
		cout << "Welcome to the guessing number game!" << endl;
		cout << "Would you like to play with your own range?\n" << endl;
		cout << "(Y)es" << endl;
		cout << "(N)o" << endl;
		getline(cin, choice);
		choice = lowercase(choice); // Lowercases strings here 

		if (choice == "y" || choice == "yes") { // User wants their own defined range 
			int guesses = 3;
			goodInput = true;
			cout << "\nOk! Please only input positive integers" << endl;

			bool validMinAndMax = false; // I have this boolean here because I want to make sure the min is always less than the max before it continues 
			while (!validMinAndMax) {
				cout << "\nPlease input the minimum number first: " << endl;
				cin >> min;
				cout << "\nNow please input the maximum number: " << endl;
				cin >> max;

				// These if statements adjust the number of guesses according to the user's selected range 
				if (max - min >= 999) {
					guesses = 10;
					validMinAndMax = true;
				}
				else if (max - min >= 99) {
					guesses = 5;
					validMinAndMax = true;
				}
				else if (max - min + 1 < 10) {
					guesses = 1;
					validMinAndMax = true;
				}
				else { // else; use the default argument 3
					validMinAndMax = true;
				}
				if (min < 0 || max < 0) { // Checks if user inputted negative numbers 
					cout << "\nPlease try again, min or max is negative\n" << endl;
					validMinAndMax = false;
				}
				else if (min > max) { // Checks if the minimum number is greater than the maximum 
					cout << "\nPlease try again, min is greater than max\n" << endl;
					validMinAndMax = false;
				}
			}
			mainProgram(guesses, min, max);
		}

		else if (choice == "n" || choice == "no") { // User does not want a defined range 
			goodInput = true;
			mainProgram();
		}

		else { // Invalid input checker 
			cout << "\nSorry, I didn't receive valid input - please try again\n" << endl;
		}
	}
}

// ----------- GUESSING GAME MAIN PROGRAM ------------ //

void mainProgram(int guesses, int min, int max) {
	int guess;
	while (guesses > 0) {
		cout << "\nTry to guess the number from " << min << " to " << max << endl;
		cout << "You have " << guesses << " guesses remaining" << endl;
		cin >> guess;
		cout << "\n";
		checkGuess(guess, min, max, guesses); // Goes to checkGuess function 
	}

	// This statement includes a call to the getMysteryNum function so it can get a random mystery number not equal to guess
	cout << "Oh no! You ran out of guesses. From the final range of " << min << " to " << max << ", the mystery number was "
		<< getMysteryNum(min, max, guess) << "\n" << endl; // Game over statement
}

// Checks user guess and sees if they are "right" (hint hint, they are never right)
// This also serves to check if the user guess is also in our min to max range 
void checkGuess(int guess, int& min, int& max, int& guesses) {
	if (guess <= max && guess >= min) { // Makes sure our guess is within our min/max range
		guesses--; // Subtracts 1 from our guesses

		// The way I decide if it is too high or low is by seeing if guess is more or less than the middle number in between the min and max
		if (guess <= ((max + min) / 2)) {
			cout << guess << " is too low!\n" << endl;
			min = guess + 1;
		}
		else if (guess > ((max + min) / 2)) {
			cout << guess << " is too high!\n" << endl;
			max = guess - 1;
		}
	}
	// User is out of range? print these statements and return back to user input to have them try again 
	else if (guess > max) {
		cout << guess << " is higher than the maximum number of " << max << "! Try Again!\n" << endl;
	}
	else if (guess < min) {
		cout << guess << " is lower than the minimum number of " << min << "! Try Again!\n" << endl;
	}
}

// This function is used to print the mystery number
// Mystery number is a random number in our range min to max (inclusive) 
int getMysteryNum(int min, int max, int guess) {
	int mysteryNum = 0;
	do {
		mysteryNum = rand() % (max - min + 1) + min;
	} while (mysteryNum == guess); // This is needed because it is possible for the random num to accidently equal our guess

	return mysteryNum;
}

// This just lowercases the string so I can have simplified if statements for my 'choice' variable 
string lowercase(string str) {
	// Selects the length of what is being transformed, where to put the transformed string, and then lowercases it
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
