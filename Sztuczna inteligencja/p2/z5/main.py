from heapq import heappop, heappush
from queue import Queue, PriorityQueue

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]


class Solution:
    def __init__(self):
        self.targets = set()
        self.initial_positions = list()
        self.walls = set()
        self.dist = []
        self.visited = []

    def input(self):
        with open('zad_input.txt') as inp:
            for i, row in enumerate(inp):
                temp = []
                vis = []
                for j, char in enumerate(row):
                    if char in '#':
                        vis.append(2)
                    else:
                        vis.append(0)
                    if char in ('G', 'B'):
                        self.targets.add((i, j))
                    if char in ('S', 'B'):
                        self.initial_positions.append((i, j))
                    temp.append(0)
                self.dist.append(temp)
                self.visited.append(vis)
            self.initial_positions = tuple(sorted(self.initial_positions))

    def move(self, state, dir):
        new_state = set()
        for (y, x) in state:
            if self.visited[y + dy[dir]][x + dx[dir]] != 2:
                new_state.add((y + dy[dir], x + dx[dir]))
            else:
                new_state.add((y, x))
        return tuple(sorted(new_state))

    def gen_new_states(self, state):
        return ((tuple(sorted(self.move(state, dir))), dir) for dir in range(0, 4))

    def win(self, state):
        return all(pos in self.targets for pos in state)

    def bfs(self):
        Q = Queue()
        for (y, x) in self.targets:
            self.visited[y][x] = 1
            self.dist[y][x] = 0
            Q.put((y, x))
        while not Q.empty():
            (y, x) = Q.get()
            for dir in range(0, 4):
                (yy, xx) = (y + dy[dir], x + dx[dir])
                if self.visited[yy][xx] == 0:
                    self.visited[yy][xx] = 1
                    self.dist[yy][xx] = self.dist[y][x] + 1
                    Q.put((yy, xx))

    def heura(self, positions):
        return max([self.dist[y][x] for (y, x) in positions])

    def a_star(self):
        q = PriorityQueue()
        visited = set()
        visited.add(self.initial_positions)
        q.put((self.heura(self.initial_positions), self.initial_positions, []))
        while not q.empty():
            (cost, positions, seq) = q.get()
            visited.add(tuple(positions))
            for state, dir in self.gen_new_states(positions):
                if state in visited:
                    continue
                for (y, x) in state:
                    b = (y, x) in self.targets
                    if not b:
                        break
                if b:
                    return seq + [dir]
                else:
                    cost = self.heura(state)
                    q.put((int(cost + len(seq)), state, seq + [dir]))

    def solve(self):
        self.bfs()
        ans = self.a_star()
        int_to_str = {0: "U", 1: "R", 2: "D", 3: "L"}
        ans = ''.join([int_to_str[i] for i in ans])
        print(ans, len(ans))
        with open('zad_output.txt', 'w') as out:
            out.write(ans)


solution = Solution()
solution.input()
solution.solve()