import chess
import chess.polyglot
import chess.syzygy
import math

opening_book = chess.polyglot.open_reader("data/polyglot/Titans.bin")
# https://chess.stackexchange.com/questions/35448/looking-for-polyglot-opening-books
tablebase = chess.syzygy.open_tablebase("data/syzygy")  # syzygy ending table


def flip_evaluation_table(table):
    flipped_table = table[::-1]
    return flipped_table


class SmartAgent:
    def __init__(self, board, color):
        self.color = color
        self.board = board
        self.pieces_values = {
            chess.PAWN: 100,
            chess.KNIGHT: 320,
            chess.BISHOP: 340,
            chess.ROOK: 500,
            chess.QUEEN: 900,
            chess.KING: 20000
        }
        # https://www.chessprogramming.org/Simplified_Evaluation_Function
        self.pawns_table = [
            0, 0, 0, 0, 0, 0, 0, 0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
            5, 5, 10, 25, 25, 10, 5, 5,
            0, 0, 0, 20, 20, 0, 0, 0,
            5, -5, -10, 0, 0, -10, -5, 5,
            5, 10, 10, -20, -20, 10, 10, 5,
            0, 0, 0, 0, 0, 0, 0, 0
        ]
        self.knights_table = [
            -20, -10, -10, -10, -10, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 10, 10, 5, 0, -10,
            -10, 5, 5, 10, 10, 5, 5, -10,
            -10, 0, 10, 10, 10, 10, 0, -10,
            -10, 10, 10, 10, 10, 10, 10, -10,
            -10, 5, 0, 0, 0, 0, 5, -10,
            -20, -10, -10, -10, -10, -10, -10, -20
        ]

        self.bishops_table = [
            -20, -10, -10, -10, -10, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 10, 10, 5, 0, -10,
            -10, 5, 5, 10, 10, 5, 5, -10,
            -10, 0, 10, 10, 10, 10, 0, -10,
            -10, 10, 10, 10, 10, 10, 10, -10,
            -10, 5, 0, 0, 0, 0, 5, -10,
            -20, -10, -10, -10, -10, -10, -10, -20
        ]
        self.rooks_table = [
            0, 0, 0, 0, 0, 0, 0, 0,
            5, 10, 10, 10, 10, 10, 10, 5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            0, 0, 0, 5, 5, 0, 0, 0
        ]
        self.queens_table = [
            -20, -10, -10, -5, -5, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 5, 5, 5, 0, -10,
            -5, 0, 5, 5, 5, 5, 0, -5,
            0, 0, 5, 5, 5, 5, 0, -5,
            -10, 5, 5, 5, 5, 5, 0, -10,
            -10, 0, 5, 0, 0, 0, 0, -10,
            -20, -10, -10, -5, -5, -10, -10, -20
        ]
        self.kings_table = [
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -30, -40, -40, -50, -50, -40, -40, -30,
            -20, -30, -30, -40, -40, -30, -30, -20,
            -10, -20, -20, -20, -20, -20, -20, -10,
            20, 20, 0, 0, 0, 0, 20, 20,
            20, 30, 10, 0, 0, 10, 30, 20
        ]
        self.flip_tables_if_black()

    def flip_tables_if_black(self):
        if not self.color:
            self.pawns_table = self.pawns_table[::-1]
            self.knights_table = self.knights_table[::-1]
            self.bishops_table = self.bishops_table[::-1]
            self.rooks_table = self.rooks_table[::-1]
            self.queens_table = self.queens_table[::-1]
            self.kings_table = self.kings_table[::-1]

    def move(self):
        # try to make a move from opening book
        book_move = opening_book.get(self.board)
        if book_move:
            return str(book_move.move)
        return str(self.alpha_beta(2))

    def alpha_beta(self, depth):
        def minimax(depth, maximazing_player, alpha, beta):
            if depth == 0 or (self.board.outcome() is not None):
                return self.score_position()

            moves = self.board.legal_moves
            if maximazing_player:
                max_eval = -math.inf
                for move in moves:
                    self.board.push(move)
                    evalt = minimax(depth - 1, False, alpha, beta)
                    self.board.pop()
                    max_eval = max(max_eval, evalt)
                    alpha = max(alpha, evalt)
                    if beta <= alpha:
                        break
                return max_eval
            else:
                min_eval = math.inf
                for move in moves:
                    self.board.push(move)
                    evalt = minimax(depth - 1, True, alpha, beta)
                    self.board.pop()
                    min_eval = min(min_eval, evalt)
                    beta = min(beta, evalt)
                    if beta <= alpha:
                        break
                return min_eval

        ms = self.board.legal_moves
        if ms:
            if self.board.turn == self.color:
                ms_heuristic = {}
                for m in ms:
                    self.board.push(m)
                    ms_heuristic[m] = minimax(depth-1, False, -math.inf, math.inf)
                    self.board.pop()

                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=True)]
                return ms[0]
            else:
                ms_heuristic = {}
                for m in ms:
                    self.board.push(m)
                    ms_heuristic[m] = minimax(depth-1, True, -math.inf, math.inf)
                    self.board.pop()
                ms = [m for m, h in sorted(ms_heuristic.items(), key=lambda x: x[1], reverse=False)]
                return ms[0]

        return None

    def score_position(self):
        result = 0

        if self.board.outcome() is not None:
            winner = self.board.outcome().winner
            if winner is None:
                result = -10000
            elif winner == self.color:
                result = 1000000
            else:
                result = -1000000
        else:
            wdl = tablebase.get_wdl(self.board)

            if wdl:
                if wdl == 0:
                    return -10000
                if self.board.turn == self.color:  # our turn
                    return 1000000 if wdl > 0 else -1000000
                else:  # enemy's turn
                    return -1000000 if wdl > 0 else 1000000

            for piece, score in self.pieces_values.items():  # +/- how many pieces we/enemy have
                result += len(self.board.pieces(piece, self.color)) * score
                result -= len(self.board.pieces(piece, not self.color)) * score

            result += sum([self.pawns_table[i] for i in self.board.pieces(chess.PAWN, self.color)]) - sum(
                [self.pawns_table[chess.square_mirror(i)] for i in self.board.pieces(chess.PAWN, not self.color)])
            result += sum([self.knights_table[i] for i in self.board.pieces(chess.KNIGHT, self.color)]) - sum(
                [self.knights_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KNIGHT, not self.color)])
            result += sum([self.bishops_table[i] for i in self.board.pieces(chess.BISHOP, self.color)]) - sum(
                [self.bishops_table[chess.square_mirror(i)] for i in self.board.pieces(chess.BISHOP, not self.color)])
            result += sum([self.rooks_table[i] for i in self.board.pieces(chess.ROOK, self.color)]) - sum(
                [self.rooks_table[chess.square_mirror(i)] for i in self.board.pieces(chess.ROOK, not self.color)])
            result += sum([self.queens_table[i] for i in self.board.pieces(chess.QUEEN, self.color)]) - sum(
                [self.queens_table[chess.square_mirror(i)] for i in self.board.pieces(chess.QUEEN, not self.color)])
            result += sum([self.kings_table[i] for i in self.board.pieces(chess.KING, self.color)]) - sum(
                [self.kings_table[chess.square_mirror(i)] for i in self.board.pieces(chess.KING, not self.color)])

            # mobility
            saved_turn = self.board.turn
            mobility = 0
            self.board.turn = self.color
            mobility += len(list(self.board.legal_moves))
            self.board.turn = not self.color
            mobility -= len(list(self.board.legal_moves))
            # print(result, mobility*3)
            result += mobility * 3
            self.board.turn = saved_turn

        return result
