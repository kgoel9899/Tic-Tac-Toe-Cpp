//Tic-Tac-Toe Board
#include<bits/stdc++.h>
#define ll long long
using namespace std;

char human = 'X';
char computer = 'O';
struct nextMove {
    int nextR;
    int nextC;
};
//tells whether there is tie or not (i.e. are there any moves left)
int tie(char** board) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == '-') {
                return 0;
            }
        }
    }
    return 1;
}
//function that returns value according to who won the game
int win(char** board) {
    //row check
    for(int i=0;i<3;i++) {
        char curr = board[i][0];
        if(curr == board[i][1] && curr == board[i][2]) {
            if(curr == human) {
                return 20;
            } else if(curr == computer){
                return -20;
            }
        }
    }
    //column check
    for(int j=0;j<3;j++) {
        char curr = board[0][j];
        if(curr == board[1][j] && curr == board[2][j]) {
            if(curr == human) {
                return 20;
            } else if(curr == computer){
                return -20;
            }
        }
    }
    //diagonal check
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if(board[0][0] == human) {
            return 20;
        } else if(board[0][0] == computer){
            return -20;
        }
    }
    //diagonal check
    if(board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        if(board[2][0] == human) {
            return 20;
        } else if(board[2][0] == computer){
            return -20;
        }
    }
    return 0;
}
//returns the best possible score out of all the possible combinations (backtracking)
int minimax(char** board, bool humanChance, int depth) {
    int ans = win(board);
    if(ans == 20) {
        return ans - depth;
    }
    if(ans == -20) {
        return ans + depth;
    }
    if(tie(board)) {
        return 0;
    }
    if(humanChance) {
        int maxi = INT_MIN;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] == '-') {
                    board[i][j] = 'X';
                    maxi = max(maxi, minimax(board, !humanChance, depth + 1));
                    board[i][j] = '-';
                }
            }
        }
        return maxi;
    } else {
        int mini = INT_MAX;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] == '-') {
                    board[i][j] = 'O';
                    mini = min(mini, minimax(board, !humanChance, depth + 1));
                    board[i][j] = '-';
                }
            }
        }
        return mini;
    }
}
//decides next optimal move for computer
nextMove decideMove(char** board) {
    nextMove result;
    if(tie(board)) {
        result.nextC = -1;
        result.nextR = -1;
        return result;
    }
    int mini = INT_MAX;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == '-') {
                board[i][j] = 'O';
                int temp = minimax(board, 1, 0);
                board[i][j] = '-';
                if(temp < mini) {
                    mini = temp;
                    result.nextR = i;
                    result.nextC = j;
                }
            }
        }
    }
    return result;
}
//prints the current status of board
void print(char** board) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    //fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char** board = new char*[3];
    for(int i=0;i<3;i++) {
        board[i] = new char[3];
        for(int j=0;j<3;j++) {
            board[i][j] = '-';
        }
    }
    //position where human wants to place X
    int row, col;
    //initially it is human's turn
    int humanCh = 1;
    //loop until the game is tied or somebody has won
    while(true) {
        if(tie(board)) {
            break;
        }
        if(win(board)) {
            break;
        }
        cout << "The current status of the Tic-Tac-Toe Board is as follows:-" << endl;
        cout << endl;
        print(board);
        cout << endl;
        if(humanCh) {
            cout << "Human's Turn (X)" << endl;
            cout << "Enter the row and column where you want to place X" << endl;
            cin >> row >> col;
            if(board[row][col] != '-') {
                cout << endl;
                cout << "Invalid Move, Try Again" << endl;
                continue;
            }
            board[row][col] = 'X';
            cout << endl;
            humanCh = 0;
        } else {
            nextMove nMove = decideMove(board);
            board[nMove.nextR][nMove.nextC] = 'O';
            cout << "Computer optimally placed O at row " << nMove.nextR << " and column " << nMove.nextC << endl;
            cout << endl;
            humanCh = 1;
        }
    }
    //printing the final board
    cout << "The current status of the Tic-Tac-Toe Board is as follows:-" << endl;
    cout << endl;
    print(board);
    cout << endl;
    //printing the final result
    if(win(board) > 0) {
        cout << "Human Won!!" << endl;
    } else if(win(board) < 0) {
        cout << "Computer Won!!" << endl;
    } else {
        cout << "The match has been tied!!" << endl;
    }
    //deleting the dynamically allocated memory
    for(int i=0;i<3;i++) {
        delete [] board[i];
    }
    delete [] board;
    return 0;
}