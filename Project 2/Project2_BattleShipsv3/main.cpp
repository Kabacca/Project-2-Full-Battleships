//System Libraries
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function Prototypes - Now with board size parameters
void dispWel();
void initBrd(vector<vector<char>>& board, int size);
void dispBrd(const vector<vector<char>>& board, bool hidShp = true);
bool plcShp(vector<vector<char>>& board, int row, int col, int size, char dir, int brdSize);
void plcRnd(vector<vector<char>>& board, int brdSize);
void plcMan(vector<vector<char>>& board, string plrNm, int brdSize);
bool isVldP(const vector<vector<char>>& board, int row, int col, int size, char dir, int brdSize);
bool mkMove(vector<vector<char>>& board, vector<vector<char>>& dispB, int row, int col);
bool isOver(const vector<vector<char>>& board);
int cntShp(const vector<vector<char>>& board);
void svStat(int moves, bool won);
void ldStat();
bool isHit(char cell);
bool isMiss(char cell);
int calcSc(int moves, bool won);
void dispSt(int totGms, int gmCnt);
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
bool vldInp(int input, int boardSize);
char getRnd();

// Functions returning values
int getRow(int boardSize);
int getCol(int boardSize);
string getNm();

// Function returning boolean
bool askAgn();
bool isVCrd(int row, int col, int boardSize);
bool hasShp(const vector<vector<char>>& board, int row, int col);

// Single dimensioned array functions
void initSc(int scores[], int size);
void dispHi(const int scores[], int size);
int findMx(const int scores[], int size);

// Parallel arrays functions
void dispPs(const string names[], const int scores[], int size);
void sortPs(string names[], int scores[], int size);

// 2D array functions (now using vectors but keeping same concepts)
void cpyBrd(const vector<vector<char>>& src, vector<vector<char>>& dest);
bool cmpBrd(const vector<vector<char>>& brd1, const vector<vector<char>>& brd2);

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

int main() {
    // Local constants instead of global variables
    const int BSIZE = 10;              // Local constant for board size
    bool dbgMod = false;               // Local debug flag
    int totGms = 1;                    // Local variable to track total games played
    
    // Static Variables - demonstrating static concept
    static int gmCnt = 0;              // Static variable to count function calls
    gmCnt++;
    
    // Single dimensioned arrays
    int hiSc[5] = {100, 85, 70, 55, 40};
    int plrMvs[100];               // Track player moves
    
    // Parallel arrays
    string plrNms[3] = {"Alice", "Bob", "Charlie"};
    int plrScs[3] = {95, 87, 76};
    
    // 2D arrays for two players - now using dynamic vectors
    vector<vector<char>> p1Brd(BSIZE, vector<char>(BSIZE));
    vector<vector<char>> p1Dsp(BSIZE, vector<char>(BSIZE));
    vector<vector<char>> p2Brd(BSIZE, vector<char>(BSIZE));
    vector<vector<char>> p2Dsp(BSIZE, vector<char>(BSIZE));
    
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
    initBrd(p1Brd, BSIZE);
    initBrd(p1Dsp, BSIZE);
    initBrd(p2Brd, BSIZE);
    initBrd(p2Dsp, BSIZE);
    
    // Player 1 places ships
    cout << "\n" << p1Nm << ", place your ships!" << endl;
    plcMan(p1Brd, p1Nm, BSIZE);
    clrScr();
    
    // Player 2 places ships
    cout << "\n" << p2Nm << ", place your ships!" << endl;
    plcMan(p2Brd, p2Nm, BSIZE);
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
    bool vldCrd = isVCrd(5, 5, BSIZE);
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
        vector<vector<char>>& tgtBrd = p1Turn ? p2Brd : p1Brd;
        vector<vector<char>>& dspBrd = p1Turn ? p2Dsp : p1Dsp;
        
        cout << "\n" << curPlr << "'s turn!" << endl;
        cout << "Enemy board:" << endl;
        dispBrd(dspBrd, true);
        
        int row = getRow(BSIZE);
        int col = getCol(BSIZE);
        
        if(!isVCrd(row, col, BSIZE)) {
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
    
    // Pass local variables to display stats
    dispSt(totGms, gmCnt);
    
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
bool vldInp(int input, int boardSize) {
    return input >= 0 && input < boardSize;
}

char getRnd() {
    return (rand() % 2 == 0) ? 'H' : 'V';
}

// Function returning boolean
bool isVCrd(int row, int col, int boardSize) {
    return (row >= 0 && row < boardSize && col >= 0 && col < boardSize);
}

bool askAgn() {
    char choice;
    while (true) {
        cout << "Play again? (y/n): ";
        cin >> choice;
        choice = toupper(choice);  // Convert to uppercase
        
        if (choice == 'Y') {
            return true;
        } else if (choice == 'N') {
            return false;
        } else {
            cout << "Please enter Y or N." << endl;
        }
    }
}

bool hasShp(const vector<vector<char>>& board, int row, int col) {
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

// 2D array functions - now using vectors but keeping same concepts
void initBrd(vector<vector<char>>& board, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            board[i][j] = '~';     // Water
        }
    }
}

void dispBrd(const vector<vector<char>>& board, bool hidShp) {
    int size = board.size();
    cout << "  ";
    for(int i = 0; i < size; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    for(int i = 0; i < size; i++) {
        cout << i << " ";
        for(int j = 0; j < size; j++) {
            if(hidShp && board[i][j] == 'S') {
                cout << "~ ";      // Hide ships from opponent
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void cpyBrd(const vector<vector<char>>& src, vector<vector<char>>& dest) {
    int size = src.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

bool cmpBrd(const vector<vector<char>>& brd1, const vector<vector<char>>& brd2) {
    int size = brd1.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
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

// Game-specific functions - updated to use vectors and pass boardSize
bool isVldP(const vector<vector<char>>& board, int row, int col, int size, char dir, int brdSize) {
    if(dir == 'H') {
        if(col + size > brdSize) return false;
        for(int i = 0; i < size; i++) {
            if(board[row][col + i] != '~') return false;
        }
    } else {
        if(row + size > brdSize) return false;
        for(int i = 0; i < size; i++) {
            if(board[row + i][col] != '~') return false;
        }
    }
    return true;
}

bool plcShp(vector<vector<char>>& board, int row, int col, int size, char dir, int brdSize) {
    if(!isVldP(board, row, col, size, dir, brdSize)) return false;
    
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

void plcRnd(vector<vector<char>>& board, int brdSize) {
    int shpSz[] = {5, 4, 3, 3, 2};  // Single dimensioned array
    
    for(int i = 0; i < 5; i++) {
        bool placed = false;
        while(!placed) {
            int row = rand() % brdSize;
            int col = rand() % brdSize;
            char dir = (rand() % 2 == 0) ? 'H' : 'V';
            placed = plcShp(board, row, col, shpSz[i], dir, brdSize);
        }
    }
}

void plcMan(vector<vector<char>>& board, string plrNm, int brdSize) {
    string shpNms[] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    int shpSz[] = {5, 4, 3, 3, 2};
    
    for(int i = 0; i < 5; i++) {
        bool placed = false;
        while(!placed) {
            cout << "\n" << plrNm << ", place your " << shpNms[i] << " (size " << shpSz[i] << ")" << endl;
            dispBrd(board, false);
            
            int row, col;
            char dir;
            
            cout << "Enter starting row (0-" << (brdSize-1) << "): ";
            cin >> row;
            cout << "Enter starting column (0-" << (brdSize-1) << "): ";
            cin >> col;
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> dir;
            
            if(isVCrd(row, col, brdSize) && (dir == 'H' || dir == 'V')) {
                placed = plcShp(board, row, col, shpSz[i], dir, brdSize);
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

bool mkMove(vector<vector<char>>& board, vector<vector<char>>& dispB, int row, int col) {
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

bool isOver(const vector<vector<char>>& board) {
    int size = board.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == 'S') return false;
        }
    }
    return true;
}

int cntShp(const vector<vector<char>>& board) {
    int count = 0;
    int size = board.size();
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == 'S') count++;
        }
    }
    return count;
}

int getRow(int boardSize) {
    int row;
    cout << "Enter row (0-" << (boardSize-1) << "): ";
    cin >> row;
    return row;
}

int getCol(int boardSize) {
    int col;
    cout << "Enter column (0-" << (boardSize-1) << "): ";
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

// Additional missing functions - updated to accept parameters
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

void dispSt(int totGms, int gmCnt) {
    cout << "Total games played: " << totGms << endl;
    cout << "Game counter: " << gmCnt << endl;
}

void clrScr() {
    // Simple screen clear simulation
    for(int i = 0; i < 50; i++) {
        cout << endl;
    }
}
