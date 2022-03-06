#include <mutex>
#include <algorithm>
#include <condition_variable>

using namespace std;

//https://leetcode.com/problems/building-h2o/
/*
1117. Building H2O

There are two kinds of threads: oxygen and hydrogen. Your goal is to group these threads to form water molecules.

There is a barrier where each thread has to wait until a complete molecule can be formed. Hydrogen and oxygen threads will be given releaseHydrogen and releaseOxygen methods respectively, which will allow them to pass the barrier. These threads should pass the barrier in groups of three, and they must immediately bond with each other to form a water molecule. You must guarantee that all the threads from one molecule bond before any other threads from the next molecule do.

In other words:

If an oxygen thread arrives at the barrier when no hydrogen threads are present, it must wait for two hydrogen threads.
If a hydrogen thread arrives at the barrier when no other threads are present, it must wait for an oxygen thread and another hydrogen thread.
We do not have to worry about matching the threads up explicitly; the threads do not necessarily know which other threads they are paired up with. The key is that threads pass the barriers in complete sets; thus, if we examine the sequence of threads that bind and divide them into groups of three, each group should contain one oxygen and two hydrogen threads.

Write synchronization code for oxygen and hydrogen molecules that enforces these constraints.

Example 1:

Input: water = "HOH"

Output: "HHO"

Explanation: "HOH" and "OHH" are also valid answers.

Example 2:

Input: water = "OOHHHH"

Output: "HHOHHO"

Explanation: "HOHHHO", "OHHHHO", "HHOHOH", "HOHHOH", "OHHHOH", "HHOOHH", "HOHOHH" and "OHHOHH" are also valid answers.

Constraints:

- 3 * n == water.length
- 1 <= n <= 20
- water[i] is either 'H' or 'O'.
- There will be exactly 2 * n 'H' in water.
- There will be exactly n 'O' in water.

Observations:

My version H2O_1 is very complicated and one may say: stupid... It has a barrier with its mutex, cv, a flag and a counter array for H and O. It also has another
pair of mutex, cv, counter for dispensing H and O, function like semaphores.

The idea is the same though: before a H2O can be formed, any incoming thread shall be blocked and H and O shall be dispensed at a 2 to 1 ratio. both scenarios that form a H2O:
either H is the 3rd elements to come or the O is the 3rd element to arrive. It appears they shall be handled differently at the detail level.

However, the implementation in H2O, is much simpler. Of course, it belongs to someone else... It's so delicate that only costs a mutex, a cv and 2 counters! It merges the
barrier and dispensing stuff in H2O_1 into a single set. Variable h and o here, combined with two if-conditions after release functions controls the thread access. "h" and "o"
will only be reset if they are in a 2 to 1 ratio exact and "h" is never more than 2, "o" is never more than 1. This implementation does an eager release: it doesn't wait till 2 H and 1 O are available. Instead,
it release at most 2 Hs or 1 O and waits for the remaining to come.

In Java, with the help of the Semaphore and Barrier, the implementation of H2O shall be more straightforward. Actually, based upon the performance chart on leetcode,
using synchronized block in Java could be faster!

import java.util.concurrent.Semaphore;
import java.util.concurrent.CyclicBarrier;
class H2O {
	private final Semaphore hSem = new Semaphore(2);
	private final Semaphore oSem = new Semaphore(1);
	private final CyclicBarrier barrier = new CyclicBarrier(3);
	public H2O() {

	}

	public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
		hSem.acquire();
		// releaseHydrogen.run() outputs "H". Do not change or remove this line.
		releaseHydrogen.run();
		try {
			barrier.await();
		}
		catch(BrokenBarrierException ex) {

		}
		finally {
			hSem.release();
		}
	}

	public void oxygen(Runnable releaseOxygen) throws InterruptedException {
		oSem.acquire();
		// releaseOxygen.run() outputs "O". Do not change or remove this line.
		releaseOxygen.run();
		try {
			barrier.await();
		}
		catch(BrokenBarrierException ex) {

		}
		finally {
			oSem.release();
		}
	}
}
*/
class H2O {
private:
	short h;
	short o;
	mutex mtx;
	condition_variable cv;
public:
	H2O() : h(0), o(0) {

	}

	void hydrogen(function<void()> releaseHydrogen) {
		unique_lock<mutex> lck(mtx);
		cv.wait(lck, [this]() -> bool { return this->h < 2; });
		// releaseHydrogen() outputs "H". Do not change or remove this line.
		releaseHydrogen();
		if (++h == 2 && o == 1)
			h = o = 0;
		cv.notify_all();
	}

	void oxygen(function<void()> releaseOxygen) {
		unique_lock<mutex> lck(mtx);
		cv.wait(lck, [this]() -> bool { return this->o < 1; });
		// releaseOxygen() outputs "O". Do not change or remove this line.
		releaseOxygen();
		++o;
		if (h == 2)
			h = o = 0;
		cv.notify_all();
	}
};

class H2O_1 {
private:
	bool inProgress;
	short dispensing[2];
	short elemStock[2];
	mutex barrierMutex;
	condition_variable barrierCond;
	mutex dispensingMutex[2];
	condition_variable dispensingCond[2];

	void increaseStock(int i) {
		unique_lock<mutex> lck(barrierMutex);
		barrierCond.wait(lck, [this]() -> bool { return !inProgress; });
		++elemStock[i];
		notify(i);
	}

	void decreaseStock(int i) {
		unique_lock<mutex> lck(barrierMutex);
		--elemStock[i];
		--dispensing[i];
		if (dispensing[0] == 0 && dispensing[1] == 0) {
			inProgress = false;
			barrierCond.notify_all();
		}
	}

	void notify(int i) {
		if (elemStock[0] > 1 && elemStock[1] > 0) {
			unique_lock<mutex> lck0(dispensingMutex[0]);
			unique_lock<mutex> lck1(dispensingMutex[1]);
			dispensing[0] = 2;
			dispensing[1] = 1;
			inProgress = true;
			dispensingCond[0].notify_one();
			if (i == 0) {
				dispensingCond[1].notify_one();
				if (elemStock[0] > 1) {
					dispensingCond[0].notify_one();
				}
			}
			else {
				dispensingCond[0].notify_one();
				if (elemStock[1] > 1) {
					dispensingCond[1].notify_one();
				}
			}
		}
	}
public:
	H2O_1() : inProgress(false), dispensing{ 0 }, elemStock{ 0 } {

	}

	void hydrogen(function<void()> releaseHydrogen) {
		increaseStock(0);
		unique_lock<mutex> lck0(dispensingMutex[0]);
		dispensingCond[0].wait(lck0, [this]() -> bool { return this->dispensing[0] > 0; });
		// releaseHydrogen() outputs "H". Do not change or remove this line.
		releaseHydrogen();
		decreaseStock(0);
	}

	void oxygen(function<void()> releaseOxygen) {
		increaseStock(1);
		unique_lock<mutex> lck0(dispensingMutex[1]);
		dispensingCond[1].wait(lck0, [this]() -> bool { return this->dispensing[1] > 0; });
		// releaseOxygen() outputs "O". Do not change or remove this line.
		releaseOxygen();
		decreaseStock(1);
	}
};
/*
Test cases:

"HOH"
"OHH"
"OOHHHH"
"HHOOHH"
"HOHOHH"
"HHHHHHOOO"
"OHHHOHHHO"
"HHOOHHHHOOOHHHH"

Outputs:

"HHO"
"OHH"
"OHHHHO"
"HHOHOH"
"HHOOHH"
"HHOOHHOHH"
"OHHOHHHHO"
"HHOOHHHOHHOHHHO"
*/