/*
 Write a function that reverses a string. The input string is given as an array of characters s.
You must do this by modifying the input array in-place with O(1) extra memory.

Constraints:
1 <= s.length <= 105
s[i] is a printable ascii character.
*/

#include <vector>

class Solution {
public:
    void reverseString(std::vector<char>& s) {
        int left=0, right=s.size()-1;
        while(left<right){
            char t=s[left];
            s[left]=s[right];
            s[right]=t;
            ++left;
            --right;
        }
    }
};
