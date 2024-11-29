#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;

class MemoryGame {
private:
    vector<int> board;
    vector<bool> revealed;
    int size;
    int pairs_found;
    int attempts;
    
    void clearScreen() {
        for(int i = 0; i < 50; i++) {
            cout << "\n";
        }
    }
    
    void displayBoard() {
        cout << "\nMemory Game Board:\n\n";
        for (int i = 0; i < size; i++) {
            if (revealed[i]) {
                cout << " " << board[i] << " ";
            } else {
                cout << " * ";
            }
            
            if ((i + 1) % 4 == 0) {
                cout << endl;
            }
        }
        cout << "\nPairs found: " << pairs_found << " | Attempts: " << attempts << endl;
        cout << "\nEnter -1 at any time to quit the game\n";
    }
    
    bool isValidInput(int position) {
        if (position == -1) return true; // Allow -1 as valid input for quitting
        return position >= 0 && position < size && !revealed[position];
    }
    
    int getValidInput(string prompt) {
        int position;
        while (true) {
            cout << prompt;
            if (cin >> position && isValidInput(position)) {
                return position;
            }
            if (position != -1) {
                cout << "Invalid input. Please enter a number between 0 and " << (size - 1) << " (-1 to quit)" << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
public:
    MemoryGame(int boardSize = 16) : size(boardSize), pairs_found(0), attempts(0) {
        board.resize(size);
        revealed.resize(size, false);
        
        for (int i = 0; i < size / 2; i++) {
            board[i * 2] = i + 1;
            board[i * 2 + 1] = i + 1;
        }
        
        random_device rd;
        mt19937 gen(rd());
        shuffle(board.begin(), board.end(), gen);
    }
    
    void play() {
        while (pairs_found < size / 2) {
            clearScreen();
            displayBoard();
            
            // Get first card
            int first = getValidInput("\nSelect first card (0-15) or -1 to quit: ");
            if (first == -1) {
                cout << "\nThanks for playing! Game ended.\n";
                return;
            }
            
            revealed[first] = true;
            clearScreen();
            displayBoard();
            
            // Get second card
            int second = getValidInput("\nSelect second card (0-15) or -1 to quit: ");
            if (second == -1) {
                cout << "\nThanks for playing! Game ended.\n";
                return;
            }
            
            revealed[second] = true;
            clearScreen();
            displayBoard();
            
            attempts++;
            
            if (board[first] == board[second]) {
                pairs_found++;
                cout << "\nMatch found! Press Enter to continue...";
            } else {
                cout << "\nNo match! Press Enter to continue...";
                revealed[first] = false;
                revealed[second] = false;
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        
        clearScreen();
        displayBoard();
        cout << "\nCongratulations! You've won in " << attempts << " attempts!" << endl;
    }
};

int main() {
    cout << "Welcome to Memory Game!\n";
    cout << "Find all matching pairs of numbers.\n";
    cout << "Enter -1 at any time to quit the game.\n\n";
    
    MemoryGame game;
    game.play();
    
    return 0;
}