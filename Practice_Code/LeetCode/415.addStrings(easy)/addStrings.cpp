/**
 * @brief 思路：
 *            1.加法是从地位开始运算，可以先翻转数字
 *            2.注意两个数字（string）长度可能不一致
 * 
 */
class Solution {
public:
    string addStrings(string num1, string num2) {
        string ans("");
        int len1 = num1.length(), len2 = num2.length();
        int carryBit = 0;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        if(len1 <= len2){       //为了num1.len > num2.len     
            swap(num1, num2);
            swap(len1, len2);
        }

        for(int i = 0; i < len2; ++i){
            int cur_sum = (num1[i] - '0') + (num2[i] - '0') + carryBit;
            ans += to_string((cur_sum) % 10);
            carryBit = cur_sum < 10 ? 0 : 1;
            //printf("%d ", cur_sum);
        }

        for(int i = len2; i < len1; ++i){
            int cur_sum = (num1[i] - '0') + carryBit;
            ans += to_string((cur_sum) % 10);
            carryBit = cur_sum < 10 ? 0 : 1;
        }

        if(carryBit){ //注意细节
            ans += "1";
        }

        reverse(ans.begin(), ans.end());

        return ans;

    }
};