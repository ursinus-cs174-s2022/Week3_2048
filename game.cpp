#include <iostream>
#include <stdio.h>
#include "randutils.h"
using namespace std;

#define BOARD_LEN 4

int board[BOARD_LEN][BOARD_LEN];
    
    
/**
 * Print out the board in text, making enough space to 
 * accommodate 4 digit numbers like 2048
 */
void printBoard() {
    for (int i = 0; i < BOARD_LEN; i++) {
        printf("=========================\n");
        for (int j = 0; j < BOARD_LEN; j++) {
            if (board[i][j] > 0) {
                printf("|%4d ", board[i][j]);
            }
            else {
            printf("|     ");
            }
        }
        printf("|\n");
    }
    printf("=========================\n\n");
}
    
/**
 * Clear the board by putting all zeroes into it
 */
void clearBoard() {
    for (int i = 0; i < BOARD_LEN; i++) {
        for (int j = 0; j < BOARD_LEN; j++) {
            board[i][j] = 0;
        }
    }   
}

/**
 * Add a single random number that's either a 2 or a 4
 * ***OR do nothing if there are no open spaces***
 */


/**
 * Add a single random number that's either a 2 or a 4
 */
void addRandom() {
    // TODO: This will infinite loop if the board is full!!
    bool finished = false;
    while (!finished) {
        int row = int(BOARD_LEN*randfloat()*0.99);
        int col = int(BOARD_LEN*randfloat()*0.99);
        if (board[row][col] == 0) {
            int num = 2;
            if (randfloat() > 0.5) {
                num = 4;
            }
            board[row][col] = num;
            finished = true;
        }
    }
}
    
/**
 * Initialize a grid with some amount of random numbers that
 * are either 2s or 4s
 * @param numInitial How many numbers to place
 */
void makeRandomGrid(int numInitial) {
    clearBoard();
    for (int i = 0; i < min(numInitial, 16); i++) {
        addRandom();
    }
}
    
/**
 * Move all of the nonzero entries over to the right so there
 * are no gaps and everything is touching the right
 */
int moveRight(){
    printBoard();
    for(int i =0; i<BOARD_LEN; i++){
        for(int j=0; j<BOARD_LEN-2; j++){
            int currspace = board[i][j];
            if(board[i][j+1] == NULL){
                board[i][j+1] = currspace;
                currspace = NULL;
            }
        }
    }
    printBoard();
    return 1;
}
    
void moveDown() {
    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j < 4; j++) {
            int value = board[i][j];
            if (value != 0) {
                int k = i;
                while (k + 1 < 4 && board[k + 1][j] == 0) {
                    board[k][j] = 0;
                    board[k + 1][j] = value;
                    k += 1;
                }
            }
        }
    }
}
    
/**
 * Combine all adjacent numbers that are the same in a particular row
 * There are three cases
 * 1) There are two contiguous.  In this case, put a zero in the place
 *    of the first one, and replace the second one with twice its value
 * 2) There are three contiguous.  In this case, put a zero in the first place,
 *    keep the original value in the second place, and put twice the original
 *    value in the third place
 * 3) There are 4 contiguous.  Put zeros in the first two, and put twice
 *    the value in the second two
 */
void combineRight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(board[i][j] == board[i][j+1] && board[i][j+2] == board[i][j+3]){
              board[i][j+1] = board[i][j] * 2;
              board[i][j] = 0;
              board[i][j+3] = board[i][j+2] * 2;
              board[i][j+2] = 0;
            }
            if(board[i][j] == board[i][j+1] && board[i][j+2] == board[i][j+1]){
                board[i][j] = 0;
                board[i][j+2] = board[i][j+1] * 2;
            }
            if(board[i][j] == board[i][j+1]){
                board[i][j+1] = board[i][j] * 2;
                board[i][j] = 0;
            }
        }
    } 
}
    
    
/**
 * Combine all adjacent numbers that are the same in a particular column
 * There are three cases
 * 1) There are two in a row.  In this case, put a zero in the place
 *    of the first one, and replace the second one with twice its value
 * 2) There are three in a row.  In this case, put a zero in the first place,
 *    keep the original value in the second place, and put twice the original
 *    value in the third place
 * 3) There are 4 in a row.  Put zeros in the first two, and put twice
 *    the value in the second two
 */
void combineDown() {
        for(int i = 0; i < BOARD_LEN; i++){
            int count = 0;
            int val = -1;
            for(int j = 0; j < BOARD_LEN; j++){
                if(board[j][i] == val){
                    count++;
                }
            if(board[j][i] != val || j == BOARD_LEN){
                if(count > 1){
                    if(count == 2){
                        board[j-1][i] = 0;
                        board[j][i] = val * 2;
                    }
                    else if(count == 3){
                        board[j-2][i] = 0;
                        board[j][i] = val * 2;
                    }
                    else if(count == 4){
                        board[j-3][i] = 0;
                        board[j-2][i] = 0;
                        board[j-1][i] = val * 2;
                        board[j][i] = val * 2;
                    }
                }
                val = board[j][i];
                count = 0;
            }
        }   
    }
}
    
void flipVertically() {
    int tempBoard[4][4];
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempBoard[j][i] = board[3-j][i];
        }
    }
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[j][i] = tempBoard[j][i];
        }
    }
}

void flipHorizontally() {
    int tempBoard[4][4];
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempBoard[i][j] = board[i][3-j];
        }
    }
    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[j][i] = tempBoard[j][i];
        }
    }
}
    
bool isFull() {

    int count = 0;
    bool result = false;

    for(int i = 0; i <= 4; i++){
        for (int j = 0; j <= 4; j++){

            if(board[i][j] == 0){
                count = count + 1;
            }
        }
    } 
    if(count > 15){
        result = true;
    }
    // TODO: Group 7 fills this in
    return result; // TODO: This is a dummy value
}
    
/**
 * Check that the board is full *and* it is not possible
 *            to combine any adjacent elements
 * @return true if the game is over, false otherwise
 */
bool isOver() {
    // TODO: Group 7 fills this in
    return false; // TODO: This is a dummy value
}
    
/**
 * Repeat the following until the board is full
 * 1) Print the board
 * 2) Have the user choose a direction: 
 *        a Left, d right, w up, s down
 * 3) Move the board in that direction and combine things as necessary
 * 4) Print the resulting board
 * 5) If the board is not full, put a new random 2 or 4 on the board
 */
void playGame() {
// Repeat the following until the board is over
    addRandom();
    addRandom();
    while(!isOver()) {
        // 1) Print the board
        printBoard();
        // 2) Have the user choose a direction:    a Left, d right, w up, s down
        char dir;
        cin >> dir;
        // 3) Move the board in that direction and combine things as necessary
        if (dir == 'a') {
            // Move left
        }
        else if (dir == 'd') {
            // Move right
        }
        else if (dir == 's') {
            // Move down
            //moveDown();
            //combineDown();
        }
        else if (dir == 'w') {
            // Move up
            flipVertically();
            moveDown();
            combineDown();
            flipVertically();
        }
        // 4) Print the resulting board
        printBoard();
        // 5) If the board is not full, put a new random 2 or 4 on the board
        if (!isFull()) {
            cout << "Trying to add something random \n";
            addRandom();
        }
    }
}
    
/**
 * You can use this for debugging; put any numbers you like in
 * the board
 */
void makeMyOwnGrid() {
    clearBoard();
    // TODO: Fill this in with your own custom board
    board[0][0] = 4;
    board[1][3] = 2;
    board[2][1] = 2;
}
    
int main() {
    // TODO: Debugging/test code here
    makeMyOwnGrid();
    moveRight();
    return 0;
}