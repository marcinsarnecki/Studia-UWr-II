import random
import sys
from random import randint
from time import time
from copy import deepcopy
from board import Board


class Player:
    __priority = [[300, -10, 11, 8, 8, 11, -10, 300],
                  [-10, -20, 1, 1, 1, 1, -20, -10],
                  [11, 1, 2, 3, 3, 2, 1, 11],
                  [8,  1, 3, 1, 1, 3, 1, 8],
                  [8,  1, 3, 1, 1, 3, 1, 8],
                  [11, 1, 2, 3, 3, 2, 1, 11],
                  [-10, -20, 1, 1, 1, 1, -20, -10],
                  [300, -10, 11, 8, 8, 11, -10, 300]]

    __ePriority = [[100, -50, 55, 40, 40, 55, -50, 100],
                   [-10, -20, -4, 1, 1, -4, -20, -10],
                   [11, -20, 2, 2, 2, 2, -4, 11],
                   [40, 1, 2, 0, 0, 2, 1, 40],
                   [40, 1, 2, 0, 0, 2, 1, 40],
                   [11, -4, 2, 2, 2, 2, -4, 11],
                   [-10, -20, -4, 1, 1, -4, -20, -10],
                   [100, -50, 55, 40, 40, 55, -50, 100]]

    def __init__(self, color, board):
        self.board: Board = board

        self.color = color
        self.boardPos = board.getPositions(self.color)

    def __calculateValue(self, board, fieldValue):
        ans = 0
        for y in range(8):
            for x in range(8):
                if board[y][x] == self.color:
                    ans += fieldValue[y][x]
                if board[y][x] == (not self.color):
                    ans -= fieldValue[y][x]
        return ans

    def __getStableFieldsAtBordersAsSet(self, pos, checkSet, yy, xx):
        ans = set()
        while pos in checkSet:
            ans.add(pos)
            pos = (pos[0] + yy, pos[1] + xx)
        return ans

    def __getNumberOfStableFieldsAtBorders(self, color):
        checkSet = self.board.whites if color else self.board.blacks
        return len(set().union(
            self.__getStableFieldsAtBordersAsSet((0, 0), checkSet, 0, 1),
            self.__getStableFieldsAtBordersAsSet((0, 0), checkSet, 1, 0),
            self.__getStableFieldsAtBordersAsSet((7, 7), checkSet, -1, 0),
            self.__getStableFieldsAtBordersAsSet((7, 7), checkSet, 0, -1),
            self.__getStableFieldsAtBordersAsSet((0, 7), checkSet, 1, 0),
            self.__getStableFieldsAtBordersAsSet((0, 7), checkSet, 0, -1),
            self.__getStableFieldsAtBordersAsSet((7, 0), checkSet, -1, 0),
            self.__getStableFieldsAtBordersAsSet((7, 0), checkSet, 0, 1)))

    def __heuristicFunction(self):
        value = 0
        if self.board.movesMade < 53:  # seems ok
            value += self.__calculateValue(self.board.board, self.__priority)  # basic value with weighted fields
        else:
            value += 0.5 * self.__calculateValue(self.board.board, self.__ePriority)  # basic value with weighted
            # fields in the late game
        if self.board.movesMade > 53:  # in late game difference in score matters more
            blackNum, whiteNum = self.board.calculate()
            if self.color:
                value += 3 * (whiteNum - blackNum)
            else:
                value += 3 * (blackNum - whiteNum)

        value += 30 * (self.__getNumberOfStableFieldsAtBorders(self.color) - self.__getNumberOfStableFieldsAtBorders(
            not self.color))
        return value

    def moveClassicRandom(self):
        allPossibilities = self.board.getAllPossibilitiesToMove(self.color)
        if len(allPossibilities) == 0:
            return -1, -1
        best = (-10000, 0, 0)

        temp = []
        temp2 = []
        original = self.board
        xxx = self.board.movesMade
        for (y, x) in allPossibilities:
            self.board = original.copy()
            self.board.addDisk(y, x, self.color)

            score = self.__heuristicFunction()
            temp.append(score)

            if score >= best[0]:
                best = (score, y, x)

        for idx, (y, x) in enumerate(allPossibilities):
            if temp[idx] == best[0]:
                temp2.append((y, x))
        (y, x) = temp2[random.choice(range(len(temp2)))]
        self.board = original
        self.board.addDisk(y, x, self.color)
        assert xxx + 1 == self.board.movesMade
        return y, x

    def move(self):
        # y, x = self.moveClassic()
        y, x = self.moveClassicRandom()
        return y, x
