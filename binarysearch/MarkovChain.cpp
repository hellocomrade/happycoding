#include <cassert>
#include <cstring>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;

namespace MarkovChain
{
	const int K = 2;
	char inputChars[5000];
	char *word[1000];
	int nword = 0;
	void populateText(const string &S)
	{
		int len = S.length();
		assert(len < 5000 - K);
		memset(word, NULL, 1000);
		strcpy(inputChars, S.c_str());
		char *pc = inputChars;
		char *itor = pc;
		do
		{
			/*
			* minic behavior of scanf, always adding null terminal automatically if go with %s
			* If we serve directly inside our code, space should be replaced by 0.
			*/
			while (' ' != *itor && 0 != *itor)++itor;
			word[nword++] = pc;
			//in case the string has multiple spaces between word boundaries
			while (' ' == *itor)
				*itor++ = 0;
			pc = itor;
		} while (0 != *itor);
		/*
		Make sure when skipUp2KWords is called, it won't pick up any garbage after the end of the string.
		*/
		word[nword] = ++itor;
		for (int i = 0; i < K; ++i)
			word[nword][i] = 0;
	}
	int sortCmp(const void *a, const void *b)
	{
		int n = K;
		//cast in C++, remove const first then to char**
		const char **p = static_cast<const char**>(const_cast<void*>(a));
		//cast in C, brutal
		const char **q = (const char**)b;
		/*
		In the following for loop, we will actually change the content of a and b: ++*p, ++*q.
		These changes should be reset when we are done. Otherwise, odd result will show up after sort.
		*/
		const char *p1 = *p;
		const char *q1 = *q;
		for (; **p == **q; ++*p, ++*q)
			if (0 == **p && 0 == --n)
			{
				*p = p1;
				*q = q1;
				return 0;
			}
		int rt = **p - **q;
		*p = p1;
		*q = q1;
		return rt;
	}
	void printFirstKWords(const char *words, int k)
	{
		while (k-- > 0)
		{
			while (0 != *words)
				cout << *words++;
			++words;
			cout << " ";
		}
	}
	char* skipUp2KWords(char *words, int n)
	{
		while (n-- > 0)
			while (0 != *(words++));
		return words;
	}
	void generator()
	{
		qsort(word, nword, sizeof(word[0]), sortCmp);
		/*char **ptr = word;
		while (NULL != *ptr)
		{
		cout << *ptr << endl;
		++ptr;
		}*/
		char *phrase = inputChars;//"people,\0by";
		char *p = nullptr;
		printFirstKWords(phrase, K);
		const int size = 10;
		srand(time(nullptr));
		for (int i = size; i > 0; --i)
		{
			int low = 0, high = nword - 1, lastHit = -1, mid, ret;
			while (low <= high)
			{
				mid = low + (high - low) / 2;
				/*
				we'd like the find the very first occurrence in the sequence that matches
				the first-k words of phrase. So, it's a looking-for-no-less-than
				*/
				/*cout << "***";
				printFirstKWords(word[mid], 2);
				cout << "|";
				printFirstKWords(phrase, 2);
				cout << endl;*/
				ret = sortCmp(&word[mid], &phrase);
				if (ret < 0)
					low = mid + 1;
				else
				{
					high = mid - 1;
					if (0 == ret)
						lastHit = mid;
				}
			}
			if (-1 == lastHit)
			{
				cerr << "no match..." << endl;
				break;
			}
			else
			{
				for (int i = lastHit; i < nword && 0 == sortCmp(&word[i], &phrase); ++i)
				{
					/*
					Make sure every match has the equal possibility to be chosen. For example:
					1st one: 1/1
					2nd one: 1/2
					3rd one: 1/3
					.
					.
					.
					n: 1/n

					The 1st one will be chosen as the default value, in case all following N matches
					fail to meet %
					*/
					if (0 == rand() % (i - lastHit + 1))
						p = word[i];
				}
				phrase = skipUp2KWords(p, 1);
				p = skipUp2KWords(phrase, K - 1);
				if (0 == strlen(p))
				{
					cerr << endl << "End game..." << endl;
					break;
				}
				else
					printFirstKWords(p, 1);
			}
		}
	}
}

void testMarkovChain()
{
	MarkovChain::populateText("of the people, by the people, for the people");
	MarkovChain::generator();
