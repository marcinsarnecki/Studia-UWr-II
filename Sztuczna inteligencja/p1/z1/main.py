from queue import Queue
DEBUG = True

def chess_to_coord(chess_pos):
    file, rank = chess_pos[0], int(chess_pos[1])
    x = ord(file) - ord('a')
    y = rank - 1
    return x, y


def coord_to_chess(coord):
    x, y = coord
    file = chr(x + ord('a'))
    rank = y + 1
    return f"{file}{rank}"


def get_initial_state(line):
    return line[0], tuple(chess_to_coord(line[i]) for i in range(1, 4))


def king_next_possible_moves(pos):
    x, y = pos
    for xx, yy in ((x + 1, y + 1), (x + 1, y), (x + 1, y - 1),  # right
        (x, y - 1), (x, y + 1),  # up down
        (x - 1, y - 1), (x - 1, y), (x - 1, y + 1)):  # left
        if 0 <= xx <= 7 and 0 <= yy <= 7:
            yield xx, yy


def can_king_beat(pos, enemy_pos):
    return enemy_pos in king_next_possible_moves(pos)


def can_rook_beat(pos, enemy_pos):
    if pos == enemy_pos:
        return False
    return pos[0] == enemy_pos[0] or pos[1] == enemy_pos[1]


def black_king_next_coords(white_king, white_rook, pos):
    for new_pos in king_next_possible_moves(pos):
        if not can_king_beat(white_king, new_pos) and not can_rook_beat(white_rook, new_pos):
            if new_pos == white_rook:
                yield white_king, (-1, -1), new_pos  # describe_action('beat rook', black_king, new_pos)
            else:
                yield white_king, white_rook, new_pos  # describe_action('black king', black_king, new_pos)


def white_king_next_coords(pos, white_rook, black_king):
    for new_pos in king_next_possible_moves(pos):
        if not can_king_beat(black_king, new_pos) and new_pos != white_rook:
            yield new_pos, white_rook, black_king


def white_rook_next_coords(white_king, pos, black_king):
    x, y = pos
    if x == 1 and y == 1:  # no rook
        return
    if y == white_king[1] and x < white_king[0]:
        horizontal = range(white_king[0])
    elif y == white_king[1]:
        horizontal = range(white_king[0] + 1, 8)
    else:
        horizontal = range(8)
    if x == white_king[0] and y < white_king[1]:
        vertical = range(white_king[1])
    elif x == white_king[0]:
        vertical = range(white_king[1] + 1, 8)
    else:
        vertical = range(8)
    for new_x in horizontal:
        if new_x != x:
            yield white_king, (new_x, y), black_king
    for new_y in vertical:
        if new_y != y:
            yield white_king, (x, new_y), black_king


def checkmate(state):
    return not list(black_king_next_coords(*state[1]))


def next_states(state):
    player, coords = state
    if player == 'black':
        for new_coords in black_king_next_coords(*coords):
            yield 'white', new_coords
    if player == 'white':
        for new_coords in white_king_next_coords(*coords):
            yield 'black', new_coords
        for new_coords in white_rook_next_coords(*coords):
            yield 'black', new_coords


def get_move(s1, s2):
    if s1[1][0] != s2[1][0]:
        return f'white king {coord_to_chess(s1[1][0])} -> {coord_to_chess(s2[1][0])}'
    if s1[1][1] != s2[1][1]:
        return f'white rook {coord_to_chess(s1[1][1])} -> {coord_to_chess(s2[1][1])}'
    if s1[1][2] != s2[1][2]:
        return f'black king {coord_to_chess(s1[1][2])} -> {coord_to_chess(s2[1][2])}'


def solve(line):
    player, coords = get_initial_state(line)
    visited = set()
    dist = {}
    visited.add((player, coords))
    dist[(player, coords)] = 0
    queue = Queue()
    queue.put((player, coords))
    prev = {}
    while not queue.empty():
        current_state = queue.get()
        if current_state[0] == 'black' and checkmate(current_state):
            ans = str(dist[current_state])
            print(ans)
            if DEBUG:
                states = []
                while current_state != (player, coords):
                    states.append(current_state)
                    current_state = prev[current_state]
                states.append(current_state)
                states.reverse()
                for i in range(0, len(states) - 1):
                    print(get_move(states[i], states[i+1]))
            return ans
        for state in next_states(current_state):
            if state not in visited:
                prev[state] = current_state
                visited.add(state)
                dist[state] = dist[current_state] + 1
                queue.put(state)


with open('zad1_input.txt', 'r') as input_file, open('zad1_output.txt', 'w+') as output_file:
    for line in input_file:
        output_file.write(solve(line.split(" ")) + '\n')
