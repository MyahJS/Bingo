// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
class Tester{
    public:

    bool assignmentNormal(Bingo & lhs, Bingo & rhs){
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

    bool constructorNormal(Bingo obj, int rows, int cols, int min, int max){
        return true;
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

    obj1.initCard();

    obj1.dumpCard();

    obj1.clear();

    obj1.dumpCard();

    obj1.reCreateCard(CARDROWS,CARDCOLS,MINVAL,MAXVAL);

    obj1.dumpCard();

    // if (obj1.initCard()){
    //     obj1.dumpCard();
    //     cout << "\ngame over after " << obj1.play(BALLS,balls) << " hits!\n" << endl;
    //     obj1.dumpCard();
    // } else {
    //     obj1.dumpCard();
    // }

    return 0;
}