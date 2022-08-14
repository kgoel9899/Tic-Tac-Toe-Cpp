// Tic-Tac-Toe Game

#include <bits/stdc++.h>
using namespace std;

const static char human = 'X';
const static char computer = 'O';
const static char nothing = '-';
vector<vector<char>> board;

// tells whether there is a tie or not (i.e. are there any moves left)
bool Tie() {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == '-') return false;
        }
    }
    return true;
}

// function that returns value according to who won the game
int Win() {
    // row check
    for(int i=0;i<3;i++) {
        char curr = board[i][0];
        if(curr == board[i][1] && curr == board[i][2]) {
            if(curr == human) return 20;
            else if(curr == computer) return -20;
        }
    }

    // column check
    for(int j=0;j<3;j++) {
        char curr = board[0][j];
        if(curr == board[1][j] && curr == board[2][j]) {
            if(curr == human) return 20;
            else if(curr == computer) return -20;
        }
    }

    // diagonal check
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if(board[0][0] == human) return 20;
        else if(board[0][0] == computer) return -20;
    }

    // diagonal check
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        if(board[2][0] == human) return 20;
        else if(board[2][0] == computer) return -20;
    }

    return 0;
}

// returns the best possible score out of all the possible combinations (backtracking)
int Minimax(bool human_chance, int depth) {
    int ans = Win();
    if(ans == 20) return ans - depth;
    else if(ans == -20) return ans + depth;
    else if(Tie()) return 0;

    if(human_chance) {
        int best = INT_MIN;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] == nothing) {
                    board[i][j] = human;
                    best = max(best, Minimax(!human_chance, depth + 1));
                    board[i][j] = nothing;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] == nothing) {
                    board[i][j] = computer;
                    best = min(best, Minimax(!human_chance, depth + 1));
                    board[i][j] = nothing;
                }
            }
        }
        return best;
    }
}

// decides next optimal move for computer
pair<int, int> DecideComputerMove() {
    pair<int, int> result;
    int best = INT_MAX;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == nothing) {
                board[i][j] = computer;
                int temp = Minimax(true, 0);
                board[i][j] = nothing;
                if(temp < best) {
                    best = temp;
                    result = {i, j};
                }
            }
        }
    }
    return result;
}

// prints the current status of board
void Print() {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    board.resize(3, vector<char>(3, nothing));

    // initially it is human's turn
    bool human_chance = 1;

    // loop until the game is tied or somebody has won
    while(true) {
        if(Tie()) break;

        if(Win()) break;

        cout << "The current status of the Tic-Tac-Toe Board is as follows:" << endl;
        cout << endl;

        Print();

        cout << endl;

        if(human_chance) {
            cout << "Human's Turn (X)" << endl;
            cout << "Enter the row and column where you want to place X" << endl;

            int row, col;
            cin >> row >> col;

            if(board[row][col] != nothing) {
                cout << endl;
                cout << "Invalid Move, Try Again" << endl;
                continue;
            }

            board[row][col] = human;
            cout << endl;
            human_chance = 0;
        } else {
            pair<int, int> move = DecideComputerMove();
            board[move.first][move.second] = computer;
            cout << "Computer optimally placed O at row = " << move.first << " and column = " << move.second << endl;
            cout << endl;
            human_chance = 1;
        }
    }

    // printing the final board
    cout << "The final status of the Tic-Tac-Toe Board is as follows:" << endl;
    cout << endl;
    Print();
    cout << endl;

    // printing the final result
    int final = Win();
    if(final > 0) cout << "Human Won!!" << endl;
    else if(final < 0) cout << "Computer Won!!" << endl;
    else cout << "The match has been tied!!" << endl;
}