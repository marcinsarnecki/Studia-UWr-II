import collections
from queue import Queue

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]


class Solution:
    def __init__(self):
        self.player = (0,0)
        self.targets = set()
        self.initial_boxes = list()
        self.walls = set()
        self.path = list()
        self.prev = {}

    def input(self):
        with open('zad_input.txt') as inp:
            for i, row in enumerate(inp):
                for j, char in enumerate(row):
                    if char in 'W':
                        self.walls.add((i, j))
                    if char in ('K', '+'):
                        self.player = (i, j)
                    if char in ('G', '*', '+'):
                        self.targets.add((i, j))
                    if char in ('B', '*'):
                        self.initial_boxes.append((i, j))
            self.initial_boxes = tuple(sorted(self.initial_boxes))

    def gen_new_states(self, state):
        player, boxes_list = state
        y, x = player
        boxes_set = set(boxes_list)
        for dir in range(0, 4):
            new_player = (y + dy[dir], x + dx[dir])
            if new_player in self.walls:
                continue
            if new_player in boxes_set:
                new_box_pos = (y + 2 * dy[dir], x + 2 * dx[dir])
                if new_box_pos in self.walls | boxes_set:  # nie mozna popchnac w sciane / innego boxa
                    continue
                new_boxes = boxes_set - {new_player} | {new_box_pos}
            else:
                new_boxes = boxes_set
            yield (new_player, tuple(sorted(new_boxes))), dir

    def is_dead(self, v):
        player, boxes = v
        for box in boxes:
            y, x = box
            if ((y - 1, x) in self.walls or (y + 1, x) in self.walls) and \
                    ((y, x - 1) in self.walls or (y, x + 1) in self.walls) and \
                    (y, x) not in self.targets:
                return True
        return False

    def generate_answer(self, prev, v):
        ans = []
        int_to_str = {0: "U", 1: "R", 2: "D", 3: "L"}
        while v in prev:
            v, dir = prev[v]
            ans.append(dir)
        ans.reverse()
        return ans

    def bfs(self):
        Q = Queue()
        v = (self.player, self.initial_boxes)
        Q.put(v)
        visited = {v}
        prev = {}

        while not Q.empty():
            v = Q.get()
            if self.win(v):
                return self.generate_answer(prev, v)
            for u, dir in self.gen_new_states(v):
                if u in visited:
                    continue
                if self.is_dead(u):  # zly stan oznaczamy jako visited zeby wiele razy go nie sprawdzac
                    visited.add(u)
                    continue
                prev[u] = (v, dir)
                visited.add(u)
                Q.put(u)

    def solve(self):
        dir_sequence = self.bfs()
        int_to_str = {0: "U", 1: "R", 2: "D", 3: "L"}
        ans = ''.join([int_to_str[i] for i in dir_sequence])
        print(ans, len(ans))
        with open('zad_output.txt', 'w') as out:
            out.write(ans)

    def win(self, state):
        player, boxes = state
        return set(boxes) == self.targets


solution = Solution()
solution.input()
solution.solve()
