#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

// Global Variables
const int BSIZE = 8;               // Smaller board size
bool dbgMod = false;

// Basic Function Prototypes
void initBrd(char board[][BSIZE]);
void dispBrd(const char board[][BSIZE], bool hidShp = true);
bool plcShp(char board[][BSIZE], int row, int col, int size, char dir);
void plcRnd(char board[][BSIZE]);
bool isVldP(const char board[][BSIZE], int row, int col, int size, char dir);
bool mkMove(char board[][BSIZE], int row, int col);
bool isOver(const char board[][BSIZE]);
int getRow();
int getCol();
string getNm();
bool askAgn();
bool isVCrd(int row, int col);

// Pass by value functions
int addNum(int a, int b);
bool vldInp(int input);

// Pass by reference functions
void incCnt(int& cnt);

// Overloaded functions
void prtSc(int score);
void prtSc(const string& plrNm, int score);

// Single array functions
void dispHi(const int scores[], int size);
int findMx(const int scores[], int size);

// STL Vector functions
void addHst(vector<string>& hist, const string& move);
void dispHs(const vector<string>& hist);

// Basic sorting
void bubSrt(int arr[], int size);

int main() {
    // Simple arrays
    int hiSc[3] = {100, 85, 70};
    
    // Game boards - only one player vs computer
    char plrBrd[BSIZE][BSIZE];
    char compBrd[BSIZE][BSIZE];
    
    // STL Vector for history
    vector<string> mvHst;
    
    cout << "=== BASIC BATTLESHIP GAME ===" << endl;
    
    // Get player name
    string plrNm = getNm();
    cout << "Welcome " << plrNm << "!" << endl;
    
    // Initialize boards
    initBrd(plrBrd);
    initBrd(compBrd);
    
    // Place ships randomly for both
    cout << "Placing ships randomly..." << endl;
    plcRnd(plrBrd);
    plcRnd(compBrd);
    
    int mvCnt = 0;
    bool gmActv = true;
    bool plrTrn = true;
    
    // Demonstrate basic concepts
    cout << "\n=== BASIC CONCEPTS ===" << endl;
    
    // Pass by value
    int sum = addNum(3, 7);
    cout << "Sum: " << sum << endl;
    
    // Pass by reference
    int cnt = 5;
    incCnt(cnt);
    cout << "Counter: " << cnt << endl;
    
    // Function overloading
    prtSc(95);
    prtSc(plrNm, 88);
    
    // Arrays
    cout << "High Scores: ";
    dispHi(hiSc, 3);
    cout << "Max Score: " << findMx(hiSc, 3) << endl;
    
    // Sorting
    int tstAr[] = {64, 25, 12, 22, 11};
    cout << "Before Sort: ";
    for(int i = 0; i < 5; i++) cout << tstAr[i] << " ";
    cout << endl;
    bubSrt(tstAr, 5);
    cout << "After Sort: ";
    for(int i = 0; i < 5; i++) cout << tstAr[i] << " ";
    cout << endl;
    
    cout << "\n=== STARTING GAME ===" << endl;
    
    // Simple game loop
    while(gmActv && mvCnt < 50) {
        if(plrTrn) {
            cout << "\n" << plrNm << "'s turn!" << endl;
            cout << "Computer's board:" << endl;
            dispBrd(compBrd, true);
            
            int row = getRow();
            int col = getCol();
            
            if(!isVCrd(row, col)) {
                cout << "Invalid!" << endl;
                continue;
            }
            
            mvCnt++;
            string mvStr = plrNm + " (" + to_string(row) + "," + to_string(col) + ")";
            
            if(mkMove(compBrd, row, col)) {
                cout << "HIT!" << endl;
                addHst(mvHst, mvStr + " - Hit");
            } else {
                cout << "MISS!" << endl;
                addHst(mvHst, mvStr + " - Miss");
            }
            
            if(isOver(compBrd)) {
                cout << plrNm << " wins!" << endl;
                gmActv = false;
                break;
            }
        } else {
            // Computer turn - random move
            int row = rand() % BSIZE;
            int col = rand() % BSIZE;
            
            if(plrBrd[row][col] == 'X' || plrBrd[row][col] == 'O') {
                continue; // Already hit
            }
            
            mvCnt++;
            string mvStr = "Computer (" + to_string(row) + "," + to_string(col) + ")";
            
            if(mkMove(plrBrd, row, col)) {
                cout << "Computer HIT your ship at (" << row << "," << col << ")!" << endl;
                addHst(mvHst, mvStr + " - Hit");
            } else {
                cout << "Computer missed at (" << row << "," << col << ")" << endl;
                addHst(mvHst, mvStr + " - Miss");
            }
            
            if(isOver(plrBrd)) {
                cout << "Computer wins!" << endl;
                gmActv = false;
                break;
            }
        }
        
        plrTrn = !plrTrn;
    }
    
    cout << "\nGame Over! Total moves: " << mvCnt << endl;
    dispHs(mvHst);
    
    return 0;
}

// Pass by value
int addNum(int a, int b) {
    return a + b;
}

// Pass by reference
void incCnt(int& cnt) {
    cnt++;
}

bool vldInp(int input) {
    return input >= 0 && input < BSIZE;
}

// Overloaded functions
void prtSc(int score) {
    cout << "Score: " << score << endl;
}

void prtSc(const string& plrNm, int score) {
    cout << plrNm << "'s Score: " << score << endl;
}

// Array functions
void dispHi(const int scores[], int size) {
    for(int i = 0; i < size; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
}

int findMx(const int scores[], int size) {
    int max = scores[0];
    for(int i = 1; i < size; i++) {
        if(scores[i] > max) max = scores[i];
    }
    return max;
}

// Basic sorting
void bubSrt(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Board functions
void initBrd(char board[][BSIZE]) {
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            board[i][j] = '~';
        }
    }
}

void dispBrd(const char board[][BSIZE], bool hidShp) {
    cout << "  ";
    for(int i = 0; i < BSIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    for(int i = 0; i < BSIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < BSIZE; j++) {
            if(hidShp && board[i][j] == 'S') {
                cout << "~ ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool isVldP(const char board[][BSIZE], int row, int col, int size, char dir) {
    if(dir == 'H') {
        if(col + size > BSIZE) return false;
        for(int i = 0; i < size; i++) {
            if(board[row][col + i] != '~') return false;
        }
    } else {
        if(row + size > BSIZE) return false;
        for(int i = 0; i < size; i++) {
            if(board[row + i][col] != '~') return false;
        }
    }
    return true;
}

bool plcShp(char board[][BSIZE], int row, int col, int size, char dir) {
    if(!isVldP(board, row, col, size, dir)) return false;
    
    if(dir == 'H') {
        for(int i = 0; i < size; i++) {
            board[row][col + i] = 'S';
        }
    } else {
        for(int i = 0; i < size; i++) {
            board[row + i][col] = 'S';
        }
    }
    return true;
}

void plcRnd(char board[][BSIZE]) {
    int shpSz[] = {4, 3, 2}; // Only 3 ships
    
    for(int i = 0; i < 3; i++) {
        bool placed = false;
        while(!placed) {
            int row = rand() % BSIZE;
            int col = rand() % BSIZE;
            char dir = (rand() % 2 == 0) ? 'H' : 'V';
            placed = plcShp(board, row, col, shpSz[i], dir);
        }
    }
}

bool mkMove(char board[][BSIZE], int row, int col) {
    if(board[row][col] == 'S') {
        board[row][col] = 'X'; // Hit
        return true;
    } else if(board[row][col] == '~') {
        board[row][col] = 'O'; // Miss
    }
    return false;
}

bool isOver(const char board[][BSIZE]) {
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            if(board[i][j] == 'S') return false;
        }
    }
    return true;
}

bool isVCrd(int row, int col) {
    return (row >= 0 && row < BSIZE && col >= 0 && col < BSIZE);
}

bool askAgn() {
    char choice;
    cout << "Play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int getRow() {
    int row;
    cout << "Enter row (0-" << BSIZE-1 << "): ";
    cin >> row;
    return row;
}

int getCol() {
    int col;
    cout << "Enter column (0-" << BSIZE-1 << "): ";
    cin >> col;
    return col;
}

string getNm() {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    return name;
}

// Vector functions
void addHst(vector<string>& hist, const string& move) {
    hist.push_back(move);
}

void dispHs(const vector<string>& hist) {
    cout << "\nMove History:" << endl;
    for(size_t i = 0; i < hist.size() && i < 10; i++) { // Show only last 10
        cout << i + 1 << ". " << hist[i] << endl;
    }
}