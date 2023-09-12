// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
class Tester{
    public:

    bool assignmentTest(Bingo & lhs, Bingo & rhs){
        // we expect that lhs object is an exact copy of rhs object 
        bool result = true;

        // we expect that the corresponding cells in lhs and rhs
        //      cards carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            for (int j=0;j<rhs.m_numCols;j++){
                result = result && (lhs.m_card[i][j] == rhs.m_card[i][j]);
            }
        }

        // we expect that the corresponding cells in lhs and rhs
        //      m_helper carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_helperSize;i++){
            result = result && (lhs.m_helper[i] == rhs.m_helper[i]);
        }

        // we expect that the corresponding cells in lhs and rhs
        //      m_trackRows carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            result = result && (lhs.m_trackRows[i] == rhs.m_trackRows[i]);
        }

        // we expect that the corresponding cells in lhs and rhs
        //      m_trackCols carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numCols;i++){
            result = result && (lhs.m_trackCols[i] == rhs.m_trackCols[i]);
        }

        result = result && (lhs.m_minBallVal == rhs.m_minBallVal);
        result = result && (lhs.m_maxBallVal == rhs.m_maxBallVal);

        return result;
    }

    bool constructorTest(Bingo & obj, int rows, int cols, int min, int max){
        // check that, if all params are valid, an object is created that matches those params
        // else check that an empty object is created
        bool result = true;

        if ((2 > rows || rows > 15 ) || (cols != 5) || (min < 1 || max > 90 || (max - min + 1) % 5 != 0)){
            // check that all ints are 0 and all arrays are nullptr
            result = result && (obj.m_numRows == 0);
            result = result && (obj.m_numCols == 0);
            result = result && (obj.m_helperSize == 0);
            result = result && (obj.m_minBallVal == 0);
            result = result && (obj.m_maxBallVal == 0);
            result = result && (obj.m_trackRows == nullptr);
            result = result && (obj.m_trackCols == nullptr);
            result = result && (obj.m_helper == nullptr);
            result = result && (obj.m_card == nullptr);
        } else {
            // check that all member ints match the params and all arrays are not null
            result = result && (obj.m_numRows == rows);
            result = result && (obj.m_numCols == cols);
            result = result && (obj.m_helperSize == max + 1);
            result = result && (obj.m_minBallVal == min);
            result = result && (obj.m_maxBallVal == max);
            result = result && (obj.m_trackRows != nullptr);
            result = result && (obj.m_trackCols != nullptr);
            result = result && (obj.m_helper != nullptr);
            result = result && (obj.m_card != nullptr);
        }
        return result;
    }

    bool initCardTest(Bingo & beforeInit, Bingo & afterInit, int min=0, int max=0){
        bool result = true;

        if (beforeInit.m_card == nullptr){
            // check that object is still empty
            result = result && (afterInit.m_numRows == 0);
            result = result && (afterInit.m_numCols == 0);
            result = result && (afterInit.m_helperSize == 0);
            result = result && (afterInit.m_minBallVal == 0);
            result = result && (afterInit.m_maxBallVal == 0);
            result = result && (afterInit.m_trackRows == nullptr);
            result = result && (afterInit.m_trackCols == nullptr);
            result = result && (afterInit.m_helper == nullptr);
            result = result && (afterInit.m_card == nullptr);
        } else {
            // make sure values in cells are within the correct range
            int totalRange = max - min + 1;
            int portion = totalRange / beforeInit.m_numCols;
            for (int i = 0; i < afterInit.m_numRows; i++){
                for(int j = 0; j < afterInit.m_numCols; j++){
                    if (j == 0){
                        result = result && (min <= afterInit.m_card[i][j].getVal() <= min+portion); 
                    }else if (j == 1){
                        result = result && (min+portion <= afterInit.m_card[i][j].getVal() <= min+2*portion);
                    }else if (j == 2){
                        result = result && (min+2*portion <= afterInit.m_card[i][j].getVal() <= min+3*portion);
                    }else if (j == 3){
                        result = result && (min+3*portion <= afterInit.m_card[i][j].getVal() <= min+4*portion);
                    }else {
                        result = result && (min+4*portion <= afterInit.m_card[i][j].getVal() <= min+5*portion);
                    }
                }
            }
        }
        return result;
    }

    bool reCreateCardTest(Bingo obj, int rows, int cols, int min, int max){
        bool result = true;

        if ((2 > rows || rows > 15 ) || (cols != 5) || (min < 1 || max > 90 || (max - min + 1) % 5 != 0)){
            // check that all ints are 0 and all arrays are nullptr
            result = result && (obj.m_numRows == 0);
            result = result && (obj.m_numCols == 0);
            result = result && (obj.m_helperSize == 0);
            result = result && (obj.m_minBallVal == 0);
            result = result && (obj.m_maxBallVal == 0);
            result = result && (obj.m_trackRows == nullptr);
            result = result && (obj.m_trackCols == nullptr);
            result = result && (obj.m_helper == nullptr);
            result = result && (obj.m_card == nullptr);
        } else {
            // check that all member ints match the params
            result = result && (obj.m_numRows == rows);
            result = result && (obj.m_numCols == cols);
            result = result && (obj.m_helperSize == max + 1);
            result = result && (obj.m_minBallVal == min);
            result = result && (obj.m_maxBallVal == max);
            // make sure values in cells are within the correct range
            int totalRange = max - min + 1;
            int portion = totalRange / obj.m_numCols;
            for (int i = 0; i < obj.m_numRows; i++){
                for(int j = 0; j < obj.m_numCols; j++){
                    if (j == 0){
                        result = result && (min <= obj.m_card[i][j].getVal() <= min+portion); 
                    }else if (j == 1){
                        result = result && (min+portion <= obj.m_card[i][j].getVal() <= min+2*portion);
                    }else if (j == 2){
                        result = result && (min+2*portion <= obj.m_card[i][j].getVal() <= min+3*portion);
                    }else if (j == 3){
                        result = result && (min+3*portion <= obj.m_card[i][j].getVal() <= min+4*portion);
                    }else {
                        result = result && (min+4*portion <= obj.m_card[i][j].getVal() <= min+5*portion);
                    }
                }
            }
        }
        return result;
    }

    bool playTest(Bingo obj, int numDraws, vector<int> rndBalls){
        return true;
    }

    private:
    
    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};

int main(){
    Tester tester;
    Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    vector<int> balls = obj1.drawBalls();

    //first check constructor for normal and edge case
    cout << endl << "Testing the constructor for a normal case:" << endl;
    if (tester.constructorTest(obj1, CARDROWS, CARDCOLS, MINVAL, MAXVAL)){
        cout << endl << "Constructor test for normal case passed!" << endl;
    } else {
        cout << endl << "Constructor test for normal case failed!" << endl;
    }

    Bingo obj2(-10, -5, MINVAL, MAXVAL);
    cout << endl << "Testing the constructor for an error case:" << endl;
    if (tester.constructorTest(obj2, -10, -5, MINVAL, MAXVAL)){
        cout << endl << "Constructor test for error case passed!" << endl;
    } else {
        cout << endl << "Constructor test for error case failed!" << endl;
    }

    Bingo obj1copy(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    obj1.initCard();
    cout << endl << "Testing initCard for a normal case:" << endl;
    if (tester.initCardTest(obj1copy, obj1, MINVAL, MAXVAL)){
        cout << endl << "InitCard test for normal case passed!" << endl;
    } else {
        cout << endl << "InitCard test for normal case failed!" << endl;
    }

    Bingo obj2copy;
    obj2.initCard();
    cout << endl << "Testing initCard for an error case:" << endl;
    if (tester.initCardTest(obj2copy, obj2)){
        cout << endl << "InitCard test for error case passed!" << endl;
    } else {
        cout << endl << "InitCard test for error case failed!" << endl;
    }

    Bingo obj3(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    obj3.clear();
    obj3.reCreateCard(2*CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    cout << endl << "Testing reCreateCard for a normal case:" << endl;
    if (tester.reCreateCardTest(obj3, CARDROWS, CARDCOLS, MINVAL, MAXVAL)){
        cout << endl << "ReCreateCard test for normal case passed!" << endl;
    } else {
        cout << endl << "ReCreateCard test for normal case failed!" << endl; 
    }

    obj3.clear();
    obj3.reCreateCard(2*CARDROWS,CARDCOLS,-10,1000);
    cout << endl << "Testing reCreateCard for an error case:" << endl;
    if (tester.reCreateCardTest(obj3, CARDROWS, CARDCOLS, -10, 1000)){
        cout << endl << "ReCreateCard test for error case passed!" << endl;
    } else {
        cout << endl << "ReCreateCard test for error case failed!" << endl; 
    }

    return 0;
}