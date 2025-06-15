#include <iostream>
#include <string>

using namespace std;

// Global constant
const int SIZE = 5;                // Very small board

// Simple Function Prototypes
void initBrd(char board[][SIZE]);
void dispBrd(char board[][SIZE]);
bool mkMove(char board[][SIZE], int row, int col);
bool isOver(char board[][SIZE]);
string getNm();

// Pass by value
int add(int a, int b);

// Pass by reference  
void inc(int& x);

// Overloaded function
void show(int x);
void show(string s);

// Array function
int getMax(int arr[], int n);

int main() {
    // Simple array
    int nums[3] = {10, 20, 15};
    
    // Game board - only 5x5
    char brd[SIZE][SIZE];
    
    cout << "=== MINIMAL BATTLESHIP ===" << endl;
    
    // Get name
    string name = getNm();
    cout << "Hi " << name << "!" << endl;
    
    // Setup board
    initBrd(brd);
    
    // Place 2 ships manually
    brd[1][1] = 'S';
    brd[1][2] = 'S';
    brd[3][3] = 'S';
    
    // Demo concepts
    cout << "\n=== BASIC DEMO ===" << endl;
    
    // Pass by value
    int sum = add(5, 3);
    cout << "Sum: " << sum << endl;
    
    // Pass by reference
    int cnt = 0;
    inc(cnt);
    cout << "Count: " << cnt << endl;
    
    // Overloading
    show(42);
    show("Hello");
    
    // Array
    cout << "Max: " << getMax(nums, 3) << endl;
    
    cout << "\n=== GAME START ===" << endl;
    
    int moves = 0;
    bool done = false;
    
    // Simple game loop
    while(!done && moves < 10) {
        cout << "\nBoard:" << endl;
        dispBrd(brd);
        
        int row, col;
        cout << "Row (0-4): ";
        cin >> row;
        cout << "Col (0-4): ";
        cin >> col;
        
        if(row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << "Bad input!" << endl;
            continue;
        }
        
        moves++;
        
        if(mkMove(brd, row, col)) {
            cout << "HIT!" << endl;
        } else {
            cout << "MISS!" << endl;
        }
        
        if(isOver(brd)) {
            cout << "You win!" << endl;
            done = true;
        }
    }
    
    if(!done) {
        cout << "Too many moves!" << endl;
    }
    
    cout << "Total moves: " << moves << endl;
    
    return 0;
}

// Pass by value
int add(int a, int b) {
    return a + b;
}

// Pass by reference
void inc(int& x) {
    x++;
}

// Overloaded functions
void show(int x) {
    cout << "Number: " << x << endl;
}

void show(string s) {
    cout << "Text: " << s << endl;
}

// Array function
int getMax(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Board functions
void initBrd(char board[][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            board[i][j] = '~';
        }
    }
}

void dispBrd(char board[][SIZE]) {
    cout << "  ";
    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    for(int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool mkMove(char board[][SIZE], int row, int col) {
    if(board[row][col] == 'S') {
        board[row][col] = 'X'; // Hit
        return true;
    } else if(board[row][col] == '~') {
        board[row][col] = 'O'; // Miss
    }
    return false;
}

bool isOver(char board[][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(board[i][j] == 'S') {
                return false; // Still has ships
            }
        }
    }
    return true; // No ships left
}

string getNm() {
    string name;
    cout << "Name: ";
    cin >> name;
    return name;
}