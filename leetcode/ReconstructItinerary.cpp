#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/reconstruct-itinerary/
/*
332. Reconstruct Itinerary

Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).

You may assume all tickets form at least one valid itinerary.

Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]

Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]

Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]

Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]

Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
			 But it is larger in lexical order.

Observations:

Of cource, I didn't know Eulerian Path or Hierholzer's algorithm. But I can tell this looks like
a graph problem and can be solved by DFS or backtracing.

findItinerary2 is my first attempt, barely passed. For a classic graph DFS, visited node has to be tracked.
For this problem though, the visited path has to be tracked, which also means if you have two ['JFK', 'ATL'],
both of them count. Therefore, have to use unordered_map<string, int> visited;

Since it's slow, made improvement by get rid of using string concatenation as keys, which is findItinerary1.
However, it's still too slow comparing with other people's solution. Then I knew I must miss something!

https://en.wikipedia.org/wiki/Eulerian_path

See findItinerary: the trick is that there is no need to track visited path at all! Simply follow smallest lexical order
to dfs and remove downstream node on the way until there is no more path to go further.

Then fallback, at the same time pushing the node visited onto an array. The final answer will be this array in
reversed order.

For example:

[["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]

"JFK" -> "KUL" then there is no way to move forward. Fallback and push ["KUL"] on the array on the way back.

Then "JFK"->"NRT"->"JFK", no way to move forward coz it's done. So fallback and push ["JFK", "NRT", "JFK"] onto ["KUL"]

So we have ["KUL", "JFK", "NRT", "JFK"]. The final result is ["JFK", "NRT", "JFK", "KUL"].

Can I figure this out during an interview? Probably not, even I did it before :)
*/
class SolutionReconstructItinerary {
public:
	vector<string> findItinerary(const vector<vector<string>>& tickets) {
		int len = (int)tickets.size();
		vector<string> ans;
		unordered_map<string, vector<string>> matrix;
		for (const auto& ticket : tickets) matrix[ticket[0]].push_back(ticket[1]);
		for (auto& m : matrix) std::sort(m.second.begin(), m.second.end());
		function<void(const string&)> dfs = [&](const string& loc) -> void {
			string neighbor;
			while (0 < matrix[loc].size()) {
				neighbor = *matrix[loc].begin();
				matrix[loc].erase(matrix[loc].begin());
				dfs(neighbor);
			}
			ans.push_back(loc);
		};
		if (0 < len) dfs("JFK");
		else ans.push_back("JFK");
		return vector<string>(ans.rbegin(), ans.rend());
	}
	vector<string> findItinerary1(const vector<vector<string>>& tickets) {
		int len = (int)tickets.size();
		vector<string> ans(len + 1);
		unordered_map<string, vector<string>> matrix;
		unordered_map<string, unordered_map<string, int>> visited;
		for (const auto& ticket : tickets) {
			if (0 == matrix.count(ticket[0])) matrix[ticket[0]] = vector<string>();
			matrix[ticket[0]].push_back(ticket[1]);
			++visited[ticket[0]][ticket[1]];
		}
		for (auto& m : matrix) std::sort(m.second.begin(), m.second.end());
		function<bool(const string&, int)> dfs = [&](const string& loc, int i) -> bool {
			ans[i] = loc;
			if (i == len) return true;
			string p;
			for (const string& neighbor : matrix[loc]) {
				if (0 < visited[loc][neighbor]) {
					--visited[loc][neighbor];
					if (false == dfs(neighbor, i + 1)) ++visited[loc][neighbor];
					else return true;
				}
			}
			return false;
		};
		if (0 < len) dfs("JFK", 0);
		else ans[0] = "JFK";
		return ans;
	}
	vector<string> findItinerary2(vector<vector<string>>& tickets) {
		int len = (int)tickets.size();
		vector<string> ans;
		unordered_map<string, vector<string>> matrix;
		unordered_map<string, int> visited;
		for (const auto& ticket : tickets) {
			if (0 == matrix.count(ticket[0])) matrix[ticket[0]] = vector<string>();
			matrix[ticket[0]].push_back(ticket[1]);
			++visited[ticket[0] + ticket[1]];
		}
		for (auto& m : matrix) std::sort(m.second.begin(), m.second.end());
		function<bool(const string&)> dfs = [&](const string& loc) -> bool {
			ans.push_back(loc);
			if (ans.size() == len + 1) return true;
			string p;
			for (const string& neighbor : matrix[loc]) {
				p = loc + neighbor;
				if (0 < visited[p]) {
					--visited[p];
					if (false == dfs(neighbor)) ++visited[p];
					else return true;
				}
			}
			ans.pop_back();
			return false;
		};
		if (0 < len) dfs("JFK");
		else ans.push_back("JFK");
		return ans;
	}
};
void TestReconstructItinerary() {
	SolutionReconstructItinerary so;
	so.findItinerary({});
	so.findItinerary({ {"JFK", "SFO"}, {"SFO", "JFK"}, { "JFK", "SFO" } });
	so.findItinerary({ {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} });
	so.findItinerary({ {"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"} });
}
/*
Test cases:

[["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]
[]
[["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
[["JFK","SFO"]]
[["JFK","SFO"],["SFO","JFK"]]
[["JFK","SFO"],["SFO","JFK"],["JFK","SFO"]]

Outputs:

["JFK","NRT","JFK","KUL"]
["JFK"]
["JFK","MUC","LHR","SFO","SJC"]
["JFK","ATL","JFK","SFO","ATL","SFO"]
["JFK","SFO"]
["JFK","SFO","JFK"]
["JFK","SFO","JFK","SFO"]
*/