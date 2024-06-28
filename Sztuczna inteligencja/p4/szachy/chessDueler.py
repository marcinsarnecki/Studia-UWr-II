import chess

from RandomAgent import RandomAgent
from SmartAgent import SmartAgent


class Chess:
    def __init__(self):
        self.board = chess.Board()

    def update(self, uci_move):
        move = chess.Move.from_uci(uci_move)
        self.board.push(move)

    def result(self):
        """ check after 100 moves or at the end -> task specific"""
        if self.board.outcome() is None:
            return None

        return self.board.outcome().winner

    def draw(self):
        print(f"move: {self.board.fullmove_number}")
        print(self.board)
        print("===============")


def play_game(AgentA, AgentB, draw=False, drawFinalState=False):
    game_board = Chess()
    white = AgentA(game_board.board, chess.WHITE)
    black = AgentB(game_board.board, chess.BLACK)

    while True:
        white_m = white.move()
        game_board.update(white_m)
        if draw:
            game_board.draw()
        if game_board.result() is not None:
            break
        black_m = black.move()
        game_board.update(black_m)
        if draw:
            game_board.draw()
        if game_board.result() is not None:
            break
    if drawFinalState:
        print()
        print(game_board.board)
    return game_board.result()


white_wins = 0
n = 10
for _ in range(n):
    winner = play_game(RandomAgent, SmartAgent, False, True)
    if winner:
        white_wins += 1
        print('white wins')
    else:
        print('black wins')
print(f'white won {white_wins}/{n} times')
