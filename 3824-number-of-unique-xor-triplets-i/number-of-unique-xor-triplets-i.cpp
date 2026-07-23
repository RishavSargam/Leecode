#include <vector>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        int n = nums.size();
        // For n = 1 or n = 2, we can only form n unique values
        if (n <= 2) {
            return n;
        }
        
        // __builtin_clz counts the leading zeros of a 32-bit integer
        int bit_length = 32 - __builtin_clz(n);
        
        // Return 1 left-shifted by the number of bits
        return 1 << bit_length;
    }
};
