// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
Bingo::Bingo(){
    // Default constructor
    // Preconditions: bingo object created with no params
    // Postconditions: generates empty bingo object
    //  any dynamic arrays set to nullptr, and any ints set to 0

    m_trackCols = nullptr;  
    m_trackRows = nullptr;  
    m_helper = nullptr;    
    m_helperSize = 0;
    m_card = nullptr;     
    m_numCols = 0;
    m_minBallVal = 0;   
    m_maxBallVal = 0;   
}

Bingo::Bingo(int rows, int columns, int min, int max){
    // Overloaded constructor
    // Preconditions: create bingo object with 
    //  number of rows and columns, and minimum and maximum ball values
    // Postconditions: if all params meet necessary requirements,
    //  initialize member variables accordingly
    //  else create empty object
    //  requirements: 2-15 rows, 5 columns, min at least 11, max - min + 1 must div by 5

    if (2 > rows || rows > 15){
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
    } else if ((max - min + 1) % 5 != 0){
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
        m_trackCols = new int[columns]; // allocate space by number of columns  
        m_trackRows = new int[rows];    // allocate space by number of rows
        m_helper = new Cell[max+1];     // allocate space by max ball value (+1 because 0 index)
        m_helperSize = max + 1;
        m_card = new Cell*[rows];       // allocate space for each column array by number of rows
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;   
        m_maxBallVal = max;   
    }
}

bool Bingo::initCard(){
    // Function to generate intitial cell values for the card
    // Preconditions: a NON EMPTY bingo object has been created
    // Postconditions: 1) populate card with random values within the requirements
    //  where each column gets 20% of the range from min to max in order
    //  2) populate m_helper with the cell values that exist on the card
    //  3) populate m_trackRows/Cols with 0s

    if (m_card!=nullptr){ // ensure bingo object is not empty

        int totalRange = m_maxBallVal - m_minBallVal + 1; // ex. 85 - 11 = 74 + 1 = 75 
        int portion = totalRange / m_numCols; // ex. 75 / 5 = 15

        // col1 range = (min, min+portion), col2 range = (min+portion, min+2*portion)...
        Random range1(m_minBallVal, m_minBallVal+portion);
        Random range2(m_minBallVal+portion, m_minBallVal+(2*portion));
        Random range3(m_minBallVal+(2*portion), m_minBallVal+(3*portion));
        Random range4(m_minBallVal+(3*portion), m_minBallVal+(4*portion));
        Random range5(m_minBallVal+(4*portion), m_minBallVal+(5*portion));

        // allocate memory for each array stored in m_card
        for (int i = 0; i < m_numRows; i++){
            m_card[i] = new Cell[m_numCols];
        }

        // iterate through list and as it goes to each column in the row, 
        //  assign random value from corresponding range
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
                // also set the row and column numbers for each cell
                m_card[i][j].setRow(i);
                m_card[i][j].setCol(j);
                // and set the cell values and row and column numbers
                //  for the corresponding cell in m_helper
                m_helper[m_card[i][j].getVal()].setVal(m_card[i][j].getVal());
                m_helper[m_card[i][j].getVal()].setRow(i);
                m_helper[m_card[i][j].getVal()].setCol(j);
            }
        }
        
        // populate tracker arrays with 0s
        for (int i = 0; i < m_numRows; i++){
            m_trackRows[i] = 0;
        }
        for (int i = 0; i < m_numCols; i++){
            m_trackCols[i] = 0;
        }
        // return true to indicate card has been initialized
        return true;
    }
    // return false to indicate card could not be initialized
    return false;
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max){
    // Function for reinitializing and generating numbers for a new card
    // Preconditions: called with (typically empty) bingo object and 
    //  a new number of rows and columns, and minimum and maximum ball values
    // Postconditions: if all params meet necessary requirements,
    //  initialize member variables accordingly AND call initCard 
    //  else create empty object
    //  requirements: 2-15 rows, 5 columns, max - min + 1 must div by 5

    bool valid = false; // keep track of whether the function successfully executes
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
    } else if ((max - min + 1) % 5 != 0){
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
        m_helper = new Cell[max+1];
        m_helperSize = max + 1;    
        m_card = new Cell*[rows];     
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;   
        m_maxBallVal = max;
        valid = true;   // true if initialization is successful
    }
    // only call initCard if object initialized successfully
    if (valid==true){
        bool init_result = initCard();
        return init_result; // return bool for if initCard ran successfully 
    }
    return valid; // return false if params were invalid
}

Bingo::~Bingo(){
    // Destructor 
    // Preconditions: none
    // Postconditions: deallocates all dynamically allocated memory

    delete[] m_trackCols;  
    delete[] m_trackRows;  
    delete[] m_helper;    
    for (int i = 0; i < m_numRows; i++){    // deallocate each array within m_card
        delete[] m_card[i];
    }
    delete[] m_card;     
}

void Bingo::clear(){
    // Function for deallocating and then creating an empty bingo object
    // Preconditions: a non empty bingo object was already created 
    // Postconditions: deallocate all dynamically allocated memory
    //  and reinitialize all member variables to default values
    
    if (m_card != nullptr){ // check that bingo object in not empty
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
}

vector<int> Bingo::drawBalls(){
    // Function to genereate a series of unique ball values within the given range
    // Preconditions: a non empty bingo object has been created (thus, min and max are valid)
    // Postconditions: returns a vector containing a set of random, unique ball values within range

    Random blower(m_minBallVal, m_maxBallVal, SHUFFLE); // a blower is the thing that mixes and dispenses the balls in bingo
    vector<int> balls;
    blower.getShuffle(balls);
    return balls;
}

int Bingo::play(int numDraws, vector<int> rndBalls){
    // Function for playing the bingo game
    // Preconditions: a fully initiallized bingo object, vector of ball values
    //  and a number of draws before the game ends 
    // Postconditions: for numDraws, "draw" a ball and check if the number exists by checking the index in m_helper
    //  if the cell at that index isn't empty, 
    //  then that number is in the card and thus the cell at that row/col number in m_card should be made empty
    //  each time a match is found, increment a "hits counter"
    //  keep track of the number of hits in each row and column (use getcol/row-1 for index in trackcols/rows)
    //  continue until number of draws is reached or until a bingo is found (trackcols/rows[index] reaches numrows/cols)
    //  return the number of hits when game ends

    int hits = 0;   // to keep track of the hits

    for (int i = 0; i < numDraws; i++){
        int current_ball = rndBalls[i];
        if (m_helper[current_ball].getVal() != EMPTYCELL){
            m_card[m_helper[current_ball].getRow()][m_helper[current_ball].getCol()].setVal(EMPTYCELL);
            m_trackRows[m_helper[current_ball].getRow() - 1]++;
            m_trackCols[m_helper[current_ball].getCol() - 1]++;
            hits++;
            // check if all cells in row or column are empty
            if (m_trackRows[m_helper[current_ball].getRow() - 1] == m_numCols || m_trackCols[m_helper[current_ball].getCol() - 1] == m_numRows){ 
                return hits;
            }
        } 
    }
    return hits;
}

const Bingo & Bingo::operator=(const Bingo & rhs){
    // Assignment operator
    // Preconditions: a bingo object has been created
    // Postconditions: returns a deep copy of the specified bingo object

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

// FOR TESTING FUNCTIONS. DELETE WHEN FINISHED
// int main(){
//     int testRows, testCols, testMin, testMax;

//     cout << "Enter number of rows" << endl;
//     cin >> testRows;
//     cout << "Enter number of columns" << endl;
//     cin >> testCols;
//     cout << "Enter number of minimum balls" << endl;
//     cin >> testMin;
//     cout << "Enter number of maximum balls" << endl;
//     cin >> testMax;

//     Bingo testObj(testRows, testCols, testMin, testMax);

//     testObj.initCard();
//     testObj.dumpCard();
//     testObj.clear();
//     testObj.dumpCard();

//     // cout << "Enter number of rows" << endl;
//     // cin >> testRows;
//     // cout << "Enter number of columns" << endl;
//     // cin >> testCols;
//     // cout << "Enter number of minimum balls" << endl;
//     // cin >> testMin;
//     // cout << "Enter number of maximum balls" << endl;
//     // cin >> testMax;

//     // testObj.reCreateCard(testRows, testCols, testMin, testMax);
//     // testObj.dumpCard();
//     // testObj.clear();
//     // return 0;
// };