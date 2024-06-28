import random
import sys
from random import randint
from board import Board


class RandomPlayer:
    def __init__(self, color, board):
        self.board: Board = board
        self.color = color

    def move(self):
        allPossibilities = self.board.getAllPossibilitiesToMove(self.color)
        # print('move random all=', allPossibilities, file=sys.stderr)
        # print('positions=', self.board.getPositions(self.color), file=sys.stderr)
        if len(allPossibilities) == 0:
            return -1, -1
        (y, x) = random.choice(allPossibilities)
        self.board.addDisk(y, x, self.color)
        return y, x
