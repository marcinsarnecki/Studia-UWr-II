import random
from queue import Queue

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

MAX_UNCERTAINTY = 2


class Solution:
    def __init__(self):
        self.targets = set()
        self.initial_positions = list()
        self.walls = set()

    def input(self):
        with open('zad_input.txt') as inp:
            for i, row in enumerate(inp):
                for j, char in enumerate(row):
                    if char in '#':
                        self.walls.add((i, j))
                    if char in ('G', 'B'):
                        self.targets.add((i, j))
                    if char in ('S', 'B'):
                        self.initial_positions.append((i, j))
            self.initial_positions = tuple(sorted(self.initial_positions))

    def move(self, state, dir):
        new_state = set()
        for (y, x) in state:
            if (y + dy[dir], x + dx[dir]) not in self.walls:
                new_state.add((y + dy[dir], x + dx[dir]))
            else:
                new_state.add((y, x))
        return tuple(sorted(new_state))

    def reduce_uncertainty(self):
        state = self.initial_positions
        sequence = []
        last_dir = 0
        dir = 0
        while len(state) > MAX_UNCERTAINTY:
            dir = random.randint(0, 3)
            while dir + 2 % 4 == last_dir:
                dir = random.randint(0, 3)
            state = self.move(state, dir)
            sequence.append(dir)
            last_dir = dir
        return tuple(sorted(state)), sequence

    def gen_new_states(self, state):
        return ((tuple(sorted(self.move(state, dir))), dir) for dir in range(0, 4))

    def win(self, state):
        return all(pos in self.targets for pos in state)

    def generate_answer(self, prev, v):
        ans = []
        int_to_str = {0: "U", 1: "R", 2: "D", 3: "L"}
        while v in prev:
            v, dir = prev[v]
            ans.append(dir)
        ans.reverse()
        return ans

    def bfs(self):
        state, random_seq = self.reduce_uncertainty()
        Q = Queue()
        visited = {state}
        Q.put((state, 0))
        prev = {}
        while not Q.empty():
            v, d = Q.get()
            if self.win(v):
                ans = random_seq + self.generate_answer(prev, v)
                return ans
            if d + len(random_seq) > 150:
                return []
            for u, dir in self.gen_new_states(v):
                if u in visited:
                    continue
                Q.put((u, d + 1))
                visited.add(u)
                prev[u] = (v, dir)

    def solve(self):
        ans = self.bfs()
        while len(ans) == 0:
            ans = self.bfs()
        int_to_str = {0: "U", 1: "R", 2: "D", 3: "L"}
        ans = ''.join([int_to_str[i] for i in ans])
        print(ans, len(ans))
        with open('zad_output.txt', 'w') as out:
            out.write(ans)


solution = Solution()
solution.input()
solution.solve()