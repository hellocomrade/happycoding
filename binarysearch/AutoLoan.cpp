#include <cassert>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;
/*
This is NOT fully tested or verified yet, so you should NOT trust it.

Apply binary search on low and high in double format. No need to worry infinite loop by m+1 or m-1
However, we still need to define a condition to exit the loop, usually an error level we can tolerate.

There are still questions: it appears montlyPayment * loanTerm should always be greater than the total
loan amount if we'd like to find a meaning APR. On the other hand, there seems to be a upper boundary
as well that no valid apr is available if that limit is exceeded. See the second to the last testing case.
*/
double AutoLoanAPR(double balance, double monthlyPayment, int loanTerm)
{
	const double precision = 5E-3;
	const double error = 1E-10;
	assert(balance > 1.0 || std::abs(1.0 - balance) <= precision);
	assert(balance < 1000000.0 || std::abs(1000000.0 - balance) <= precision);
	assert(monthlyPayment > 0.0 || monthlyPayment <= precision);
	assert(monthlyPayment < balance / 2.0 || std::abs(balance / 2.0 - monthlyPayment) <= precision);
	if (monthlyPayment * loanTerm < balance)
		return -1.0;
	else if (std::abs(monthlyPayment * loanTerm - balance) <= precision)
		return 0.0;
	double l = 0.0, h = 100.0, m, p, b;
	while (std::abs(h - l) > error)
	{
		m = l + (h - l) / 2.0;
		p = m / (100 * 12);
		b = balance;
		int i = 0;
		for (i = 0; i < loanTerm; ++i)
			b -= (monthlyPayment - b * p);
		/*
		we don't have to worry infinite loop here by adding/substracting 1 on l or h,
		since we are dealing floating point numbers. They will never really identical
		*/
		if (b > error)
			h = m; //apr is too high, never be able to pay off, therefore lower it
		else
			l = m;
	}
	//an apri is valid only if the remaing balance is zero after the full term
	return std::abs(b) <= precision ? m : -1;
}
void testAutoLoanAPR()
{
	//The return value must be within 1e-9 absolute or relative error of the actual result.
	cout << "Expect 9.56205462458368 +/- 1e-9: " << std::setprecision(12) << AutoLoanAPR(2000.0, 510.0, 4) << endl;
	cout << "Expect 7.687856394581649 +/- 1e-9: " << std::setprecision(12) << AutoLoanAPR(15000.0, 364.0, 48) << endl;
	cout << "Expect 1.3322616182218813E-13 +/- 1e-9: " << std::setprecision(12) << AutoLoanAPR(6800.0, 100.0, 68) << endl;
	cout << "Expect 65.661500558: " << std::setprecision(12) << AutoLoanAPR(1, .2, 6) << endl;
	cout << "Expect -1: " << std::setprecision(12) << AutoLoanAPR(1, .2, 7) << endl;
}