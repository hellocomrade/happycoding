#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/random-pick-with-weight/
/*
528. Random Pick with Weight

You are given an array of positive integers w where w[i] describes the weight of ith index (0-indexed).

We need to call the function pickIndex() which randomly returns an integer in the range [0, w.length - 1]. pickIndex() should return the integer proportional to its weight in the w array.
For example, for w = [1, 3], the probability of picking the index 0 is 1 / (1 + 3) = 0.25 (i.e 25%) while the probability of picking the index 1 is 3 / (1 + 3) = 0.75 (i.e 75%).

More formally, the probability of picking index i is w[i] / sum(w).

Example 1:

Input

["Solution","pickIndex"]

[[[1]],[]]

Output
[null,0]

Explanation

Solution solution = new Solution([1]);

solution.pickIndex(); // return 0. Since there is only one single element on the array the only option is to return the first element.

Example 2:

Input

["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]

[[[1,3]],[],[],[],[],[]]

Output

[null,1,1,1,1,0]

Explanation

Solution solution = new Solution([1, 3]);

solution.pickIndex(); // return 1. It's returning the second element (index = 1) that has probability of 3/4.

solution.pickIndex(); // return 1

solution.pickIndex(); // return 1

solution.pickIndex(); // return 1

solution.pickIndex(); // return 0. It's returning the first element (index = 0) that has probability of 1/4.

Since this is a randomization problem, multiple answers are allowed so the following outputs can be considered correct :

[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......

and so on.


Constraints:

- 1 <= w.length <= 10000
- 1 <= w[i] <= 10^5
- pickIndex will be called at most 10000 times.

Observations:

First of all, this is about Possibility theory, not picking items for a knapsack....

Based upon the calculated randomized possibility on the fly, like rand(), the index (number) with the possibility w[i]/sum(w) shall be returned. More precisely,

For w as [1,3], the possibilities are [0.25, 0.75] or [1, 4] in the integer form.

Given a randomly generated number saying 0.6 or 3 in the integer form, which index (number) should be returned? The answer is index = 1 (3), since the possibility is higher than 0.25 or 1.

In other words, since the possibility of returning index =0 (1) is 25% or 1 out of 5, current given possibility 60% or 3 out of 5 is higher. Index = 1 (3) should be returned.

So, with any given possibility, how can the proper index be located efficiently?

[1, 3, 1] -> [0.2, 0.6, 0.2]

How about BS?

If naively sorting the possibility array -> [0.2, 0.2, 0.6], and 30% is given, then index = 1 (3) is returned.

What if we do prefix sum? [1, 3, 1] -> [0.2, 0.8, 1.0] or [1, 4, 5] and 30% is given, then index = 1 (3) is returned. By doing prefix sum, sorting can be avoid and a linear
algorithm is feasible.

By using the fancy std::uniform_int_distribution instead of rand(), there is probably a penalty on performance...
*/
class RandomPickWithWeight {
private:
	vector<int> prefixSum;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution;
public:
	RandomPickWithWeight(vector<int>& w) : prefixSum(w.size(), 0), generator() {
		std::partial_sum(w.begin(), w.end(), this->prefixSum.begin());
		/*
		Upper and lower bounds of the range([a, b]) of possible values the distribution can generate.
		Note that the range includes both a and b(along with all the integer values in between).
		*/
		this->distribution = std::uniform_int_distribution<int>(0, this->prefixSum[prefixSum.size() - 1] - 1);
	}

	int pickIndex() {
		return std::upper_bound(this->prefixSum.begin(), this->prefixSum.end(), distribution(this->generator)) - this->prefixSum.begin();
	}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

 /*
 Test cases:
 ["Solution","pickIndex"]
 [[[1]],[]]
 ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
 [[[1,3]],[],[],[],[],[]]

 Outputs:
 [null,0]
 [null,0,0,1,1,1]

 */