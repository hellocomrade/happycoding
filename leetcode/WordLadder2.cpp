#include <cassert>
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

//https://leetcode.com/problems/word-ladder-ii/
/*
126. Word Ladder II

Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
[
["hit","hot","dot","dog","cog"],
["hit","hot","lot","log","cog"]
]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.

Observations:
As a "phase II" of word ladder (Leetcode 127), instead of finding the count of the minimum steps, K to transform from start to end,
we will have to find all "shortest pathes" with K steps.

In Leetcode 127, we built a hash table with keys using wild card '?'. So, instead of trying all 26 alphabets against a given word,
we only replace each letter in the given word with '?'. This is usually a good way to boost the performance considering the fact most
of English words are way less than 26 letters each.

However, in this one, we gave up that idea because I was afraid that we will use too much memory and take too long to complete the algorithm.
Why? Since we are asked to find all possible shortest path, in order to save memory, we may have to take backtracing approach. This will normally
requires a DFS built in a recursive approach. Somehow, before we do that, we need to create a structure that is comprehensive enough to track
all possible routes between start till end.

This can be done using a BFS. We first introduce string end as a virtual node into dict so we would have an ending point for our Breadth First Search.
Then starting from string start, we find all immediate neighbors who meet the transform rule for a given node. At meantime, we keep tracking the order of
the given node. All neighbors will then be pushed to a queue as long as they haven't been accessed before. This process will stop once we reach string end.

Is this sufficient enough to cover all nodes we need to examine? Yes, since we are doing BFS, once we have reached the string end, it is guaranteed that the detination
will be reached as earliest as it can and all nodes that can transfer to the string end have already put string end onto their neighbor list. All other nodes that are not reached yet at this moment are definitely irrelevant to
shortest path scan.

An interesting bug of passing value of a vector instead of its reference, which introduced huge performance penalty since this is done during
the recursion.
*/
class SolutionWordLadder2 {
private:
	/*
	DFS
	The arugment list was written as vector<string> vec, which influenced the performance hugely due to the extensive copy construction on vec!
	Once that has been corrected, we have this algorithm ACed.
	*/
	void aux(vector<vector<string>>& ans, vector<string>& vec, unordered_map<string, std::pair<vector<string>, int>>& g, const string& start, const string& end, int order) {
		vec[order] = start;
		if (end == start) {
			ans.push_back(std::move(vector<string>(vec.begin(), vec.begin() + order + 1)));
			return;
		}
		for (auto& str : g[start].first)
			if (g[str].second == order + 1)
				this->aux(ans, vec, g, str, end, order + 1);
	}
public:
	/**
	* @param start, a string
	* @param end, a string
	* @param dict, a set of string
	* @return a list of lists of string
	*/
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		vector<vector<string>> ans;
		/*
		in the pair, the vector contains all immediate and legal children of the node, int is the order of the node
		*/
		unordered_map<string, std::pair<vector<string>, int>> g;
		/*
		Put end on the dict to make sure we have an ending point on the graph
		*/
		dict.emplace(end);
		size_t len = start.length();
		char old_char = 0;
		string str, key;
		queue<string> q;
		q.push(start);
		while (false == q.empty()) {
			key = std::move(q.front()); q.pop();
			if (key == end) break;
			str = key;
			/*
			Since we use a huge structure to store graph info, g[key] should be created already when we set up its order during BFS.
			This is only for the string start as the key.
			BTW, for an existing key-value in unordered_map, try to emplace again will simply be ignored. In other words, newly given
			value will NOT replace the existing one.
			*/
			if (start == key)
				g.emplace(key, std::make_pair(vector<string>(), 0));
			for (size_t i = 0; i < len; ++i) {
				for (char j = 'a'; j <= 'z'; ++j) {
					if (j == str[i])continue;
					old_char = str[i];
					str[i] = j;
					if (dict.end() != dict.find(str)) {
						/*
						We will only process for the following two conditions:
						1. Node str has not been visited yet during a BFS. This can be confirmed by g.find(str) == g.end();
						2. Node str has been visited. However, the current key's order is one level above node str. In other
						words, according to the transform rule and common sense of a "shortest path", node key to node str
						is legit and str should be considered as key's legal child even though str has other parent(s).
						*/
						if (g.end() == g.find(str) || g[str].second == g[key].second + 1) {
							/*
							If g.find on str returns end, it means node str has not been visited yet
							*/
							if (g.end() == g.find(str)) {
								/*
								we should only push str to the queue if str hasn't be on the queue before.
								otherwise, we will introduce duplications onto the neighor list of str.
								*/
								q.push(str);
								g.emplace(str, std::make_pair(vector<string>(), g[key].second + 1));
							}
							/*
							however, we will put str onto key's neighor list even str is accessed before for an obvious reason:
							we need to find all possible routes even they may overlap in between (not completely though). In such
							scenario, str has multiple parents.
							*/
							g[key].first.push_back(str);
						}
					}
					str[i] = old_char;
				}
			}
		}
		vector<string> vec(dict.size() + 2);
		this->aux(ans, vec, g, start, end, 0);
		return ans;
	}
};
void TestWordLadder2() {
	SolutionWordLadder2 so;
	unordered_set<string> dict1;
	dict1.insert("a");
	dict1.insert("b");
	dict1.insert("c");
	vector<vector<string>> ans1 = so.findLadders("a", "c", dict1);
	assert(1 == ans1.size() && 2 == ans1[0].size() && "a" == ans1[0][0] && "c" == ans1[0][1]);

	unordered_set<string> dict2;
	dict2.insert("hot");
	dict2.insert("dot");
	dict2.insert("dog");
	dict2.insert("lot");
	dict2.insert("log");
	vector<vector<string>> ans2 = so.findLadders("hit", "cog", dict2);
	assert(2 == ans2.size() && 5 == ans2[0].size() && 5 == ans2[1].size());

	unordered_set<string> dict3;
	dict3.insert("hot");
	dict3.insert("cog");
	dict3.insert("dog");
	dict3.insert("tot");
	dict3.insert("hog");
	dict3.insert("hop");
	dict3.insert("pot");
	dict3.insert("dot");
	vector<vector<string>> ans3 = so.findLadders("hot", "dog", dict3);
	assert(2 == ans3.size() && 3 == ans3[0].size() && 3 == ans3[1].size());

	unordered_set<string> dict7;
	unordered_set<string> dict8;
	vector<string> candidates1{ "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob", "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt" };
	vector<string> candidates0{ "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay", "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal", "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit", "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row", "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has", "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu", "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy", "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply", "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan", "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye", "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot", "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib", "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm", "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk", "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag", "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic", "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his", "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod", "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib", "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr", "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap", "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx", "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set", "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao", "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap", "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky", "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo", "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva", "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep", "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed", "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum", "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem", "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen", "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit", "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken", "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin", "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui", "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo", "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas", "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio", "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit", "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix", "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid", "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil", "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig", "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty", "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug", "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot", "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism", "err", "him", "all", "pad", "hah", "hie", "aim", "ike", "jed", "ego", "mac", "baa", "min", "com", "ill", "was", "cab", "ago", "ina", "big", "ilk", "gal", "tap", "duh", "ola", "ran", "lab", "top", "gob", "hot", "ora", "tia", "kip", "han", "met", "hut", "she", "sac", "fed", "goo", "tee", "ell", "not", "act", "gil", "rut", "ala", "ape", "rig", "cid", "god", "duo", "lin", "aid", "gel", "awl", "lag", "elf", "liz", "ref", "aha", "fib", "oho", "tho", "her", "nor", "ace", "adz", "fun", "ned", "coo", "win", "tao", "coy", "van", "man", "pit", "guy", "foe", "hid", "mai", "sup", "jay", "hob", "mow", "jot", "are", "pol", "arc", "lax", "aft", "alb", "len", "air", "pug", "pox", "vow", "got", "meg", "zoe", "amp", "ale", "bud", "gee", "pin", "dun", "pat", "ten", "mob" };
	for (auto s : candidates0)
		dict7.emplace(s);
	for (auto s : candidates1)
		dict8.emplace(s);
	assert(11 == so.findLadders("cet", "ism", dict7)[0].size());
	assert(11 == so.findLadders("cet", "ism", dict8)[0].size());
}