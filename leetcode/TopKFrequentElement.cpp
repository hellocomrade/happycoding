#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//
/*
347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
- You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
- Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

Observations:
This can be done in O(NlogN) for sure. But it asks for a linear or even log solution. What are the available sorting algorithm could
achieve linear time complexity:

- Heap, not heap sort, asymptotically tight time complexity of building a heap is O(N);

- Another one is bucket sort;

However, leetcode only offers 20 test cases, which is not enough to tell the difference between O(NlogN) and O(N) by my testing.

topKFrequent2 is using std::make_heap series and lambda compare function explicitly.

topKFrequent1 take advantage of priority_heap defined in <queue>

topKFrequent is with bucket sort. This is guaranteed O(N). Even though the integers in nums could range from [INT_MIN, INT_MAX], the buckets
here are counted by the number of occurrence. Therefore, only len(nums) buckets are needed!
*/
class SolutionTopKFrequentElement {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int len = (int)nums.size();
        vector<int> ans;
        vector<vector<int>> bucket(len + 1, vector<int>());
        unordered_map<int, size_t> counts;
        for(int i : nums)++counts[i];
        for(auto i : counts)bucket[i.second].push_back(i.first);
        for(int i = len; i > -1 ; --i) {
            if(bucket[i].size() > 0)
                for(int i : bucket[i])
                    if(ans.size() < k)ans.push_back(i);
            if(k == ans.size())break;
        }
        return ans;
    }
    vector<int> topKFrequent1(vector<int>& nums, int k) {
        vector<int> ans(k , 0);
        priority_queue<std::pair<int, size_t>> heap;
        unordered_map<int, size_t> counts;
        for(int i : nums)++counts[i];
        for(auto i : counts)heap.emplace(i.second, i.first);
        for(int i = 0; i < k; ++i) {
            ans[i] = heap.top().second;
            heap.pop();
        }
        return ans;
    }
    vector<int> topKFrequent2(vector<int>& nums, int k) {
        vector<int> ans(k , 0);
        vector<std::pair<int, size_t>> heap;
        unordered_map<int, size_t> counts;
        for(int i : nums)++counts[i];
        auto cmp = [](const auto& p1, const auto& p2) {return p1.second < p2.second;};
        for(auto i : counts)heap.push_back(i);
        std::make_heap(heap.begin(), heap.end(), cmp);
        for(int i = 0; i < k; ++i) {
            std::pop_heap(heap.begin(), heap.end(), cmp);
            ans[i] = heap.back().first;
            heap.pop_back();
        }
        return ans;
    }
};
