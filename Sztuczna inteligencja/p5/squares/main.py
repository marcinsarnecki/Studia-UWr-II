class Square:
    def __init__(self, size):
        self.size = size
        self.position = None
        self.letter = chr(ord('A') + size - 1)  # Przypisanie litery kwadratowi

    def __str__(self):
        return f"{self.letter}"


def can_place(square, board, x, y):
    # Sprawdź czy kwadrat mieści się w planszy
    if x + square.size > len(board) or y + square.size > len(board):
        return False

    # Sprawdź czy kwadrat nie nachodzi na inne kwadraty
    for i in range(x, x + square.size):
        for j in range(y, y + square.size):
            if board[i][j] is not None:
                return False

    return True


def place(square, board, x, y):
    for i in range(x, x + square.size):
        for j in range(y, y + square.size):
            board[i][j] = square
    square.position = (x, y)

def find_solution(squares):
    board_size = 70
    board = [[None] * board_size for _ in range(board_size)]
    sorted_squares = sorted(squares, key=lambda sq: sq.size, reverse=True)
    filled_fields = 0
    unfilled_fields = 0

    # Sprawdź każdy kwadrat i umieść go na planszy
    for square in sorted_squares:
        placed = False
        for x in range(board_size):
            for y in range(board_size):
                if can_place(square, board, x, y):
                    place(square, board, x, y)
                    filled_fields += square.size ** 2
                    placed = True
                    break
            if placed:
                break

        # Jeśli kwadrat nie został umieszczony, zwiększ liczbę niewypełnionych pól
        if not placed:
            unfilled_fields += square.size ** 2

    # Spróbuj wykorzystać niewykorzystane kwadraty do wypełnienia pustych pól
    for square in sorted_squares:
        if square.position is None:
            for x in range(board_size):
                for y in range(board_size):
                    if can_place(square, board, x, y):
                        place(square, board, x, y)
                        filled_fields += square.size ** 2
                        break

    return board, filled_fields, unfilled_fields


squares = [Square(i) for i in range(1, 25)]
solution, filled, unfilled = find_solution(squares)

if solution is not None:
    for row in solution:
        print("".join([str(sq) if sq is not None else "." for sq in row]))
    print('Liczba zdobytych pól:', filled)
    print('Liczba pól, których nie udało się wypełnić:', unfilled)
else:
    print("Brak rozwiązania.")
