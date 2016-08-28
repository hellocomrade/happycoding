#include <cassert>
#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/n-queens/
/*
 51. N-Queens  QuestionEditorial Solution  My Submissions
 Total Accepted: 60971
 Total Submissions: 223016
 Difficulty: Hard
 The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
 
 
 
 Given an integer n, return all distinct solutions to the n-queens puzzle.
 
 Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
 
 For example,
 There exist two distinct solutions to the 4-queens puzzle:
 
 [
 [".Q..",  // Solution 1
 "...Q",
 "Q...",
 "..Q."],
 
 ["..Q.",  // Solution 2
 "Q...",
 "...Q",
 ".Q.."]
 ]
 
 Observations:
 I don't know chess, so had to do a bit research on rules for Queen. Quenn can attack any enemy on the same row, same column
 or same diagonals (2 of them, if Queen is not on any edge). According to wiki:
 
 https://en.wikipedia.org/wiki/Eight_queens_puzzle
 
 "The eight queens puzzle is the problem of placing eight chess queens on an 8×8 chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. The eight queens puzzle is an example of the more general n queens problem of placing n non-attacking queens on an n×n chessboard, for which solutions exist for all natural numbers n with the exception of n=2 and n=3."
 
 It sounds like backtracing fits the logic best! So be it! Here is the intuitive solution:
 We put Queen on every position at each row, then move to the next row, try any position on the second row that
 will not break the rules defined above. The implicit rule we apply automatically is no Queens on the same row
 since we only place a Queen on each row.
 
 Recursion is of course applied since we do backtracing.
 
 The first version runs 12 ms on Leetcode, take a closer look: we could actually combine 3 for loops together in
 a single loop, which will potentially boost the performance by 3 times. So came with the second version. But,
 the first version is still more understandable. Please refer to the inline comments in aux1.
*/
class SolutionNQueens {
private:
    //8ms
    void aux(vector<vector<string>> &ans, vector<string> &vec, int idx, int n) {
        if(idx == n) {
            ans.push_back(vector<string>(vec));
            return;
        }
        for(int i = 0; i < n; ++i) {
            if(idx > 0) {
                bool bj = false, bk = false, bl = false;
                for(int j = i - 1, k = i + 1, l = idx - 1;l >= 0; --j, ++k, --l) {
                    if(j >= 0 && vec[l][j] == 'Q') {
                        bj = true;
                        break;
                    }
                    if(k < n && vec[l][k] == 'Q') {
                        bk = true;
                        break;
                    }
                    if(vec[l][i] == 'Q') {
                        bl = true;
                        break;
                    }
                }
                if(bj || bk || bl)continue;
            }
            vec[idx][i] = 'Q';
            this->aux(ans, vec, idx + 1, n);
            vec[idx][i] = '.';
        }
    }
    //12ms
    void aux1(vector<vector<string>> &ans, vector<string> &vec, int idx, int n) {
        if(idx == n) {//if we reach here, we have a valid solution
            ans.push_back(vector<string>(vec));
            return;
        }
        for(int i = 0; i < n; ++i) {
            if(idx > 0) { //we allow Queen to be placed on any position on row 0, no check if idx == 0
                int j, k;
                //Check backward diagnal
                for(j = i - 1, k = idx - 1; j >= 0 && k >= 0; --j, --k)
                    if(vec[k][j] == 'Q')break;
                //If the exit of loop by the break? k >= 0 means we still have rows to check,
                //if this is the case and j != -1, we have a conflict
                if(j != -1 && k >= 0)continue;
                //Check forward diagnal
                for(j = i + 1, k = idx - 1; j < n && k >= 0; ++j, --k)
                    if(vec[k][j] == 'Q')break;
                //If the exit of loop by the break? k >= 0 means we still have rows to check,
                //if this is the case and j != n, we have a conflict
                if(j != n && k >= 0)continue;
                //Check same column
                for(j = 0; j < idx; ++j)
                    if(vec[j][i] == 'Q')break;
                //If the exit of loop by the break? k >= 0 means we still have rows to check so a conflict it is
                if(j < idx)continue;
            }
            //We are OK to put 'Q' at row idx with column index i
            vec[idx][i] = 'Q';
            this->aux1(ans, vec, idx + 1, n);
            //reset, bracktracing
            vec[idx][i] = '.';
        }
    }
public:
    /**
     * Get all distinct N-Queen solutions
     * @param n: The number of queens
     * @return: All distinct solutions
     * For example, A string '...Q' shows a queen on forth position
     */
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string>> ans = vector<vector<string>>();
        if(n > 0) {
            //Each string with n characters and acts like a row.
            vector<string> vec(n, string(n, '.'));
            this->aux(ans, vec, 0, n);
        }
        return ans;
    }
};
void TestNQueens() {
    SolutionNQueens so;
    vector<vector<string>> ans5 = so.solveNQueens(5);
    assert(10 == ans5.size());
    vector<vector<string>> ans8 = so.solveNQueens(8);
    assert(92 == ans8.size());
    return;
}



