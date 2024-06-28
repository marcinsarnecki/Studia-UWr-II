from random import shuffle

from board import Board


class RandomAgent:
    def __init__(self, player):
        self.player = player

    def move(self, brd, LIMIT=20000):
        allMoves = brd.allMoves(self.player)
        shuffle(allMoves)
        if allMoves == [] or brd.winner() is not None:
            return -1, -1, -1, -1
        n = len(allMoves)
        res = [0 for _ in range(n)]
        idx = 0

        while LIMIT > 0:
            moves, winner = allMoves[idx][1].simulateRandomGame()
            LIMIT -= moves
            res[idx] += 1 if winner == self.player else 0
            idx = (idx + 1) % n

        idx = res.index(max(res))
        move = allMoves[idx][0]
        return move



