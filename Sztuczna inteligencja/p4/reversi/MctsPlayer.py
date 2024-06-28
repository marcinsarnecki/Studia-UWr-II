from MctsPlayerClass import Player
from board import Board


DEBUG = False

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
                player = Player(False, board)
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y, x = player.move(time_for_move, remaining_time)
            print(f'IDO {x} {y}')

        elif command == "HEDID":
            if player == -1:
                player = Player(True, board)
                player.tree.create_child()
            time_for_move = float(message[1])
            remaining_time = float(message[2])
            y = int(message[4])
            x = int(message[3])
            player.moveByParticularAction(y, x)
            y, x = player.move(time_for_move, remaining_time)
            print(f'IDO {x} {y}')
            if DEBUG:
                player.tree.board.printBoard()

        elif command == "ONEMORE":
            player = -1
            board = Board()
            print('RDY')

        elif command == "BYE":
            break

        else:
            print("Invalid command")
