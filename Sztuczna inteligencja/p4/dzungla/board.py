import os
import sys
from copy import deepcopy
from random import shuffle


def u(s):
    return s.upper()


def inBounds(y, x):
    return 9 > y > -1 and 7 > x > -1


terrain = [
    "..#*#..",
    "...#...",
    ".......",
    ".~~.~~.",
    ".~~.~~.",
    ".~~.~~.",
    ".......",
    "...#...",
    "..#*#.."]


class Board:
    dirs = [(0, 1), (1, 0), (-1, 0), (0, -1)]
    traps = {(0, 2), (0, 4), (1, 3), (8, 2), (8, 4), (7, 3)}

    def __init__(self):
        self.turn = 0
        self.board = [
            ["L", ".", "#", "*", "#", ".", "T"],
            [".", "D", ".", "#", ".", "C", "."],
            ["R", ".", "J", ".", "W", ".", "E"],
            [".", "~", "~", ".", "~", "~", "."],
            [".", "~", "~", ".", "~", "~", "."],
            [".", "~", "~", ".", "~", "~", "."],
            ["e", ".", "w", ".", "j", ".", "r"],
            [".", "c", ".", "#", ".", "d", "."],
            ["t", ".", "#", "*", "#", ".", "l"]]
        self.animal_powers = {
            "E": 7,
            "L": 6,
            "T": 5,
            "J": 4,
            "W": 3,
            "D": 2,
            "C": 1,
            "R": 0,
            ".": -1,
            "~": -1,
            "#": -1
        }

    def print_board(self):
        for row in self.board:
            print("".join(row))
        print()

    def print_move(self, y0, x0, y1, x1):
        print(x0, y0, x1, y1)

    def winner(self):
        if self.board[0][3] != "*":
            return 0
        elif self.board[8][3] != "*":
            return 1
        return None

    def moveAnimal(self, y0, x0, y1, x1):
        # print('ide ', y0, x0, ' -> ', y1, x1)
        self.turn = 1 if self.board[y0][x0].islower() else 0
        self.board[y1][x1] = self.board[y0][x0]
        self.board[y0][x0] = terrain[y0][x0]

    def canKill(self, y0, x0, y1, x1):
        if self.board[y1][x1] == "." or self.board[y1][x1] == "*" or self.board[y1][x1] == "#":
            return True
        if terrain[y0][x0] == "~" and terrain[y1][x1] != "~":  # cant kill coming out from water
            return False
        p1 = self.animal_powers[self.board[y0][x0].upper()]
        p2 = self.animal_powers[self.board[y1][x1].upper()]
        if p1 == 0 and p2 == 7:  # rat kills elephant
            return True
        if p1 == 7 and p2 == 0:  # but not vice versa
            return False
        if (y1, x1) in self.traps:  # in traps everyone dies
            return True
        if p1 >= p2:  # stronger or equal
            return True
        return False

    def copy(self):
        ret = Board()
        ret.board = deepcopy(self.board)
        return ret

    def canMove(self, y0, x0, y1, x1):
        if not inBounds(y1, x1):  # out of board
            return False
        if self.board[y0][x0].islower() and self.board[y1][x1].islower():  # own animal
            return False
        if self.board[y0][x0].isupper() and self.board[y1][x1].isupper():  # own animal
            return False

        animal = self.board[y0][x0]
        player = 0 if animal.islower() else 1
        animal = animal.upper()

        if player == 0 and y1 == 8 and x1 == 3:  # own den
            return False
        if player == 1 and y1 == 0 and x1 == 3:  # own den
            return False

        if self.board[y1][x1] == "~" and animal != "R":  # not-rat trying to get into water
            return False

        if animal == "T" or animal == "L":  # jump
            enemy_rat = "R" if player == 0 else "r"
            dy = y1 - y0
            dx = x1 - x0
            while self.board[y1][x1] == "~":
                y1 += dy
                x1 += dx
                if self.board[y1][x1] == enemy_rat:
                    return False

        if not self.canKill(y0, x0, y1, x1):
            return False
        # self.moveAnimal(y0, x0, y1, x1)
        return y1, x1

    def allMoves(self, player):
        ans = []
        for y in range(9):
            for x in range(7):
                if self.board[y][x] in ("#", "~", "*", "."):
                    continue
                if (self.board[y][x].islower() and player == 0) or (self.board[y][x].isupper() and player == 1):
                    for (dy, dx) in self.dirs:
                        yy = y + dy
                        xx = x + dx
                        move = self.canMove(y, x, yy, xx)
                        if move:
                            newBoard = self.copy()
                            newBoard.moveAnimal(y, x, move[0], move[1])
                            ans.append(((y, x, move[0], move[1]), newBoard))
        return ans

    def randomMove(self):
        player = self.turn
        animals = []
        enemies_left = 0
        for y in range(9):
            for x in range(7):
                if self.board[y][x] in ("#", "~", "*", "."):
                    continue
                if (self.board[y][x].islower() and player == 0) or (self.board[y][x].isupper() and player == 1):
                    animals.append((y, x))
                else:
                    enemies_left += 1
        if not animals:
            return 11 - player
        shuffle(animals)

        while animals:
            y, x = animals.pop()
            dirs = deepcopy(self.dirs)
            shuffle(dirs)
            while dirs:
                dy, dx = dirs.pop()
                yy = y + dy
                xx = x + dx
                if self.canMove(y, x, yy, xx):
                    self.moveAnimal(y, x, yy, xx)
                    return True
        # self.turn = 1 - self.turn  # winner has turn if randomMove returns false
        return False

    def simulateRandomGame(self):
        moves = 0
        temp_board = self.copy()
        while temp_board.winner() is None:
            res = temp_board.randomMove()
            # os.system('clear')
            # temp_board.print_board()
            moves += 1
            if res >= 10:
                return moves, res - 10
            if not res:
                break
        return moves, temp_board.winner()


if __name__ == "__main__":
    w1 = 0
    for i in range(1000):
        board = Board()
        moves, winner = board.simulateRandomGame()
        # print('moves =', moves, 'winner =', winner)
        if winner == 1:
            w1 += 1
        print(i)
    print('w1 = ', w1, 'w0 = ', 1000 - w1)
