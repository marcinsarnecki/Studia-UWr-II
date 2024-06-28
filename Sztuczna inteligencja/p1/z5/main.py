import random


def opt_dist(list, D):
    temp_list = "".join(map(str, list))
    x = temp_list.count('1')
    ans = len(list)  # maksymalny wynik
    for i in range(0, len(list) - D + 1):  # zakldamy, ze ciag jedynek znajduje sie na pozycji 'i'
        ans = min(ans,
                  x - temp_list.count('1', i, i + D) +   # jedynki spoza ciagu zamieniamy na zera
                  D - temp_list.count('1', i, i + D))    # zera w ciagu na jedynki
    return ans


class Solution:
    def __init__(self):
        self.n = 0
        self.m = 0
        self.rowsInput = []
        self.colsInput = []
        self.rows = []
        self.cols = []
        self.TRY_LIMIT = 10000

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
        return all(opt_dist(self.rows[i], self.rowsInput[i]) == 0 for i in range(0, self.n)) \
            and all(opt_dist(self.cols[i], self.colsInput[i]) == 0 for i in range(0, self.m))

    def input(self):
        with open('zad5_input.txt') as input_file:
            text = input_file.read().splitlines()
            self.n = int(text[0].split(' ')[0])
            self.m = int(text[0].split(' ')[1])
            self.rowsInput = [0] * self.n
            self.colsInput = [0] * self.m
            for i in range(0, self.n):
                self.rowsInput[i] = int(text[i+1])
            for i in range(0, self.m):
                self.colsInput[i] = int(text[i+1+self.n])

    def try_solve(self):
        for k in range(0, self.TRY_LIMIT):
            if self.check():
                break
            if random.randint(1, 100) <= 1:
                i = random.randint(0, self.n - 1)
                j = random.randint(0, self.m - 1)
                self.change_cell(i, j)
            elif random.randint(1, 2) == 1:
                i = random.randint(0, self.n - 1)
                best = self.m + self.n + 3
                jj = 0
                for j in range(0, self.m):
                    self.change_cell(i, j)
                    if opt_dist(self.rows[i], self.rowsInput[i]) + opt_dist(self.cols[j], self.colsInput[j]) < best:
                        best = opt_dist(self.rows[i], self.rowsInput[i]) + opt_dist(self.cols[j], self.colsInput[j])
                        jj = i
                    self.change_cell(i, j)
                self.change_cell(i, jj)
            else:
                j = random.randint(0, self.m - 1)
                best = self.m + self.n + 3
                ii = 0
                for i in range(0, self.n):
                    self.change_cell(i, j)
                    if opt_dist(self.cols[j], self.colsInput[j]) + opt_dist(self.rows[i], self.rowsInput[i])< best:
                        best = opt_dist(self.rows[j], self.rowsInput[j]) + opt_dist(self.rows[i], self.rowsInput[i])
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
        with open('zad5_output.txt', 'w') as f:
            for i in range(0, self.n):
                output = ''.join(map(lambda x: '#' if x == 1 else '.', self.rows[i]))
                print(output, file=f)


solution = Solution()
solution.input()
solution.solve()
solution.print_all_to_file()
