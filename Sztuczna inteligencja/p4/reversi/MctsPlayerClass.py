import random
import sys
import time
from copy import deepcopy
from math import log, sqrt
import HeuristicPlayerClass

from board import Board


PLAYER_COLOR = -1
TIME_FOR_A_MOVE = 0.99
EXPLORING_CONSTANT = 1

DEBUG = False


class Node:
    def __init__(self, color, board, parent, action):
        self.board: Board = board
        self.color = color
        self.child = None  #
        self.T = 0  # won
        self.N = 0  # total count
        self.parent = parent
        self.action = action

    def getUCB(self):
        if self.N == 0:
            return float(1000000)
        top_node = self
        if top_node.parent:
            top_node = top_node.parent
        if top_node.color == PLAYER_COLOR:
            return (self.T / self.N) + EXPLORING_CONSTANT * sqrt(log(top_node.N) / self.N)
        else:
            return ((self.N - self.T) / self.N) + EXPLORING_CONSTANT * sqrt(log(top_node.N) / self.N)

    def create_child(self):
        if self.board.isDone():
            return
        actions = []
        child = {}
        for (y, x) in self.board.getAllPossibilitiesToMove(self.color):
            actions.append((y, x))
            new_board = deepcopy(self.board)
            new_board.addDisk(y, x, self.color)
            child[(y, x)] = Node(not self.color, new_board, self, (y, x))
        self.child = child

    def explore(self):
        current = self
        while current.child:
            child = current.child
            max_U = max(c.getUCB() for c in child.values())
            actions = [a for a, c in child.items() if c.getUCB() == max_U]
            if len(actions) == 0:
                print("error zero length ", max_U, file=sys.stderr)
            action = random.choice(actions)
            current = child[action]
        res = 0
        if current.N < 1:
            res = current.rollout()
            current.T += res
        else:
            current.create_child()
            if current.child:
                current = random.choice(list(current.child.values()))
            res = current.rollout()
            current.T = current.T + res
        current.N += 1
        parent = current

        while parent.parent:
            parent = parent.parent
            parent.N += 1
            parent.T = parent.T + res

    def rollout(self):  # return 1 if player wins
        board = deepcopy(self.board)
        me = HeuristicPlayerClass.Player(PLAYER_COLOR, board)
        enemy = HeuristicPlayerClass.Player(not PLAYER_COLOR, board)
        turn = self.color
        passed = 0
        while not board.isDone() and passed < 2:
            if turn == PLAYER_COLOR:
                y, x = me.move()
            else:
                y, x = enemy.move()
            if y == -1 and x == -1:
                passed += 1
            else:
                passed = 0
            turn = not turn
        return board.isWinner(PLAYER_COLOR)

    def next(self):
        if self.board.isDone():
            raise ValueError("game has ended")

        if not self.child:
            self.color = not self.color
            return self, (-1, -1)

        child = self.child

        max_N = max(node.N for node in child.values())

        max_children = [c for a, c in child.items() if c.N == max_N]

        if len(max_children) == 0:
            print("error zero length ", max_N, file=sys.stderr)

        max_child = random.choice(max_children)
        return max_child, max_child.action

    def detach_parent(self):
        self.parent = None


class Player:
    def __init__(self, color, board):
        global PLAYER_COLOR
        PLAYER_COLOR = color
        self.tree: Node = Node(False, board, None, (-1, -1))

    def move(self, time_for_move, remaining_time):
        startTime = time.time()
        while time.time() - startTime < TIME_FOR_A_MOVE:
            self.tree.explore()

        if DEBUG:
            self.printChildren()
        self.tree, (y, x) = self.tree.next()
        if DEBUG:
            print(f"chose {y} {x} {round(100 * self.tree.T / self.tree.N, 2)}% T={self.tree.T} N={self.tree.N}",
                  file=sys.stderr)
        self.tree.detach_parent()
        return y, x

    def printChildren(self):
        print('inside print children! ', file=sys.stderr, end=', ')
        print('current: ', self.tree.color == PLAYER_COLOR, file=sys.stderr, end=', ')
        print('children: \n', file=sys.stderr, end=": ")
        for a, c in self.tree.child.items():
            print(f"a={a} {round(100 * c.T / (c.N if c.N > 0 else c.N + 1), 2)}% T={c.T} N={c.N}", file=sys.stderr,
                  end='  |  ')
        print('out of print children ', file=sys.stderr)

    def moveByParticularAction(self, y, x):
        if y == -1 and x == -1:
            self.tree.color = not self.tree.color
            pass
        else:
            if not self.tree.child:
                self.tree.create_child()
            self.tree = self.tree.child[(y, x)]
            self.tree.detach_parent()
