class Solution {
    /*回溯法求解N皇后*/
public:
    vector<vector<string>> res; /* result */
    vector<vector<string>> solveNQueens(int n) {
        /* 一个符合条件的放置方案,初始化为'.' */
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }

private:

    /*递归*/
    void backtrack(vector<string>& board, int row)
    {
        /*end*/
        if(board.size() == row){
            res.push_back(board);
            return ;
        }

        int n = board[row].size();
        for(int col = 0; col < n; ++col)
        {
            if( ! isValid(board, row, col))
                continue;
            
            board[row][col] = 'Q';    /*do*/
            backtrack(board, row + 1);/*recursive, next row*/
            board[row][col] = '.';    /*undo*/
        }

    }

    /*判断Q放置是否符合规定*/
    bool isValid(vector<string>& board, int row, int col)
    {
        int n = board.size();

        for(int i = 0; i < n; i++){
            if(board[i][col] == 'Q')return false;
        }
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++){
            if(board[i][j] == 'Q')return false;
        }
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
            if(board[i][j] == 'Q')return false;
        }
        return true;
    }
};