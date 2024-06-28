import random

class Solution:
    def __init__(self):
        self.n = 0
        self.m = 0
        self.rowsInput = []
        self.colsInput = []
        self.rows = []
        self.cols = []
        self.cache = {}
        self.TRY_LIMIT = 100000

    def change_cell(self, i, j):
        self.rows[i][j] ^= 1
        self.cols[j][i] ^= 1

    def reset_array(self):
        self.rows = [[0] * self.m for i in range(0, self.n)]
        self.cols = [[0] * self.n for j in range(0, self.m)]
        for i in range(0, self.n):
            for j in range(0, self.m):
                if random.randint(0, 1) == 1:
                    self.change_cell(i, j)

    def check(self):
        return all(self.opt_dist(self.rows[i], self.rowsInput[i]) == 0 for i in range(0, self.n)) \
            and all(self.opt_dist(self.cols[i], self.colsInput[i]) == 0 for i in range(0, self.m))

    def input(self):
        with open('zad_input.txt') as input_file:
            text = input_file.read().splitlines()
            self.n = int(text[0].split(' ')[0])
            self.m = int(text[0].split(' ')[1])
            self.rowsInput = [[]] * self.n
            self.colsInput = [[]] * self.m
            for i in range(0, self.n):
                self.rowsInput[i] = [int(x) for x in text[i+1].split()]
            for i in range(0, self.m):
                self.colsInput[i] = [int(x) for x in text[i+1+self.n].split()]

            # print('input:')
            # for i in range(0, self.n):
            #     print(self.rowsInput[i])
            # for i in range(0, self.m):
            #     print(self.colsInput[i])

    def opt_dist(self, row, blocks):
        key = tuple(row), tuple(blocks)
        if key in self.cache:
            return self.cache[key]
        if not blocks:
            return sum(row)
        current = blocks[0]
        last = len(row) - sum(blocks) - len(blocks) + 1  # najpozniejszy start
        before = 0
        num_1s_in_window = sum(row[:current])

        swap_after_current = len(row) > current and row[current]
        best = (current - num_1s_in_window) + swap_after_current + self.opt_dist(row[current + 1:], blocks[1:])

        if last > 0:
            for i in range(last):
                num_1s_in_window -= row[i]
                before += row[i]
                num_1s_in_window += row[i + current]
                swap_after_current = len(row) > i + current + 1 and row[i + current + 1]
                best = min(best, (current - num_1s_in_window) + before + swap_after_current +  # ile 0 na 1 w aktualnym, ile 1 przed na 0, czy swap tuz za + rekurencyjnie
                           self.opt_dist(row[i + current + 2:], blocks[1:]))
        self.cache[key] = best
        return best

    def try_solve(self):
        for k in range(0, self.TRY_LIMIT):
            if self.check():
                break
            # if random.randint(1, 100) <= 3:
            #     i = random.randint(0, self.n - 1)
            #     j = random.randint(0, self.m - 1)
            #     self.change_cell(i, j)
            elif random.randint(1, 2) == 1:
                i = random.randint(0, self.n - 1)
                best = self.m + self.n + 3
                jj = 0
                for j in range(0, self.m):
                    self.change_cell(i, j)
                    if self.opt_dist(self.rows[i], self.rowsInput[i]) + self.opt_dist(self.cols[j], self.colsInput[j]) < best:
                        best = self.opt_dist(self.rows[i], self.rowsInput[i]) + self.opt_dist(self.cols[j], self.colsInput[j])
                        jj = j
                    self.change_cell(i, j)
                self.change_cell(i, jj)
            else:
                j = random.randint(0, self.m - 1)
                best = self.m + self.n + 3
                ii = 0
                for i in range(0, self.n):
                    self.change_cell(i, j)
                    if self.opt_dist(self.cols[j], self.colsInput[j]) + self.opt_dist(self.rows[i], self.rowsInput[i]) < best:
                        best = self.opt_dist(self.cols[j], self.colsInput[j]) + self.opt_dist(self.rows[i], self.rowsInput[i])
                        ii = i
                    self.change_cell(i, j)
                self.change_cell(ii, j)

    def solve(self):
        self.reset_array()
        while not self.check():
            self.reset_array()
            self.try_solve()

    def print_all(self):
        for i in range(0, self.n):
            print(''.join(map(lambda x: '#' if x == 1 else '.', self.rows[i])))

    def print_all_to_file(self):
        with open('zad_output.txt', 'w') as f:
            for i in range(0, self.n):
                output = ''.join(map(lambda x: '#' if x == 1 else '.', self.rows[i]))
                print(output, file=f)


solution = Solution()
solution.input()
solution.solve()
solution.print_all_to_file()