from HeuristicAgent import HeuristicAgent
from board import Board

if __name__ == "__main__":
    time_for_move = 0
    remaining_time = 0
    board = Board()
    player = -1  # not initialized
    print('RDY')
    while True:
        message = input().split()
        command = message[0]
        if command == "UGO":
            if player == -1:
                player = HeuristicAgent(0)
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y0, x0, y1, x1 = player.move(board)
            if y0 != -1 and x0 != -1:
                board.moveAnimal(y0, x0, y1, x1)
            print(f'IDO {x0} {y1} {x1} {y1}')

        elif command == "HEDID":
            if player == -1:
                player = HeuristicAgent(1)
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y0 = int(message[4])
            x0 = int(message[3])
            y1 = int(message[6])
            x1 = int(message[5])
            if x0 == -1 and y0 == -1:
                pass
            else:
                board.moveAnimal(y0, x0, y1, x1)
            y0, x0, y1, x1 = player.move(board)
            if y0 != -1 and x0 != -1:
                board.moveAnimal(y0, x0, y1, x1)
            print(f'IDO {x0} {y0} {x1} {y1}')
            # player.board.printBoard()
            # print()
            # print()

        elif command == "ONEMORE":
            player = -1
            board = Board()
            print('RDY')

        elif command == "BYE":
            break

        else:
            print("Invalid command")
