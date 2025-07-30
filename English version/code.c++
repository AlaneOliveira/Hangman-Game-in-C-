#include <iostream>
#include <string>
#include <cstdlib> // for system()
#include <cctype>  // for toupper(), isalpha()
using namespace std;

// Function to clear the screen depending on the OS
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #elif __linux__ || __APPLE__
        system("clear"); // Linux and macOS
    #else
        cout << "\n[Unable to clear the screen automatically]\n";
    #endif
}

// Array containing the hangman figure drawings for each mistake level
const string hangmanFigure[] = {
R"(  
  +---+
  |   |
      |
      |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
      |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
  |   |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========
)",
R"(  
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========
)"
};

int main() {
    int wins = 0;     // total number of wins
    int losses = 0;   // total number of losses
    char playAgain = 'y'; // controls the main game loop

    while (playAgain == 'y' || playAgain == 'Y') {
        string word, hint, letter;
        string guessedLetters; // stores letters already guessed
        int letterLength = 1;  // ensures the user inputs only one letter
        int attempts = 6;      // maximum number of allowed wrong attempts

        // Stylized title
        cout << "\033[1;35m";
        cout << "╔════════════════════════════╗\n";
        cout << "║      HANGMAN - START       ║\n";
        cout << "╚════════════════════════════╝\n";
        cout << "\033[0m\n";

        // Input the secret word
        cout << "Enter the secret word: ";
        getline(cin, word); // allows words with spaces

        // Input the hint for the player
        cout << "Enter a hint: ";
        getline(cin, hint);

        // Create a hidden version of the word with underscores
        string hiddenWord(word.size(), '_');

        clearScreen();

        // Main game loop
        while (attempts > 0 && hiddenWord != word) {
            cout << "Hint: " << hint << endl;
            cout << "Remaining attempts: " << attempts << endl;
            cout << hangmanFigure[6 - attempts] << endl;
            cout << "Hidden word: " << hiddenWord << endl;
            cout << "Guessed letters: " << guessedLetters << endl;

            // Letter input with validation
            do {
                cout << "Enter a letter (or ! to guess the full word): ";
                cin >> letter;

                // If the player wants to guess the whole word
                if (letter == "!") {
                    string fullGuess;
                    cin.ignore(); // clears buffer before getline
                    cout << "Enter the full word: ";
                    getline(cin, fullGuess);

                    if (fullGuess == word) {
                        hiddenWord = word;
                        break; // player guessed correctly
                    } else {
                        cout << "Wrong guess! You lose one attempt.\n";
                        attempts--;
                        break; // exit do-while and retry
                    }
                }
                // Check if input is a valid alphabet letter
                else if (!isalpha(letter[0])) {
                    cout << "Character '" << letter[0] << "' is not a valid letter (a-z, A-Z).\n";
                    letter = "";
                    continue;
                }

                // Ensure input is exactly one character
                if (letter.size() != letterLength) {
                    cout << "\nInvalid input! Please enter exactly " << letterLength << " letter(s).\n";
                    letter = "";
                    continue;
                }

                // Convert letter to uppercase
                char letterChar = toupper(letter[0]);

                // Check if the letter was already guessed
                if (guessedLetters.find(letterChar) != string::npos) {
                    cout << "You already guessed that letter. Try another.\n";
                    letter = "";
                    continue;
                } else {
                    guessedLetters += letterChar; // store valid guess
                    break;
                }

            } while (true);

            // Check if the guessed letter is in the word
            bool correct = false;
            char letterChar = toupper(letter[0]);

            for (int i = 0; i < word.size(); i++) {
                if (toupper(word[i]) == letterChar) {
                    hiddenWord[i] = word[i];
                    correct = true;
                }
            }

            if (!correct) {
                attempts--; // lose one attempt if letter not found
            }

            clearScreen(); // clear screen after each turn
        }

        // Check for win
        if (word == hiddenWord) {
            wins++;
            cout << "\033[1;32m";
            cout << "╔══════════════════════════════╗\n";
            cout << "║      CONGRATULATIONS!        ║\n";
            cout << "╚══════════════════════════════╝\n";
            cout << "\033[0m";
            cout << "\nWord: \033[1;33m" << word << "\033[0m" << endl;
        } else {
            losses++;
            cout << hangmanFigure[6] << endl; // show full figure
            cout << "\033[1;31m";
            cout << "╔══════════════════════╗\n";
            cout << "║       YOU LOST!      ║\n";
            cout << "╚══════════════════════╝\n";
            cout << "\033[0m";
            cout << "\nWord: \033[1;31m" << word << "\033[0m" << endl;
        }

        // Display stats for current session
        cout << "\nTotal wins: " << wins << endl;
        cout << "Total losses: " << losses << endl;

        // Ask the user if they want to play again
        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        cin.ignore(); // clear buffer
        clearScreen();

        if (playAgain == 'n' || playAgain == 'N') {
            cout << "Thanks for playing! See you next time.\n";
            cout << "\nTotal wins: " << wins << endl;
            cout << "Total losses: " << losses << endl;
        }
    }

    return 0;
}
