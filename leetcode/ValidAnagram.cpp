#include <string>
using namespace std;
class SolutionValidAnagram {
public:
    bool isAnagram(string s, string t) {
        if(s.length() == t.length()) {
            long long memo[26] = {0};
            for(auto c : s)++memo[c - 97];
            for(auto c : t) {
                if(memo[c - 97] > 0)--memo[c - 97];
                else return false;
            }
            return true;
        }
        return false;
    }
};
