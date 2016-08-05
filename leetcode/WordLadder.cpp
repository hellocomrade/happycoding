#include <cassert>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <iostream>

using namespace std;
using WordLadderGraph = unordered_map<string, std::pair<vector<string>, int> >;

//https://leetcode.com/problems/word-ladder/
/*
127. Word Ladder

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.

Observations:
First of all, I completely failed on this one. Can't finish coding in 30 minutes.

According to the description, graph BFS should be the direction to go since we are looking for the "shortest"
distance between start to end. That has been said, it has been proved that building the complete graph up front (see the following attempts)
will not meet the time requirement.

Therefore, we have to build the graph-like BFS on the fly by using dict as the lookup table. According to the given test cases,
most of strings are very short, it's faster to use back tracing here by temporarily replacing the character in given string str by [a-z],
then we check if such string exists in dict. If so, we are sure we find a neighbor of str. Put this neighbor on a queue for the next round BFS.
For BFS search, we apply the similar approach for tree level search: only the elements in the queue on the same level are considered. This can be
done by having the size of the queue up front in each iteration.

Another "flaw" of my slow algorithm is that the comparison on strings are done through isNextStep. This should be faster than the approach above on
each run. However, since the test cases have hundreds of short strings, the overall performance is worse since the other one only do 26 * O(1) * number_of_neighbors.
O(1) refers to the lookup on unordered_set.

The best approach below is still too slow. More study is necessary to boost the performance.
*/
class SolutionWordLadder {
private:
	bool isNextStep(const string& s1, const string& s2, int strLen) {
		int cnt = 0, idx = 0;
		while (idx < strLen) {
			if (s1[idx] == s2[idx])++cnt;
			++idx;
		}
		return cnt >= strLen - 1;
	}
	WordLadderGraph bulidGraph(unordered_set<string> &dict, int strLen) {
		WordLadderGraph map;
		auto end = dict.end();
		auto mend = map.end();
		for (auto itor = dict.begin(); itor != end;) {
			if (map.find(*itor) == mend)
				map.emplace(*itor, std::make_pair(vector<string>{}, 0));
			for (auto itor1 = dict.begin(); itor1 != end; ++itor1) {
				if (*itor == *itor1)continue;
				if (true == this->isNextStep(*itor, *itor1, strLen)) {
					map[*itor].first.push_back(*itor1);
					if (map.find(*itor1) == mend)
						map.emplace(*itor1, std::make_pair(vector<string>{}, 0));
					map[*itor1].first.push_back(*itor);
				}
			}
			itor = dict.erase(itor);
		}
		return map;
	}
public:
    //212 ms
    //Preprocess words using ? ask wildcard, for example, hit will be put under three keys: "?it",
    //"h?t" and "hi?". All other words following the same pattern will be appended to the vector
    //under the key,
    //Having this in hand, we reduce the comparison from 26 [a - z] to the lenght of the words,
    //they all have the same length, which is way less than 26 for test cases.
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        if (start == end)return 1;
        int len = start.length(), size = 0, dist = 1;
        char mask = '?', oldChar = 0;
        string strClone;
        unordered_map<std::string, vector<std::string> > maps;
        auto endMap = maps.end();
        dict.erase(start);
        dict.emplace(end);
        for(string str : dict) {
            if(str.length() != len)return 0;
            strClone = str;
            for(int i = 0; i < len; ++i) {
                oldChar = str[i];
                str[i] = mask;
                if(maps.find(str) == endMap)maps.emplace(str, vector<string>());
                maps[str].push_back(strClone);
                str[i] = oldChar;
            }
        }
        queue<string> q;
        q.push(start);
        while(false == q.empty()) {
            size = q.size();
            for(int i = 0; i < size; ++i) {
                strClone = q.front(); q.pop();
                //the following loop really reduce the time complexity for given test cases
                for(int j = 0; j < len; ++j) {
                    oldChar = strClone[j];
                    strClone[j] = mask;
                    if(maps.find(strClone) != endMap) {
                        for(string str : maps[strClone]) {
                            if(str == end)
                                return dist + 1;
                            q.push(str);
                        }
                        maps.erase(strClone);
                    }
                    strClone[j] = oldChar;
                }
            }
            ++dist;
        }
        return 0;
    }
    //Still slow, 284ms...
    int ladderLength4(string start, string end, unordered_set<string> &dict) {
		if (start == end)return 1;
		char oc = 0;
		int len = start.length(), distance = 1, qsize = 0;
		if (dict.size() > 0) {
			if (dict.find(start) != dict.end())dict.erase(start);
			if (dict.find(end) == dict.end())dict.emplace(end);
			queue<string> q;
			q.push(start);
			while (false == q.empty()) {
				qsize = q.size();
				for (int i = 0; i < qsize; ++i) {
					string s = q.front(); q.pop();
					if (s == end)
						return distance;
					for (int i = 0; i < len; ++i) {
						oc = s[i];
						for (char c = 'a'; c <= 'z'; ++c) {
							s[i] = c;
							if (dict.find(s) != dict.end()) {
								q.push(s);
								dict.erase(s);
							}
						}
						s[i] = oc;
					}
				}
				++distance;
			}
		}
		return 0;
	}
	//Toooooo slow
	int ladderLength3(string beginWord, string endWord, unordered_set<string>& wordList) {
		if (beginWord == endWord)return 1;
		int len = beginWord.length(), size = wordList.size(), distance = 1, qsize = 0;
		if (this->isNextStep(beginWord, endWord, len) == true)return 2;
		if (size > 0) {
			if (wordList.find(endWord) == wordList.end())
				wordList.emplace(endWord);
			queue<string> q;
			q.push(beginWord);
			while (false == q.empty()) {
				qsize = q.size();
				for (int i = 0; i < qsize; ++i) {
					string s = q.front(); q.pop();
					if (s == endWord)
						return distance;
					for (auto itor = wordList.begin(); itor != wordList.end();) {
						if (true == this->isNextStep(*itor, s, len)) {
							q.push(*itor);
							itor = wordList.erase(itor);
						}
						else ++itor;
					}
				}
				++distance;
			}
		}
		return 0;
	}
	//time out
	int ladderLength2(string start, string end, unordered_set<string> &dict) {
		int len = start.length(), size = dict.size();
		if (this->isNextStep(start, end, len) == true)return 2;
		if (size > 0) {
			unordered_map<string, int> distance;
			if (dict.find(start) == dict.end())
				dict.emplace(start);
			WordLadderGraph graph = this->bulidGraph(dict, len);
			if (0 == graph[start].first.size())return 0;
			queue<string> q;
			q.push(start);
			graph[start].second = 1;
			distance[start] = 1;
			while (false == q.empty()) {
				string s = q.front(); q.pop();
				if (true == this->isNextStep(s, end, len))
					return distance[s] + (s == end ? 0 : 1);
				for (string neighbor : graph[s].first) {
					if (graph[neighbor].second == 0) {
						graph[neighbor].second = 1;
						distance[neighbor] = distance[s] + 1;
						q.push(neighbor);
					}
				}
				graph[s].second = 2;
			}
		}
		return 0;
	}
	//Time out
	/**
	* @param start, a string
	* @param end, a string
	* @param dict, a set of string
	* @return an integer
	*/
	int ladderLength1(string start, string end, unordered_set<string> &dict) {
		int ans = 0, len = start.length(), size = dict.size();
		if (this->isNextStep(start, end, len) == true)return 2;
		if (size > 0) {
			ans = size + 2 + 1;
			vector<string> firstStep;
			unordered_map<string, int> distance;
			for (auto itor = dict.begin(); itor != dict.end(); ++itor) {
				if (true == this->isNextStep(start, *itor, len))firstStep.push_back(*itor);
				distance[*itor] = 0;
			}
			if (0 == firstStep.size())return 0;
			WordLadderGraph graph = this->bulidGraph(dict, len);
			queue<string> q;
			for (string step1 : firstStep) {
				///The follow code will not update graph, since auto was inferred as a pair and 
				//pass by value instead of reference
				/*for (auto p : graph) {
				distance[p.first] = 0;
				p.second.second = 0;
				}*/
				for (auto p = graph.begin(); p != graph.end(); ++p) {
					distance[p->first] = 0;
					p->second.second = 0;
				}
				q.push(step1);
				graph[step1].second = 1;
				distance[step1] = start == step1 ? 1 : 2;
				while (false == q.empty()) {
					string s = q.front(); q.pop();
					if (true == this->isNextStep(s, end, len))
						ans = std::min(distance[s] + (s == end ? 0 : 1), ans);
					for (string neighbor : graph[s].first) {
						if (graph[neighbor].second == 0) {
							graph[neighbor].second = 1;
							distance[neighbor] = distance[s] + 1;
							q.push(neighbor);
						}
					}
					graph[s].second = 2;
				}
			}
		}
		return ans == size + 3 ? 0 : ans < 2 ? 2 : ans;
	}
};
void TestWordLadder() {
	unordered_set<string> dict;
	dict.emplace("hot");
	dict.emplace("dot");
	dict.emplace("dog");
	dict.emplace("lot");
	dict.emplace("log");
	SolutionWordLadder so;
	assert(5 == so.ladderLength("hit", "cog", dict));

	unordered_set<string> dict1;
	dict1.emplace("a");
	dict1.emplace("b");
	dict1.emplace("c");
	assert(2 == so.ladderLength("a", "c", dict1));

	unordered_set<string> dict4;
	dict4.emplace("hot");
	dict4.emplace("dot");
	dict4.emplace("dog");
	assert(2 == so.ladderLength("hot", "dot", dict4));

	unordered_set<string> dict2;
	dict2.emplace("hit");
	assert(1 == so.ladderLength("hot", "hot", dict2));

	unordered_set<string> dict9;
	dict9.emplace("b");
	assert(1 == so.ladderLength("a", "a", dict9));

	unordered_set<string> dict3;
	dict3.emplace("ab");
	assert(3 == so.ladderLength("sb", "ae", dict3));

	unordered_set<string> dict5;
	dict5.emplace("red");
	dict5.emplace("tax");
	dict5.emplace("ted");
	dict5.emplace("tex");
	dict5.emplace("red");
	dict5.emplace("tax");
	dict5.emplace("tad");
	dict5.emplace("den");
	dict5.emplace("rex");
	dict5.emplace("pee");
	assert(4 == so.ladderLength("red", "tax", dict5));

	unordered_set<string> dict6;
	dict6.emplace("dot");
	dict6.emplace("doe");
	assert(3 == so.ladderLength("hot", "doe", dict6));

	unordered_set<string> dict7;
	unordered_set<string> dict8;
	vector<string> candidates1{ "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob", "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt" };
	vector<string> candidates0{ "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob" };
	/*for (auto s : candidates0)
	dict7.emplace(s);
	for (auto s : candidates1)
	dict8.emplace(s);
	WordLadderGraph g0 = so.bulidGraph(dict7, 3);
	WordLadderGraph g1 = so.bulidGraph(dict8, 3);
	for (auto p : g0) {
	auto q = g1[p.first];
	if(false == std::is_permutation(q.first.begin(), q.first.end(), p.second.first.begin()))
	cout << p.first << endl;
	}*/
	for (auto s : candidates0)
		dict7.emplace(s);
	for (auto s : candidates1)
		dict8.emplace(s);
	assert(11 == so.ladderLength("cet", "ism", dict7));
	assert(11 == so.ladderLength("cet", "ism", dict8));
}