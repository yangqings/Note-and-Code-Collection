/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == nullptr)return 0;
        
        queue<pair<TreeNode *, int>> que;
        que.emplace(root, 1);

        while(!que.empty()){
            TreeNode *node = que.front().first;
            int depth = que.front().second;

            que.pop();
            if(node->left == nullptr && node->right == nullptr){
                return depth;
            }
            if(node->left != nullptr)
                que.emplace(node->left, depth + 1);
            
            if(node->right != nullptr)
                que.emplace(node->right, depth + 1);
            
        }
        return 0;
    }
};