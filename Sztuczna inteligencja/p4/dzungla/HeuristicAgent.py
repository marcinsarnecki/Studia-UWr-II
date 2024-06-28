from random import shuffle

from board import Board

INF = 1000000000
ANIMAL_CONSTANT = 25


def dist(y0, x0, y1, x1):
    return abs(y1 - y0) + abs(x1 - x0)


class HeuristicAgent:
    def __init__(self, player):
        self.defensiveAnimals = {"D", "W"}
        self.player = player
        self.toEnemyFlagValues = [[0] * 7 for _ in range(9)]
        self.enemyFlagY = 0
        self.enemyFlagX = 3
        self.myFlagY = 8
        self.myFlagX = 3
        if player == 1:
            self.enemyFlagY = 8
            self.myFlagY = 0
        for y in range(9):
            for x in range(7):
                self.toEnemyFlagValues[y][x] = 15 - dist(y, x, self.enemyFlagY, self.enemyFlagX)
        self.defenceValues = [[0] * 7 for _ in range(9)]
        nearTrapsY = 7
        nearTrapsX0 = 2
        nearTrapsX1 = 4
        if player == 1:
            nearTrapsY = 1
        for y in range(9):
            for x in range(7):
                self.defenceValues[y][x] = 15 - min(dist(y, x, nearTrapsY, nearTrapsX0),
                                                    dist(y, x, nearTrapsY, nearTrapsX1))

    def loadAnimals(self, board: Board):
        animals = {}
        enemies = {}
        for y in range(9):
            for x in range(7):
                if board.board[y][x] in ("#", "~", "*", "."):
                    continue
                if (board.board[y][x].islower() and self.player == 0) or (
                        board.board[y][x].isupper() and self.player == 1):
                    animals[board.board[y][x].upper()] = (y, x)
                else:
                    enemies[board.board[y][x].upper()] = (y, x)
        return animals, enemies

    def evalBoard(self, board):
        animals, enemies = self.loadAnimals(board)
        if len(enemies) == 0:
            return INF
        if board.winner() == self.player:
            return INF
        ans = 0
        for animal, (y, x) in animals.items():
            ans += (board.animal_powers[animal] ** 2) * ANIMAL_CONSTANT  # my animal squad
        for animal, (y, x) in enemies.items():
            ans -= (board.animal_powers[animal] ** 2) * ANIMAL_CONSTANT  # enemy animal squad
            if (y, x) in board.traps:
                ans = -INF
        for animal, (y, x) in animals.items():
            if animal in self.defensiveAnimals:  # distance
                ans += self.defenceValues[y][x]
            else:
                ans += self.toEnemyFlagValues[y][x]  # distance
                if dist(y, x, self.enemyFlagY, self.enemyFlagX) <= 1:
                    ans += 1000
            for dy, dx in board.dirs:
                yy = y + dy
                xx = x + dx
                if (yy, xx) in enemies.values():
                    if board.canKill(y, x, yy, xx):
                        ans += (board.animal_powers[board.board[yy][xx].upper()] ** 2) * ANIMAL_CONSTANT  # kill
                    if board.canKill(yy, xx, y, x):
                        ans -= (board.animal_powers[board.board[y][x].upper()] ** 2) * ANIMAL_CONSTANT  # death
        return ans

    def move(self, board):
        allMoves = board.allMoves(self.player)
        if allMoves == [] or board.winner() is not None:
            return -1, -1, -1, -1
        n = len(allMoves)
        res = [0 for _ in range(n)]
        for i in range(n):
            res[i] = self.evalBoard(allMoves[i][1])
        idx = res.index(max(res))
        move = allMoves[idx][0]
        return move
