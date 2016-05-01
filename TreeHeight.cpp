#include <algorithm>
#include <iostream>
using namespace std;

//https://codility.com/demo/results/trainingREH34X-UHV/
struct tree {
	int x;
	tree * l;
	tree * r;
};
int solutionTreeHeightAux(tree * T)
{
	if (nullptr == T)
		return 0;
	int left = solutionTreeHeightAux(T->l);
	int right = solutionTreeHeightAux(T->r);
	return 1 + std::max(left, right);
}
int solutionTreeHeight(tree * T)
{
	return solutionTreeHeightAux(T) - 1;
}
int solutionTreeHeight1(tree * T)
{
	if (nullptr == T)
		return -1;
	return 1 + std::max(solutionTreeHeight1(T->l), solutionTreeHeight1(T->r));
}
void testTreeHeight()
{
	tree t20{ 20, nullptr, nullptr };
	tree t21{ 21, nullptr, nullptr };
	tree t1{ 1, nullptr, nullptr };
	tree t3{ 3, &t20, &t21 };
	tree t10{ 10, &t1, nullptr };
	tree root5{ 5, &t3, &t10 };
	cout << "Expect 2: " << solutionTreeHeight1(&root5) << endl;

	tree t22{ 22, nullptr, nullptr };
	tree t19{ 19, &t22, nullptr };
	tree t18{ 18, &t19, nullptr };
	tree root1{ 1, &t18, nullptr };
	cout << "Expect 3: " << solutionTreeHeight1(&root1) << endl;

	tree root2{ 2, nullptr, nullptr };
	cout << "Expect 0: " << solutionTreeHeight1(&root2) << endl;

	cout << "Expect -1: " << solutionTreeHeight1(nullptr) << endl;
}