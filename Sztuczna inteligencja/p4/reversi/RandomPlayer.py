from RandomPlayerClass import RandomPlayer
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
                player = RandomPlayer(False, board)
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y, x = player.move()
            print(f'IDO {x} {y}')

        elif command == "HEDID":
            if player == -1:
                player = RandomPlayer(True, board)
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y = int(message[4])
            x = int(message[3])
            if x == -1 and y == -1:
                # player.board.whiteTurn = not player.board.whiteTurn
                pass
            else:
                player.board.addDisk(y, x, not player.color)
            y, x = player.move()
            print(f'IDO {x} {y}')

        elif command == "ONEMORE":
            player = -1
            board = Board()
            print('RDY')

        elif command == "BYE":
            break

        else:
            print("Invalid command")
