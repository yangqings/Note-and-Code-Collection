/**
 * @brief 通过斜杠划分区域
 *        思路：并查集
 */

/**
 * @brief Union Set
 *        常规并查集
 */
class USet{
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    USet(int n): parent(n), rank(n), count(1){
        for(int i = 0; i < n; ++i){
            parent[i]=i;
        }
    }

    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y){
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY){
            if(rank[rootX] < rank[rootY]){
                swap(rootX, rootY);
            }
            
            parent[rootY] = rootX;

            if(rank[rootX] == rank[rootY]) 
                rank[rootX] += 1;
        }else{//两个顶点的根节点相同，区域数+1
            count++;
        }
    }

    int getCount(){
        return count;
    }
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        if(n == 0) return 0;
        int m = n + 1;
        int num = m*m;

        USet us(num + 1);
        for(int i = 0; i < num; ++i){
            if(i/m == 0 || i/m == m - 1 || i%m == 0 || i%m == m - 1)
                us.merge(num, i);
        }

        for(int i = 0; i < n; ++i){
            auto s = grid[i];
            for(int c = 0; c < s.size(); ++c){
                if(s[c] == '/') us.merge((i + 1)*m + c, i * m + c + 1);
                else if(s[c] == '\\')us.merge(i * m + c, (i + 1) * m + c + 1);
            }
        }
        return us.getCount();
    }
};