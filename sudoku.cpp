#include <iostream>
#include <vector>
#include <utility>
using namespace std;


class Sudoku {
public:
    Sudoku() : total(0) {
        board.resize(9, vector<char>(9));
        char c;
        uint32_t count = 0;
        while(count < 81 && cin >> c) {
            board[count / 9][count % 9] = c;
            count++;
            if(isdigit(c)) {
                total++;
            }
        }
    }

    void solve(uint32_t row, uint32_t col) {
        if(total == 81) { //solution
            printBoard();
            return;
        }
        if(isdigit(board[row][col])) {
            total++;
            solve(row + (col + 1)/9, (col + 1) % 9);
        }
        else {
            for(size_t v = 0; v < nums.size(); v++) {
                if(promising(row, col, nums[v])) {
                    board[row][col] = nums[v];
                    solve(row + (col + 1)/9, (col + 1) % 9);
                    board[row][col] = '*';
                }
            }
        }
    }

private:
    bool promising(uint32_t row, uint32_t col, char val) {
        for(size_t r = 0; r < board.size(); r++) { //check column
            if(r != row && board[r][col] == val) {
                return false;
            }
        }

        for(size_t c = 0; c < board[0].size(); c++) { //check row
            if(c != col && board[row][c] == val) {
                return false;
            }
        }

        //checkBox
        auto box = findBox(row,col);
        for(size_t r = 3 * (box.first - 1); r < 3 * box.first; r++) {
            for(size_t c = 3 * (box.second - 1); c < 3 * box.second; c++) {
                if((r != row || c != col) && board[r][c] == val) {
                    return false;
                }
            }
        }
        
        return true;
    }

    void printBoard() {
        cout << "|-------|-------|-------|\n";
        for(size_t r = 0; r < board.size(); r++) {
            cout << "| " << board[r][0] << " ";
            for(size_t c = 1; c < board[0].size() - 1; c++) {
                cout << board[r][c] << " ";
                if(c % 3 == 2) {
                    cout << "| ";
                }
            }
            cout << board[r].back() << " |\n";
            if(r % 3 == 2) {
                cout << "|-------|-------|-------|\n";
            }
        }
    }

    pair<uint32_t,uint32_t> findBox(uint32_t row, uint32_t col) {
        if(row < 3) {
            if(col < 3) {
                return make_pair(1,1);
            }
            else if(col < 6) {
                return make_pair(1,2);
            }
            else {
                return make_pair(1,3);
            }
        }
        else if(row < 6) {
            if(col < 3) {
                return make_pair(2,1);
            }
            else if(col < 6) {
                return make_pair(2,2);
            }
            else {
                return make_pair(2,3);
            }
        }
        else {
            if(col < 3) {
                return make_pair(3,1);
            }
            else if(col < 6) {
                return make_pair(3,2);
            }
            else {
                return make_pair(3,3);
            }
        }
    }

    uint32_t total;
    vector<vector<char>> board;
    const vector<char> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv); //file redirection

    Sudoku s;
    s.solve(0,0);
}
