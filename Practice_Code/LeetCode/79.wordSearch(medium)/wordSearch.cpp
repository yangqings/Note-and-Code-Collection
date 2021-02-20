/**
 * @brief 回溯法求解单词搜索问题
 *        解题关键：
 *                1.标记已经适配的单词，不能重复适配
 *                2.当单词失配时候，将标志位还原
 */

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size(), col = board[0].size();
        vector<vector<bool>> board_state(row, vector<bool>(col,false));

        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(backTrack(board, board_state, word, i, j))
                    return true;
            }
        }

        return false;
    }

    bool backTrack(vector<vector<char>>& board, vector<vector<bool>>& board_state, string word, int row, int col) 
    {
        int n = board.size(), m = board[0].size();

        if(word.length() == 1){//递归基
            return (board[row][col] == word.front());
        }
        if(board_state[row][col] == false && board[row][col] == word.front()){
            string tempString = word.substr(1, word.length());
            board_state[row][col] = true;    //标记
            for(int i = 0; i < 4; ++i){      //上下左右，共四个方向
                int x = row + direction[i][0];
                int y = col + direction[i][1];

                if(x < n && y < m && x >= 0 && y >= 0 && board_state[x][y] == false){
                    if(backTrack(board, board_state, tempString, x, y)) 
                        return true;
                }

            }
            board_state[row][col] = false;   //还原
        }
        return false;
    }

private:
    int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
};








