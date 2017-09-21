#include <cassert>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/max-points-on-a-line/
/*
149. Max Points on a Line

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Observations:
Straight line equations have couple forms.
General form: A * X + B * Y + C = 0
Given two points P1(X1, Y1) and P2(X2, Y2), P1 and P2 are not the same
A = Y2 - Y1
B = X1 - X2
C = X2 * Y1 - X1 * Y2
Slope-Intercept form: K * X + B = Y
Given two points P1(X1, Y1) and P2(X2, Y2),
K = (Y2 - Y1) / (X2 - X1)
B =

General form works for all edge cases, but slope-intercept form can't work if X2 is equal to X1.

Since we have the presumption that hash table will be used, we need to define the key for the table. If we
take the slope K as the key, we may run into trouble coz the slope is a double number and the hashed values
may be different for two doubles that are considered equal.

We need an alternative here by using the numerator/denominator form. The complications are:
1. C++ doesn't have hash function for std::pair unless you define you own. So, I chose using stringified
number combination;
2. That 6/4 and 3/2 result in the same slope, however they have different representations. Therefore, we
will have to convert 6/4 to 3/2 by their greatest common divisor, I call it standardized form;
A even wild scenario is like: -3/2 and 3/-2.

Generally speaking, the general form of line's equation actually works better since it covers all edge cases.
The downside is that you have to store the combination of A, B and C.

By a close look on the nature of the problem, if we do brute force, it takes O(N^3). If we scan the points array
from left to right, the first point needs to check n - 1 points, the second point needs to check n - 2 points.
This way, it only takes O(N^2) time. in each iteration, we have a base point points[i], if lines
{points[j], points[i]} and {points[m], points[i]} both have same slope k, the three points shall be on the same
line since they share the same endian points[i]. In this context, C in the general form is not important anymore
for regular cases as long as we have a fresh hashtable for each iteration.

This pushes us back to the idea of using the numerator/denominator form of the slope. In this scenario, the
edge cases are vertical and horizontal lines. For vertical line, the standardized form is X = N, N is a constant,
Horizontal lines is Y = N; For other regular one, we could leave C to 0 as long as we refresh the hashtable on
each iteration.

One last thing is the duplicated points. I handle them by sorting the points first. Then during the scanning,
the duplicated point with points[i] will be skipped and the counting is on. We then append the duplicate count onto
the final result.

By a second thought, sorting is unnecessary, we still have to handle duplicates though. We don't care the oder of these points
anyway. Actually, there would be lots of repeat calacuations, for example pnt0, pnt1, and pntN are on one line.
When we start from pnt0, we get 3 points; next iteration is based on pnt1, the same line, we get 2 points (pnt1 and pntN). So,
it won't affect the final answer, just waste time...

One more thing to point out is that hashing on double type might not be safe:
https://stackoverflow.com/questions/7403210/hashing-floating-point-values
*/
namespace MaxPointsOnLine {
	struct Point {
		int x;
		int y;
		Point() : x(0), y(0) {}
		Point(int a, int b) : x(a), y(b) {}
	};
	class SolutionMaxPointsOnLine {
	private:
		int gcd(int a, int b)
		{
			return b == 0 ? a : gcd(b, a % b);
		}
	public:
		int maxPoints(vector<Point>& points) {
			long long ans = 1, maxsofar = 0, dupCnt = 0, a, b, g;
			size_t len = points.size();
			if (len > 1) {
				unordered_map<long long, unordered_map<long long, unordered_map<double, long long>>> map;
				double c;
				for (size_t i = 0; i < len - 1; ++i) {
					for (size_t j = i + 1; j < len; ++j) {
						if (points[j].y == points[i].y && points[i].x == points[j].x) {
							++dupCnt;
							continue;
						}
						a = points[j].y - points[i].y;
						b = points[i].x - points[j].x;
						c = points[j].x * points[i].y * 1LL - points[i].x * points[j].y * 1LL;
						g = this->gcd(a, b);
						if (0 != g)
							a /= g, b /= g, c /= g;
						if (map.end() == map.find(a))map.emplace(a, unordered_map<long long, unordered_map<double, long long>>());
						if (map[a].end() == map[a].find(b))map[a].emplace(b, unordered_map<double, long long>());
						if (map[a][b].end() == map[a][b].find(c))
							map[a][b].emplace(c, 2);
						else
							++map[a][b][c];
						maxsofar = std::max(maxsofar, map[a][b][c]);
					}
					if (0 == maxsofar)
						++dupCnt;
					ans = std::max(ans, maxsofar + dupCnt);
					dupCnt = maxsofar = 0;
					map.clear();
				}
			}
			return 0 == len ? 0 : ans;
		}
		int maxPoints1(vector<Point>& points) {
			auto comp = [](const Point &p1, const Point &p2) {
				if (p1.x < p2.x)return true;
				else if (p1.x == p2.x && p1.y < p2.y)return true;
				else return false;
			};
			int len = points.size();
			if (len < 1 || len == 1)return len;
			std::sort(points.begin(), points.end(), comp);
			int a = 0, b = 0, c = 0, x = 0, y = 0;
			long long maxCnt = 0, dupCnt = 0, ans = 1;
			unordered_map<std::string, long long> map;
			for (int i = 0; i < len - 1; ++i)
			{
				maxCnt = 0, x = points[i].x, y = points[i].y;
				if (x == points[i + 1].x && y == points[i + 1].y)
				{
					++dupCnt;
					continue;
				}
				map.clear();
				for (int j = i + 1; j < len; ++j)
				{
					a = points[j].y - y;
					b = points[j].x - x;
					int g = this->gcd(a, b);
					a /= g;
					b /= g;
					c = (a == 0) ? y : (b == 0) ? x : 0;
					std::ostringstream os;
					os << a << ',' << b << ',' << c;
					string s = os.str();
					//cout << s << endl;
					if (map.find(s) != map.end())
						++map[s];
					else
						map.emplace(s, 2);
					maxCnt = std::max(maxCnt, map[s]);
				}
				ans = std::max(maxCnt + dupCnt, ans);
				dupCnt = 0;
			}
			/*
			one exception is that lots of duplicates are on the end of the array including the last one,
			so, no calcuation is done and ans never got updated, so we will have to patch it at the end.
			*/
			return std::max(ans, dupCnt + 1);
		}
	};
}
void TestMaxPointsOnLine()
{
	using MPOL = MaxPointsOnLine::SolutionMaxPointsOnLine;
	using Point = MaxPointsOnLine::Point;
	MPOL so;

	vector<Point> pnts00;
	pnts00.emplace_back(Point(0, 0));
	pnts00.emplace_back(Point(-1, -1));
	pnts00.emplace_back(Point(2, 2));
	assert(3 == so.maxPoints(pnts00));

	vector<Point> pnts1;
	pnts1.emplace_back(Point(1, 1));
	pnts1.emplace_back(Point(1, 2));
	pnts1.emplace_back(Point(1, 3));
	pnts1.emplace_back(Point(2, 1));
	pnts1.emplace_back(Point(1, 1));
	pnts1.emplace_back(Point(0, 0));
	pnts1.emplace_back(Point(1, 1));
	assert(5 == so.maxPoints(pnts1));

	vector<Point> pnts0;
	pnts0.emplace_back(Point(1, 2));
	pnts0.emplace_back(Point(3, 6));
	pnts0.emplace_back(Point(0, 0));
	pnts0.emplace_back(Point(1, 3));
	assert(3 == so.maxPoints(pnts0));



	vector<Point> pnts2;
	pnts2.emplace_back(Point(1, 1));
	pnts2.emplace_back(Point(1, 2));
	assert(2 == so.maxPoints(pnts2));

	vector<Point> pnts3;
	pnts3.emplace_back(Point(0, 0));
	pnts3.emplace_back(Point(1, 0));
	assert(2 == so.maxPoints(pnts3));

	vector<Point> pnts4;
	pnts4.emplace_back(Point(0, 0));
	pnts4.emplace_back(Point(0, 0));
	assert(2 == so.maxPoints(pnts4));

	vector<Point> pnts5;
	pnts5.emplace_back(Point(1, 1));
	pnts5.emplace_back(Point(1, 1));
	pnts5.emplace_back(Point(2, 2));
	pnts5.emplace_back(Point(2, 2));
	assert(4 == so.maxPoints(pnts5));
}