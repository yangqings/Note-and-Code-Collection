
/**
 * @brief 求0~n范围质数的个数
 *        埃拉托斯特尼筛法（Sieve of Eratosthenes，简称埃氏筛法）：
 *        从1 到n 遍历，假设当前遍历到m，则把所有小于n 的、且是m 的倍
 *        数的整数标为和数；遍历完成后，没有被标为和数的数字即为质数。
 */
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;
        vector<bool> prime(n, true);
        int count = n - 2; // 去掉不是质数的1
        for (int i = 2; i <= n; ++i) {
            if(prime[i]){
                for(int j = 2*i; j < n; j += i){
                    if(prime[j]){
                        prime[j] = false;
                        --count;
                    }
                }
            }
        }
        return count;
    }
};