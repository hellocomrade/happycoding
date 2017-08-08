#include <limits>

using namespace std;

class SolutionReverseInteger {
public:
    int reverse(int x) {
        long long ans = 0LL;
        while(x) {
            ans = ans * 10LL + x % 10;
            x /= 10;
        }
        return ans >= numeric_limits<int>::min() && ans <= numeric_limits<int>::max() ? static_cast<int>(ans) : 0;
    }
    int reverse1(int x) {
        int ans = 0, tmp;
        while(x) {
            tmp = ans * 10 + x % 10;
            if(ans != tmp / 10)return 0;
            ans = tmp;
            x /= 10;
        }
        return ans;
    }
};
