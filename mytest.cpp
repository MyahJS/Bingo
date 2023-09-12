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

    bool constructorTest(Bingo obj, int rows, int cols, int min, int max){
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

    bool initCardNormal(Bingo obj, int rows, int cols, int min, int max){
        return true;
    }

    bool reCreateCardNormal(Bingo obj, int rows, int cols, int min, int max){
        return true;
    }

    bool playNormal(Bingo obj, int numDraws, vector<int> rndBalls){
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
    cout << "Testing the constructor for a normal case:" << endl;
    if (tester.constructorTest(obj1, CARDROWS, CARDCOLS, MINVAL, MAXVAL)){
        cout << "Constructor test for normal case passed!" << endl;
    } else {
        cout << "Constructor test for normal case failed!" << endl;
    }

    return 0;
}