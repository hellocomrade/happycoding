#https://leetcode.com/problems/gas-station/?tab=Description
#
# Circle is actually not necessary to take care at all. See C++ solution.
# Here is a "naive" version with the same level of time complexity though.
# Even it's "naive", the same greedy rule applies: if we fail on station i, we total discard everything from 0 to i and 
# restart everything from i + 1.
class SolutionGasStation(object):
    def canCompleteCircuit(self, gas, cost):
        """
        :type gas: List[int]
        :type cost: List[int]
        :rtype: int
        """
        size, start, pos, gasInTank = len(gas), 0, 0, 0
        while pos < size:
            start, gasInTank = pos, 0
            while True:
                if start != pos and pos % size == start:
                    return start
                gasInTank = gasInTank + gas[pos % size] - cost[pos % size]
                pos = pos + 1
                if gasInTank < 0:
                    break;
        return -1
