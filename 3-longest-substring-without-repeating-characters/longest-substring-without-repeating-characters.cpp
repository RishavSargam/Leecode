
class Solution {
public:
    int lengthOfLongestSubstring(const string &s) {
        vector<int> last(256, 0); 
        int n = s.size();
        int l = 0; 
        int best = 0;
        for (int r = 0; r < n; ++r) {
            unsigned char ch = s[r];

            if (last[ch] > 0 && last[ch] - 1 >= l) {
                l = last[ch]; 
            }
            last[ch] = r + 1;          
            best = max(best, r - l + 1);   
        }
        return best;
    }
};