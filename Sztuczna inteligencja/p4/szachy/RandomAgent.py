import random


class RandomAgent:
    def __init__(self, board, color):
        self.board = board
        self.color = color

    def move(self):
        return self.make_move_random()

    def make_move_random(self):
        legal_moves = list(self.board.legal_moves)
        return str(random.choice(legal_moves))
