int gcd(int a, int b)
{
	return b == 0 ? 0 : gcd(b, a % b);
}
int lcm(int a, int b)
{
	if (0 == b)return 0;
	return a*gcd(a, b) / b;
}
//https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
int extgcd(int a, int b, int &x, int &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = extgcd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return d;
}
