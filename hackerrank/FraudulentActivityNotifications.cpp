#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
/*
Fraudulent Activity Notifications

HackerLand National Bank has a simple policy for warning clients about possible fraudulent account activity.
If the amount spent by a client on a particular day is greater than or equal to 2X the client's median spending for a trailing number of days, they send the client a notification about potential fraud.
The bank doesn't send the client any notifications until they have at least that trailing number of prior days' transaction data.

Given the number of trailing days d and a client's total daily expenditures for a period of n days, find and print the number of times the client will receive a notification over all n days.

For example, d =3 and expenditures = [10, 20, 30, 40, 50]. On the first three days, they just collect spending data. At day 4,
we have trailing expenditures of [10, 20, 30]. The median is 20 and the day's expenditure is 40. Because 40 >= 2 X 20, there will be a notice.
The next day, our trailing expenditures are [20, 30, 40] and the expenditures are 50. This is less than 2 X 30 so no notice will be sent. Over the period, there was one notice sent.

Note: The median of a list of numbers can be found by arranging all the numbers from smallest to greatest. If there is an odd number of numbers,
the middle one is picked. If there is an even number of numbers, median is then defined to be the average of the two middle values.

Function Description

Complete the function activityNotifications in the editor below. It must return an integer representing the number of client notifications.

activityNotifications has the following parameter(s):

- expenditure: an array of integers representing daily expenditures
- d: an integer, the lookback days for median spending

Input Format

The first line contains two space-separated integers n and d, the number of days of transaction data, and the number of trailing days' data used to calculate median spending.
The second line contains n space-separated non-negative integers where each integer i denotes expenditure[i].

Constraints

- 1 <= n <= 2 * 10^5
- 1 <= d <= n
- 0 <= expenditure[i] <= 200

Output Format

Print an integer denoting the total number of times the client receives a notification over a period of n days.

Sample Input 0

9 5

2 3 4 2 3 6 8 4 5

Sample Output 0

2

Explanation 0

We must determine the total number of notifications the client receives over a period of n = 9 days.
For the first five days, the customer receives no notifications because the bank has insufficient transaction data: notifications = 0.

On the sixth day, the bank has d = 5 days of prior transaction data, {2, 3, 4, 2, 3}, and median = 3 dollars. The client spends 6 dollars, which triggers a notification because 6 >= 2 X median: notification = 0 + 1 = 1.

On the seventh day, the bank has d = 5 days of prior transaction data, {3, 4, 2, 3, 6}, and median = 3 dollars. The client spends 8 dollars, which triggers a notification because 8 >= 2 X median: notification = 1 + 1 = 2.

On the eighth day, the bank has d = 5 days of prior transaction data, {4, 2, 3, 6, 8}, and median = 4 dollars. The client spends 4 dollars, which does not trigger a notification because 4 < 2 X median: notification = 2.

On the ninth day, the bank has d = 5 days of prior transaction data, {2, 3, 6, 8, 4}, and a transaction median of 4 dollars. The client spends 5 dollars, which does not trigger a notification because 5 < 2 X median: notification = 2.

Sample Input 1

5 4

1 2 3 4 4

Sample Output 1

0

There are  days of data required so the first day a notice might go out is day . Our trailing expenditures are  with a median of  The client spends  which is less than  so no notification is sent.

Observations:

All descriptions above can be translated to two lines of text:

In a given array, pick the last n elements, get their median, then compare the median with the current element. If current element is
at least 2 times of median, count plus one.

In a naive approach, one can maintain a vector with size k to track the last k elements. Sort this vector in every iteration.
This will take (N - k)*k*log(k), given N is the size of the expenditure.

Note 0 <= expenditure[i] <= 200, then bucket sort can be applied so the sorting will only take O(1) given the max is 200.
Overall time complexity can be reduce to O(N).

Also, hackerrank recommended another problem "Finding the Running Median" asking for calcuating continuous median on an array,
which can be sloved in NlogN by using 2 heaps.
*/
namespace FraudulentActivityNotifications {
	vector<string> split_string(string);

	class FraudulentActivityNotifications {
	public:
		int activityNotifications(vector<int> expenditure, int d) {
			int len = (int)expenditure.size(), ans = 0;
			vector<int> buckets(201, 0);
			for (int i = 0, j = 0, k = 0, cnt = 0, cnt1 = 0, mid = 0; i < len; cnt1 = 0, ++i) {
				if (d > cnt++) ++buckets[expenditure[i]];
				else {
					mid = 1 == (d & 1) ? d / 2 + 1 : d / 2;
					for (j = 0; j < 201; ++j) {
						cnt1 += buckets[j];
						if (cnt1 >= mid) break;
					}
					if (1 == (d & 1) || cnt1 > mid) { if (2 * j <= expenditure[i]) ++ans; }
					else {
						for (k = j + 1; k < 201; ++k) if (buckets[k] > 0) break;
						if ((k + j) <= expenditure[i]) ++ans;
					}
					--buckets[expenditure[i - d]], ++buckets[expenditure[i]];
				}
			}
			return ans;
		}
	};
	vector<string> split_string(string input_string) {
		string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
			return x == y && x == ' ';
		});

		input_string.erase(new_end, input_string.end());

		while (input_string[input_string.length() - 1] == ' ') {
			input_string.pop_back();
		}

		vector<string> splits;
		char delimiter = ' ';

		size_t i = 0;
		size_t pos = input_string.find(delimiter);

		while (pos != string::npos) {
			splits.push_back(input_string.substr(i, pos - i));

			i = pos + 1;
			pos = input_string.find(delimiter, i);
		}

		splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

		return splits;
	}
}
int TestFraudulentActivityNotifications()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string nd_temp;
	getline(cin, nd_temp);

	namespace FAN = FraudulentActivityNotifications;
	vector<string> nd = FAN::split_string(nd_temp);

	int n = stoi(nd[0]);

	int d = stoi(nd[1]);

	string expenditure_temp_temp;
	getline(cin, expenditure_temp_temp);

	vector<string> expenditure_temp = FAN::split_string(expenditure_temp_temp);

	vector<int> expenditure(n);

	for (int i = 0; i < n; i++) {
		int expenditure_item = stoi(expenditure_temp[i]);

		expenditure[i] = expenditure_item;
	}
	FAN::FraudulentActivityNotifications so;
	int result = so.activityNotifications(expenditure, d);

	fout << result << "\n";

	fout.close();

	return 0;
}