// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
Bingo::Bingo(){
    m_trackCols = nullptr;  // use this to keep track & check if a column is complete
    m_trackRows = nullptr;  // use this to keep track & check if a row is complete
    m_helper = nullptr;    // the array to store cells in which index numbers are the cell values
    m_helperSize = 0;
    m_card = nullptr;     // the 2d structure to store card information
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;   // min value in a cell
    m_maxBallVal = 0;   // max value in a cell
}

Bingo::Bingo(int rows, int columns, int min, int max){
    // requirements: 2-15 rows, 5 columns, min at least 11, max at most 85,
    //  max - min must div by 5
    if (2 > rows || rows > 15 ){
        cout << "Invalid number of rows. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;   
    } else if (columns != 5){
        cout << "Invalid number of columns. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;   
    } else if (min < 11 || max > 85){
        cout << "Invalid number of balls. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;   
    } else if ((max - min) % 5 != 0){
        cout << "Invalid number of balls. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr; 
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;  
    } else {
        cout << "Initialization successfull. Creating bingo object..." << endl;
        m_trackCols = new int[columns];  
        m_trackRows = new int[rows];  
        m_helper = new Cell[m_maxBallVal+1];    
        m_card = new Cell*[rows];     
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;   
        m_maxBallVal = max;   
    }
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max){
    bool valid = false;
    if (2 > rows || rows > 15 ){
        cout << "Invalid number of rows. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;   
    } else if (columns != 5){
        cout << "Invalid number of columns. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0;  
    } else if (min < 11 || max > 85){
        cout << "Invalid number of balls. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr;  
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0; 
    } else if ((max - min) % 5 != 0){
        cout << "Invalid number of balls. Creating empty object..." << endl;
        m_trackCols = nullptr;  
        m_trackRows = nullptr; 
        m_helper = nullptr;    
        m_helperSize = 0;
        m_card = nullptr;     
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;   
        m_maxBallVal = 0; 
    } else {
        cout << "Initialization successfull. Creating bingo object..." << endl;
        m_trackCols = new int[columns];
          
        m_trackRows = new int[rows];  
        m_helper = new Cell[m_maxBallVal+1];    
        m_card = new Cell*[rows];     
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;   
        m_maxBallVal = max;
        valid = true;   
    }
    if (valid==true){
        return initCard();
    }
    return valid;
}

Bingo::~Bingo(){
    delete[] m_trackCols;  
    delete[] m_trackRows;  
    delete[] m_helper;    
    for (int i = 0; i < m_numRows; i++){
        delete[] m_card[i];
    }
    delete[] m_card;     
}

void Bingo::clear(){
    delete[] m_trackCols;  
    delete[] m_trackRows;  
    delete[] m_helper; 
    m_trackCols = nullptr;  
    m_trackRows = nullptr;  
    m_helper = nullptr;       
    m_helperSize = 0;
    for (int i = 0; i < m_numRows; i++){
        delete[] m_card[i];
    }
    delete[] m_card;
    m_card = nullptr;     
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;   
    m_maxBallVal = 0;
}

bool Bingo::initCard(){
    // populate card with random values within the requirements
    // each column gets 20% of the range from min to max in order
    if (m_card!=nullptr){

        int totalRange = m_maxBallVal - m_minBallVal + 1;
        int portion = totalRange / m_numCols;
        // col1 range = (min, min+portion), col2 range = (min+portion, min+2*portion)...
        Random range1(m_minBallVal, m_minBallVal+portion);
        Random range2(m_minBallVal+portion, m_minBallVal+(2*portion));
        Random range3(m_minBallVal+(2*portion), m_minBallVal+(3*portion));
        Random range4(m_minBallVal+(3*portion), m_minBallVal+(4*portion));
        Random range5(m_minBallVal+(4*portion), m_minBallVal+(5*portion));
        for (int i = 0; i < m_numRows; i++){
            m_card[i] = new Cell[m_numCols];
        }
        // iterate through list and as it goes to each column in the row, assign random value of correct range
        for (int i = 0; i < m_numRows; i++){
            for(int j = 0; j < m_numCols; j++){
                if (j == 0){
                    m_card[i][j].setVal(range1.getRandNum()); 
                }else if (j == 1){
                    m_card[i][j].setVal(range2.getRandNum());
                }else if (j == 2){
                    m_card[i][j].setVal(range3.getRandNum ());
                }else if (j == 3){
                    m_card[i][j].setVal(range4.getRandNum());
                }else {
                    m_card[i][j].setVal(range5.getRandNum());
                }
                m_card[i][j].setRow(i);
                m_card[i][j].setCol(j);
                m_helper[m_card[i][j].getVal()].setVal(m_card[i][j].getVal());
                m_helper[m_card[i][j].getVal()].setRow(i);
                m_helper[m_card[i][j].getVal()].setCol(j);
            }
        }
        return true;
    }
    return false;
}

vector<int> Bingo::drawBalls(){
    Random blower(m_minBallVal, m_maxBallVal, SHUFFLE); // a blower in the thing that mixes and dispenses the balls in bingo
    vector<int> balls;
    blower.getShuffle(balls);
    return balls;
}

int Bingo::play(int numDraws, vector<int> rndBalls){

    return 1;
}

const Bingo & Bingo::operator=(const Bingo & rhs){
    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
};

int main(){
    int testRows, testCols, testMin, testMax;

    cout << "Enter number of rows" << endl;
    cin >> testRows;
    cout << "Enter number of columns" << endl;
    cin >> testCols;
    cout << "Enter number of minimum balls" << endl;
    cin >> testMin;
    cout << "Enter number of maximum balls" << endl;
    cin >> testMax;

    Bingo testObj(testRows, testCols, testMin, testMax);
    // bool success = testObj.initCard();

    // while (success!=true){
    //     cout << "Enter number of rows" << endl;
    //     cin >> testRows;
    //     cout << "Enter number of columns" << endl;
    //     cin >> testCols;
    //     cout << "Enter number of minimum balls" << endl;
    //     cin >> testMin;
    //     cout << "Enter number of maximum balls" << endl;
    //     cin >> testMax;
    
    //     bool success = testObj.reCreateCard(testRows, testCols, testMin, testMax);
    // };
    testObj.initCard();
    testObj.dumpCard();
    return 0;
};