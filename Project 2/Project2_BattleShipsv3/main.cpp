#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

// Global Variables
int totGms = 0;                    // Global variable to track total games played
const int BSIZE = 10;              // Global constant for board size
bool dbgMod = false;               // Global debug flag

// Function Prototypes
void dispWel();
void initBrd(char board[][BSIZE]);
void dispBrd(const char board[][BSIZE], bool hidShp = true);
bool plcShp(char board[][BSIZE], int row, int col, int size, char dir);
void plcRnd(char board[][BSIZE]);
void plcMan(char board[][BSIZE], string plrNm);
bool isVldP(const char board[][BSIZE], int row, int col, int size, char dir);
bool mkMove(char board[][BSIZE], char dispB[][BSIZE], int row, int col);
bool isOver(const char board[][BSIZE]);
int cntShp(const char board[][BSIZE]);
void svStat(int moves, bool won);
void ldStat();
bool isHit(char cell);
bool isMiss(char cell);
int calcSc(int moves, bool won);
void dispSt();
void clrScr();

// Function with defaulted arguments
void dispMs(string msg, int delay = 1000, bool newln = true);

// Overloaded functions
void prtSc(int score);
void prtSc(int plrSc, int compSc);
void prtSc(const string& plrNm, int score);

// Pass by reference functions
void incCnt(int& cnt);
void updSt(int& wins, int& loss, bool won);
void swpVal(int& a, int& b);

// Pass by value functions
int addNum(int a, int b);
bool vldInp(int input);
char getRnd();

// Functions returning values
int getRow();
int getCol();
string getNm();

// Function returning boolean
bool askAgn();
bool isVCrd(int row, int col);
bool hasShp(const char board[][BSIZE], int row, int col);

// Single dimensioned array functions
void initSc(int scores[], int size);
void dispHi(const int scores[], int size);
int findMx(const int scores[], int size);

// Parallel arrays functions
void dispPs(const string names[], const int scores[], int size);
void sortPs(string names[], int scores[], int size);

// 2D array functions
void cpyBrd(const char src[][BSIZE], char dest[][BSIZE]);
bool cmpBrd(const char brd1[][BSIZE], const char brd2[][BSIZE]);

// STL Vector functions
void addHst(vector<string>& hist, const string& move);
void dispHs(const vector<string>& hist);
vector<int> genRnd(int count);
void sortVc(vector<int>& nums);

// Searching and sorting functions
void bubSrt(int arr[], int size);
void selSrt(int arr[], int size);
int linSch(const int arr[], int size, int tgt);
int binSch(const int arr[], int size, int tgt);

// Static Variables
static int gmCnt = 0;              // Static variable to count function calls

int main() {
    totGms++;                      // Using global variable
    
    // Single dimensioned arrays
    int hiSc[5] = {100, 85, 70, 55, 40};
    int plrMvs[100];               // Track player moves
    
    // Parallel arrays
    string plrNms[3] = {"Alice", "Bob", "Charlie"};
    int plrScs[3] = {95, 87, 76};
    
    // 2D arrays for two players
    char p1Brd[BSIZE][BSIZE];
    char p1Dsp[BSIZE][BSIZE];
    char p2Brd[BSIZE][BSIZE];
    char p2Dsp[BSIZE][BSIZE];
    
    // STL Vectors
    vector<string> mvHst;
    vector<int> rndNum = genRnd(10);
    
    dispWel();
    
    // Get player names
    string p1Nm = getNm();
    cout << "Player 1: " << p1Nm << endl;
    string p2Nm = getNm();
    cout << "Player 2: " << p2Nm << endl;
    
    // Initialize boards
    initBrd(p1Brd);
    initBrd(p1Dsp);
    initBrd(p2Brd);
    initBrd(p2Dsp);
    
    // Player 1 places ships
    cout << "\n" << p1Nm << ", place your ships!" << endl;
    plcMan(p1Brd, p1Nm);
    clrScr();
    
    // Player 2 places ships
    cout << "\n" << p2Nm << ", place your ships!" << endl;
    plcMan(p2Brd, p2Nm);
    clrScr();
    
    int mvCnt = 0;
    bool gmActv = true;
    bool p1Turn = true;
    
    // Demonstrate various concepts
    cout << "\n=== DEMONSTRATING PROGRAMMING CONCEPTS ===" << endl;
    
    // Pass by value
    int sum = addNum(5, 3);
    cout << "Pass by value - Sum of 5 and 3: " << sum << endl;
    
    // Pass by reference
    int cnt = 0;
    incCnt(cnt);
    cout << "Pass by reference - Counter after increment: " << cnt << endl;
    
    // Function returning boolean
    bool vldCrd = isVCrd(5, 5);
    cout << "Boolean return - Is (5,5) valid?: " << (vldCrd ? "Yes" : "No") << endl;
    
    // Defaulted arguments
    dispMs("Testing defaulted arguments", 500, true);
    
    // Function overloading
    prtSc(100);
    prtSc(85, 92);
    prtSc("Player1", 78);
    
    // Static variables
    static int gmId = 1000;
    gmId++;
    cout << "Game ID: " << gmId << endl;
    gmId++;
    cout << "Next Game ID: " << gmId << endl;
    
    // Single dimensioned arrays
    cout << "High Scores: ";
    dispHi(hiSc, 5);
    cout << "Max Score: " << findMx(hiSc, 5) << endl;
    
    // Parallel arrays
    cout << "\nPlayer Scores:" << endl;
    dispPs(plrNms, plrScs, 3);
    
    // Bubble Sort
    int tstAr1[] = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before Bubble Sort: ";
    for(int i = 0; i < 7; i++) cout << tstAr1[i] << " ";
    cout << endl;
    bubSrt(tstAr1, 7);
    cout << "After Bubble Sort: ";
    for(int i = 0; i < 7; i++) cout << tstAr1[i] << " ";
    cout << endl;
    
    // Selection Sort
    int tstAr2[] = {64, 25, 12, 22, 11};
    cout << "Before Selection Sort: ";
    for(int i = 0; i < 5; i++) cout << tstAr2[i] << " ";
    cout << endl;
    selSrt(tstAr2, 5);
    cout << "After Selection Sort: ";
    for(int i = 0; i < 5; i++) cout << tstAr2[i] << " ";
    cout << endl;
    
    // Linear Search
    int schAr[] = {10, 20, 30, 40, 50};
    int linRes = linSch(schAr, 5, 30);
    cout << "Linear Search for 30: " << (linRes != -1 ? "Found at index " + to_string(linRes) : "Not found") << endl;
    
    // Binary Search
    int binRes = binSch(schAr, 5, 40);
    cout << "Binary Search for 40: " << (binRes != -1 ? "Found at index " + to_string(binRes) : "Not found") << endl;
    
    // STL Vectors
    addHst(mvHst, "A1 - Hit");
    addHst(mvHst, "B2 - Miss");
    addHst(mvHst, "C3 - Hit");
    dispHs(mvHst);
    
    cout << "\n=== STARTING GAME ===" << endl;
    
    // Main game loop for two players
    while(gmActv) {
        string curPlr = p1Turn ? p1Nm : p2Nm;
        char (*tgtBrd)[BSIZE] = p1Turn ? p2Brd : p1Brd;
        char (*dspBrd)[BSIZE] = p1Turn ? p2Dsp : p1Dsp;
        
        cout << "\n" << curPlr << "'s turn!" << endl;
        cout << "Enemy board:" << endl;
        dispBrd(dspBrd, true);
        
        int row = getRow();
        int col = getCol();
        
        if(!isVCrd(row, col)) {
            cout << "Invalid coordinates!" << endl;
            continue;
        }
        
        if(dspBrd[row][col] != '~') {
            cout << "Already attacked this position!" << endl;
            continue;
        }
        
        mvCnt++;
        string mvStr = curPlr + " (" + to_string(row) + "," + to_string(col) + ")";
        
        if(mkMove(tgtBrd, dspBrd, row, col)) {
            cout << "HIT!" << endl;
            addHst(mvHst, mvStr + " - Hit");
        } else {
            cout << "MISS!" << endl;
            addHst(mvHst, mvStr + " - Miss");
        }
        
        if(isOver(tgtBrd)) {
            cout << curPlr << " wins! All enemy ships destroyed!" << endl;
            gmActv = false;
            break;
        }
        
        p1Turn = !p1Turn; // Switch turns
        
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        clrScr();
    }
    
    cout << "\nGame Over! Total moves: " << mvCnt << endl;
    
    // Ask to play again
    if(askAgn()) {
        cout << "Thanks for playing! Restart the program to play again." << endl;
    }
    
    // exit() function
    if(mvCnt > 100) {
        cout << "Game took too long, exiting..." << endl;
        exit(0);
    }
    
    return 0;
}

// Function with static variable
int getNxId() {
    static int gmId = 1000;        // Static variable retains value between calls
    return ++gmId;
}

// Pass by value example
int addNum(int a, int b) {
    return a + b;                  // Simple pass by value, returning value
}

// Pass by reference example
void incCnt(int& cnt) {
    cnt++;                         // Modifies original variable
}

// Function with defaulted arguments
void dispMs(string msg, int delay, bool newln) {
    cout << msg;
    if (newln) cout << endl;
    // Simulate delay (dummy implementation)
    for(int i = 0; i < delay/100; i++) {
        // Simple delay loop
    }
}

// Overloaded functions
void prtSc(int score) {
    cout << "Score: " << score << endl;
}

void prtSc(int plrSc, int compSc) {
    cout << "Player: " << plrSc << " | Computer: " << compSc << endl;
}

void prtSc(const string& plrNm, int score) {
    cout << plrNm << "'s Score: " << score << endl;
}

// More pass by reference functions
void updSt(int& wins, int& loss, bool won) {
    if(won) wins++;
    else loss++;
}

void swpVal(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// More pass by value functions
bool vldInp(int input) {
    return input >= 0 && input < BSIZE;
}

char getRnd() {
    return (rand() % 2 == 0) ? 'H' : 'V';
}

// Function returning boolean
bool isVCrd(int row, int col) {
    return (row >= 0 && row < BSIZE && col >= 0 && col < BSIZE);
}

bool askAgn() {
    char choice;
    cout << "Play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

bool hasShp(const char board[][BSIZE], int row, int col) {
    return board[row][col] == 'S';
}

bool isHit(char cell) {
    return cell == 'X';
}

bool isMiss(char cell) {
    return cell == 'O';
}

// Single dimensioned array functions
void initSc(int scores[], int size) {
    for(int i = 0; i < size; i++) {
        scores[i] = 0;
    }
}

void dispHi(const int scores[], int size) {
    cout << "High Scores: ";
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

// Parallel arrays functions
void dispPs(const string names[], const int scores[], int size) {
    for(int i = 0; i < size; i++) {
        cout << names[i] << ": " << scores[i] << endl;
    }
}

void sortPs(string names[], int scores[], int size) {
    // Bubble sort with parallel arrays
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(scores[j] < scores[j + 1]) {
                // Swap scores
                int tmpSc = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tmpSc;
                // Swap corresponding names
                string tmpNm = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tmpNm;
            }
        }
    }
}

// 2D array functions
void initBrd(char board[][BSIZE]) {
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            board[i][j] = '~';     // Water
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
                cout << "~ ";      // Hide ships from opponent
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void cpyBrd(const char src[][BSIZE], char dest[][BSIZE]) {
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

bool cmpBrd(const char brd1[][BSIZE], const char brd2[][BSIZE]) {
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            if(brd1[i][j] != brd2[i][j]) return false;
        }
    }
    return true;
}

// STL Vector functions
void addHst(vector<string>& hist, const string& move) {
    hist.push_back(move);
}

void dispHs(const vector<string>& hist) {
    cout << "Move History:" << endl;
    for(size_t i = 0; i < hist.size(); i++) {
        cout << i + 1 << ". " << hist[i] << endl;
    }
}

vector<int> genRnd(int count) {
    vector<int> nums;
    for(int i = 0; i < count; i++) {
        nums.push_back(rand() % 100);
    }
    return nums;
}

void sortVc(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}

// Searching and Sorting functions
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

void selSrt(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if(minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

int linSch(const int arr[], int size, int tgt) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == tgt) return i;
    }
    return -1;
}

int binSch(const int arr[], int size, int tgt) {
    int left = 0, right = size - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == tgt) return mid;
        if(arr[mid] < tgt) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Game-specific functions
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
    int shpSz[] = {5, 4, 3, 3, 2};  // Single dimensioned array
    
    for(int i = 0; i < 5; i++) {
        bool placed = false;
        while(!placed) {
            int row = rand() % BSIZE;
            int col = rand() % BSIZE;
            char dir = (rand() % 2 == 0) ? 'H' : 'V';
            placed = plcShp(board, row, col, shpSz[i], dir);
        }
    }
}

void plcMan(char board[][BSIZE], string plrNm) {
    string shpNms[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    int shpSz[] = {5, 4, 3, 3, 2};
    
    for(int i = 0; i < 5; i++) {
        bool placed = false;
        while(!placed) {
            cout << "\n" << plrNm << ", place your " << shpNms[i] << " (size " << shpSz[i] << ")" << endl;
            dispBrd(board, false);
            
            int row, col;
            char dir;
            
            cout << "Enter starting row (0-9): ";
            cin >> row;
            cout << "Enter starting column (0-9): ";
            cin >> col;
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> dir;
            
            if(isVCrd(row, col) && (dir == 'H' || dir == 'V')) {
                placed = plcShp(board, row, col, shpSz[i], dir);
                if(!placed) {
                    cout << "Invalid placement! Try again." << endl;
                }
            } else {
                cout << "Invalid input! Try again." << endl;
            }
        }
    }
    
    cout << "\nAll ships placed!" << endl;
    dispBrd(board, false);
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

bool mkMove(char board[][BSIZE], char dispB[][BSIZE], int row, int col) {
    if(board[row][col] == 'S') {
        board[row][col] = 'X';     // Hit
        dispB[row][col] = 'X';
        return true;
    } else if(board[row][col] == '~') {
        board[row][col] = 'O';     // Miss
        dispB[row][col] = 'O';
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

int cntShp(const char board[][BSIZE]) {
    int count = 0;
    for(int i = 0; i < BSIZE; i++) {
        for(int j = 0; j < BSIZE; j++) {
            if(board[i][j] == 'S') count++;
        }
    }
    return count;
}

int getRow() {
    int row;
    cout << "Enter row (0-9): ";
    cin >> row;
    return row;
}

int getCol() {
    int col;
    cout << "Enter column (0-9): ";
    cin >> col;
    return col;
}

string getNm() {
    string name;
    cout << "Enter player name: ";
    cin >> name;
    return name;
}

void dispWel() {
    cout << "================================" << endl;
    cout << "    TWO PLAYER BATTLESHIP GAME" << endl;
    cout << "================================" << endl;
}

// Additional missing functions
void svStat(int moves, bool won) {
    ofstream file("stats.txt", ios::app);
    if(file.is_open()) {
        file << "Moves: " << moves << ", Won: " << (won ? "Yes" : "No") << endl;
        file.close();
    }
}

void ldStat() {
    ifstream file("stats.txt");
    string line;
    if(file.is_open()) {
        while(getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}

int calcSc(int moves, bool won) {
    int baseSc = won ? 1000 : 0;
    return baseSc - moves;
}

void dispSt() {
    cout << "Total games played: " << totGms << endl;
    cout << "Game counter: " << gmCnt << endl;
}

void clrScr() {
    // Simple screen clear simulation
    for(int i = 0; i < 50; i++) {
        cout << endl;
    }
}