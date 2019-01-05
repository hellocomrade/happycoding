#include <vector>
#include <string>

using namespace std;

//https://www.hackerrank.com/challenges/countingsort4/problem
class SolutionFullCountSort {
public:
    void countSort(vector<vector<string>> arr) {
        int len = arr.size(), dash = len / 2, i = 0;
        vector<vector<string>> sorted(100, vector<string>());
        for(const auto& pair : arr)
            sorted[std::stoi(pair[0])].push_back(i++ < dash ? "-" : pair[1]);
        i = -1;
        while(++i < 100) for(const auto& str : sorted[i]) cout << str << " ";
        cout << endl;
    }
};
