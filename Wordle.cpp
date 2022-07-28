// Wordle.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <windows.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

bool showWord {false};

void fixList() {	// Deletes copies of words in our list: WORKS

	vector<std::string> words;	// Create a vector that can be sorted
	vector<std::string> words2;

	std::ifstream file("FiveLetterWords.txt");
	std::string line;

	while (std::getline(file, line)) {	// Move through the file, adding each line to the vector
		std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::toupper(c); }); // Make it uppercase
		words.push_back(line);
		words2.push_back(line);
	}
	sort(words.begin(), words.end());	// Sort the vector
	sort(words2.begin(), words2.end());

	for (int i = 0; i < words.size(); i++) {
		int copies = 0;
		for (int j = 0; j < words2.size(); j++) {
			if (words.at(i) == words2.at(j)) {
				copies++;
				if (copies > 1) {
					words2.at(j) = "";
				}
			}
		}
	}

	std::ofstream out("FiveLetterWords.txt");
	std::ostream_iterator<std::string> iter(out, "\n");	// Create a vector iterator
	std::copy(words2.begin(), words2.end(), iter);	// Write the sorted vector to the text file

	return;
}

void displayAllWords() {	// Displays all words in our list: WORKS

	std::ifstream file("FiveLetterWords.txt");
	std::string line;

	cout << "\n";
	while (std::getline(file, line)) {	// Move through the file, adding each line to the vector
		cout << line << "\n";
		Sleep(50);
	}
	return;
}

void sort() {	// Sorts and capitalizes all words in the file: WORKS

	vector<std::string> words;	// Create a vector that can be sorted

	std::ifstream file("FiveLetterWords.txt");
	std::string line;

	while (std::getline(file, line)) {	// Move through the file, adding each line to the vector
		if (!line.empty()) {
			std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { return std::toupper(c); }); // Make it uppercase
			words.push_back(line);
		}
	}
	sort(words.begin(), words.end());	// Sort the vector

	std::ofstream out("FiveLetterWords.txt");
	std::ostream_iterator<std::string> iter(out, "\n");	// Create a vector iterator
	std::copy(words.begin(), words.end(), iter);	// Write the sorted vector to the text file

	return;
}

std::string getWord() {	// Gets a random word for the user to guess: WORKS
	
	vector<std::string> words;	// Create a vector that can be sorted

	std::ifstream file("FiveLetterWords.txt"); // 599 words
	std::string line;
	srand(time(0));	// Set a new "seed" for randomness
	int randomNumber = rand() % 600;	// Picks a random number

	while (std::getline(file, line)) {	// Move through the file, adding each line to the vector
		words.push_back(line);
	}

	std::string randomWord = words.at(randomNumber);	// Gets a random word based on random number
	return randomWord;
}

void wordle(std::string word) {	// Here is where we play the actual game: WORKS
	
	std::string displayed = "-----";
	std::string guessedWord;
	int tries = 6;

	while (displayed.compare(word) != 0) {	// While displayed is NOT the word
		if (tries == 0) {
			break;
		}
		else {
			cout << "You have: " << tries << " left";
			cout << "\n";
			cout << displayed << "\n";
			cout << "Guess a word: ";
			cin >> guessedWord;
			while (guessedWord.size() != 5) {
				cout << "\n";
				cout << "Word MUST be 5 letters long! No more, no less!\nTry again: ";
				cin >> guessedWord;
			}
			std::transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(), [](unsigned char c) { return std::toupper(c); }); // Make it uppercase
			for (int i = 0; i < 5; i++) {
				if (guessedWord.at(i) == word.at(i)) {
					displayed.at(i) = word.at(i);
				}
				else {
					// Do nothing, no letters
				}
			}
			for (int i = 0; i < 5; i++) {
				int used = 0;
				for (int j = 0; j < 5; j++) {
					if ((guessedWord.at(i) == word.at(j))) {
						if (displayed.at(j) == '-') {
							used++;
						}
					}
					else {
						// Do nothing
					}
				}
				if (used > 0) {
					cout << guessedWord.at(i) << " is used " << used << " more times\n";
				}
			}
		}
		tries--;
	}
	if (displayed.compare(word) == 0) {
		tries--;
		cout << "CONGRATULATIONS! You guessed your word with " << tries + 1 << " guesses left. Good Job!!!";
	}
	else {
		cout << "Sorry! You are all out of guesses! Your word was: " << word;
	}
	return;
}

void getReady() {	// Get the game ready for the player: WORKS

	printf("Let me get a word ready\n");
	for (int i = 0; i < 10; i++) {
		printf(".");
		Sleep(200);
	}
	sort();
	std::string wordToGuess = getWord();
	if (showWord) {
		cout << "\n" << wordToGuess << "\n";
	}
	//cout << "\n" << wordToGuess << "\n";	// GET RID OF THIS
	cout << "\n" << "\n";
	printf("Your word is ready, good luck!\n");
	wordle(wordToGuess);
	cout << "\n" << "\n" << "\n" << "\n" << "\n";
	return;
}

int main() {

	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 700;
	fontex.dwFontSize.X = 36;
	fontex.dwFontSize.Y = 36;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);  // Gives a borderless window

	while (true) {
		int startExit;
		cout << "Welcome to (my version) of Wordle! What would you like to do?\n1: Guess a Word\n2: Exit\nYour Choice: ";
		cin >> startExit;

		while (cin.fail()) {
			cout << "Please Enter A Number..." << "\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> startExit;
		}
		if (startExit == 1) {   // Look up
			cout << "" << "\n";
			getReady();
			cout << "" << "\n";
		}
		else if (startExit == 2) {	// Exit
			cout << "" << "\n";
			printf("Ok, well, Goodbye!");
			cout << "" << "\n";
			exit(0);
		}
		else if (startExit == 6386) {
			int developer;
			cout << "\n";
			cout << "What in the world do you want?\n1: Re-sort and Cap words\n2: Display all words\n3: Show word each game\n4: Fix word list\n5: Choose the word\nChoice: ";
			cin >> developer;
			if (developer == 1) {	// Re-sort and Cap
				sort();
				printf("\nDone\n");
				cout << "\n";
			}
			else if (developer == 2) {	// Print all words
				displayAllWords();
				printf("\nDone\n");
				cout << "\n";
			}
			else if (developer == 3) {	// Display word
				showWord = true;
				cout << "\n" << "\n";
			}
			else if (developer == 4) {
				fixList();
				printf("\nDone\n");
				cout << "\n";
			}
			else if (developer == 5) {
				std::string chosenWord;
				cout << "\n";
				cout << "What's the word: ";
				cin >> chosenWord;
				std::transform(chosenWord.begin(), chosenWord.end(), chosenWord.begin(), [](unsigned char c) { return std::toupper(c); }); // Make it uppercase
				wordle(chosenWord);
			}
		}
		else if (startExit == 69) {
			cout << "" << "\n";
			printf("Nice..");
			cout << "" << "\n";
		}
		else if (startExit == 420) {
			cout << "\n";
			while (true) {
				printf("Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day Smoke Weed Every Day");
				Sleep(5);
				cout << "\n";
			}
		}
		else {
			cout << " " << "\n";
			printf("Invalid Input! Try Again...\n");
			cout << " " << "\n";
		}
	}
}