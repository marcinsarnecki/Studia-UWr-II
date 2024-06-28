import sys
import time
from HeuristicAgent import HeuristicAgent
from RandomAgent import RandomAgent
from board import Board

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print('number of games not passed!')
        exit(1)
    n = int(sys.argv[1])
    wins = [0, 0]
    total_time = [0, 0]  # Track the total time taken by each bot
    for i in range(n):
        p = (RandomAgent(0), HeuristicAgent(1))
        board = Board()
        while True:
            # board.print_board()
            turn = board.turn

            start_time = time.time()

            move = p[turn].move(board)

            end_time = time.time()
            move_time = end_time - start_time
            total_time[turn] += move_time

            if move == (-1, -1, -1, -1):
                wins[1 - turn] += 1
                break
            board.moveAnimal(*move)
            if board.winner() is not None:
                wins[board.winner()] += 1
                break
        board.print_board()
    print("Total time taken by RandomAgent:", total_time[0])
    print("Total time taken by HeuristicAgent:", total_time[1])
    print("wins = ", wins)




