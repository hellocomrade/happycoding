#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/design-twitter/
/*
355. Design Twitter

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

postTweet(userId, tweetId): Compose a new tweet.

getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.

follow(followerId, followeeId): Follower follows a followee.

unfollow(followerId, followeeId): Follower unfollows a followee.

Example:

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);

Observations:

This is really a good interview question for testing applicant's design skills using a case that everyone understands!

First of all, one will need a Tweet class, which stores:

1. User ID;
2. Tweet ID;
3. Timestamp;

And then diving into implementation:

The evil of this problem is in details. In order to get tweets for a user:

1. Have to loop not only this users tweets but also all the users followees' tweets;
2. Have to get top 10 based upon timestamp;

The second requirement is a perfect use case for Max heap or Min heap with a fixed size. It appears to be a Max heap.
However, C++ doesn't support fixed size and heap only supports retrieving and removing from the top of the heap. Therefore,
a Min heap has to be used here. Unfortunately, C++'s default priority_heap is a Max heap. So, one has to override the comparator.
One may think the standard function objcet std::greater can help, but it doesn't support a class like Tweet by default.
So the best solution is define your own function object or using lambda.

Define lambda function:

auto cmp = [](const Tweet &t1, const Tweet &t2) { return t1.getTimestamp() > t2.getTimestamp(); };

Then:

priority_queue<Tweet, vector<Tweet>, decltype(cmp)> q(cmp);

Fixed size is achieved by checking the size of the queue before inseration. If the size reaches the capacity and the tweet
on top of the heap is older than the one that is currently examined, pop the head from the queue and push the current one on
to the heap.

Let's go back to the first requirement: one may notice looping through user's tweets and looping through followees' tweets will
have the exactly same code for dealing with the queue. One may have to write the same code twice. Of course, one could collect all
tweets first then send to a method to handle queuing. But that requires extra space.

One smart solution is: when a new user is created, let the user follows hiself/herself. So, in terms of getting new tweets, one may
only loop the user's followees' list, which includes the user ID by default.

In terms of data structure, followees shall be stored in a hash set to achieve O(1) deletion.

Edge cases:

1. User doesn't exist;
2. Follower or followee doesn't exist;
3. User tries to follow hiself/herself (this is built in our code, adding it will introduce duplicates);
*/
class Twitter {
private:
	static const int CAPACITY = 10;
	class Tweet {
	private:
		int tweetId;
		int userId;
		long timestamp;
	public:
		Tweet(int uid, int tid, long ts) : userId(uid), tweetId(tid), timestamp(ts) {}
		int getTweetId() const { return this->tweetId; }
		int getUserId() const { return this->userId; }
		long getTimestamp() const { return this->timestamp; }
	};
	unordered_map<int, vector<Tweet> > userTweets;
	unordered_map<int, unordered_set<int> > userFollowees;
	long ticks;
	void createUser(int userId) {
		this->userTweets.emplace(userId, vector<Tweet>());
		this->userFollowees.emplace(userId, unordered_set<int>());
		this->userFollowees[userId].insert(userId);
	}
	bool isExistingUser(int userId) { return 1 == this->userTweets.count(userId); }
public:
	/** Initialize your data structure here. */
	Twitter() : ticks(0) {

	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		if (false == this->isExistingUser(userId)) this->createUser(userId);
		this->userTweets[userId].emplace_back(Tweet(userId, tweetId, ++this->ticks));
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		if (false == this->isExistingUser(userId)) this->createUser(userId);
		vector<int> tweets;
		auto cmp = [](const Tweet &t1, const Tweet &t2) { return t1.getTimestamp() > t2.getTimestamp(); };
		priority_queue<Tweet, vector<Tweet>, decltype(cmp)> q(cmp);
		for (int followeeId : this->userFollowees[userId]) {
			for (const Tweet& tweet : this->userTweets[followeeId]) {
				if (q.size() == CAPACITY) {
					if (q.top().getTimestamp() < tweet.getTimestamp()) q.pop(), q.push(tweet);
				}
				else
					q.push(tweet);
			}
		}
		while (false == q.empty()) tweets.emplace_back(q.top().getTweetId()), q.pop();
		std::reverse(tweets.begin(), tweets.end());
		return tweets;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followerId == followeeId) return;
		if (true == this->isExistingUser(followerId)) this->createUser(followerId);
		if (true == this->isExistingUser(followeeId)) this->createUser(followeeId);
		this->userFollowees[followerId].insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		if (followerId == followeeId) return;
		if (true == this->isExistingUser(followerId)) this->createUser(followerId);
		if (true == this->isExistingUser(followeeId)) this->createUser(followeeId);
		if (1 == this->userFollowees[followerId].count(followeeId)) this->userFollowees[followerId].erase(followeeId);
	}
};

/**
* Your Twitter object will be instantiated and called as such:
* Twitter obj = new Twitter();
* obj.postTweet(userId,tweetId);
* vector<int> param_2 = obj.getNewsFeed(userId);
* obj.follow(followerId,followeeId);
* obj.unfollow(followerId,followeeId);
*/
/*
Test cases:

["Twitter","postTweet","getNewsFeed","follow","postTweet","getNewsFeed","unfollow","getNewsFeed"]
[[],[1,5],[1],[1,2],[2,6],[1],[1,2],[1]]
["Twitter","postTweet","follow","getNewsFeed"]
[[],[1,5],[1,1],[1]]
["Twitter","postTweet","getNewsFeed","follow","getNewsFeed","unfollow","getNewsFeed"]
[[],[1,1],[1],[2,1],[2],[2,1],[2]]
["Twitter","getNewsFeed"]
[[],[1]]
["Twitter","postTweet","follow","follow","getNewsFeed"]
[[],[2,5],[1,2],[1,2],[1]]
["Twitter","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","postTweet","getNewsFeed"]
[[],[1,5],[1,3],[1,101],[1,13],[1,10],[1,2],[1,94],[1,505],[1,333],[1,22],[1,11],[1]]

Outputs:

[null,null,[5],null,null,[6,5],null,[5]]
[null,null,null,[5]]
[null,null,[1],null,[1],null,[]]
[null,[]]
[null,null,null,null,[5]]
[null,null,null,null,null,null,null,null,null,null,null,null,[11,22,333,505,94,2,10,13,101,3]]
*/