# https://leetcode.com/problems/dungeon-game/
class SolutionDungeonGame:

    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        rcnt = len(dungeon)
        if 1 > rcnt: return 0
        ccnt = len(dungeon[0])
        if 1 > ccnt: return 0
        dungeon[-1][-1] = max(1, 1 - dungeon[-1][-1])
        for i in range(rcnt - 1, -1, -1):
            for j in range(ccnt - 1, -1, -1):
                if i + 1 < rcnt and j + 1 < ccnt:
                    dungeon[i][j] = max(1, min(dungeon[i + 1][j], dungeon[i][j + 1]) - dungeon[i][j])
                elif i + 1 < rcnt:
                    dungeon[i][j] = max(1, dungeon[i + 1][j] - dungeon[i][j])
                elif j + 1 < ccnt:
                    dungeon[i][j] = max(1, dungeon[i][j + 1] - dungeon[i][j])
        return dungeon[0][0]