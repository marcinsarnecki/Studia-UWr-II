from queue import Queue


class Solution:
    def __init__(self):
        self.n = 0
        self.m = 0
        self.rowsInput = []
        self.colsInput = []
        self.answer = []
        self.rows_combinations = []
        self.cols_combinations = []
        self.bad = Queue()

    def input(self):
        with open('zad_input.txt') as input_file:
            text = input_file.read().splitlines()
            self.n = int(text[0].split(' ')[0])
            self.m = int(text[0].split(' ')[1])
            self.rowsInput = [[]] * self.n
            self.colsInput = [[]] * self.m
            for i in range(0, self.n):
                self.rowsInput[i] = [int(x) for x in text[i + 1].split()]
            for i in range(0, self.m):
                self.colsInput[i] = [int(x) for x in text[i + 1 + self.n].split()]
            self.answer = [[-1 for j in range(self.m)] for i in range(self.n)]

    def generate_blocks(self, n, blocks):
        if not blocks:
            return [[0] * n]  # nic nie zostalo, same zera
        if len(blocks) == 1:  # pojedyczny blok
            ans = []
            for pos in range(n - blocks[0] + 1):
                ans.append([0] * pos + [1] * blocks[0] + [0] * (n - pos - blocks[0]))
            return ans
        ans = []
        first = blocks[0]
        remaining_blocks = blocks[1:]
        for position in range(n - first + 1 - sum(remaining_blocks) - len(remaining_blocks)):
            for rest in self.generate_blocks(n - position - first - 1, remaining_blocks):
                ans.append([0] * position + [1] * first + [0] + rest)
        return ans

    def check_in_rows(self, y, x, value):
        return all(self.rows_combinations[y][i][x] == value for i in range(len(self.rows_combinations[y])))

    def check_in_cols(self, y, x, value):
        return all(self.cols_combinations[x][i][y] == value for i in range(len(self.cols_combinations[x])))

    def delete_useless_rows(self, y, x, value):
        self.rows_combinations[y] = [row for row in self.rows_combinations[y] if row[x] == value]
        self.check_debug()

    def delete_useless_cols(self, y, x, value):
        self.cols_combinations[x] = [col for col in self.cols_combinations[x] if col[y] == value]
        self.check_debug()

    def try_to_guess(self, y, x):
        self.check_debug()
        value = self.rows_combinations[y][0][x]
        if self.check_in_rows(y, x, value):
            self.delete_useless_cols(y, x, value)
            self.answer[y][x] = value
            return
        value = self.cols_combinations[x][0][y]
        if self.check_in_cols(y, x, value):
            self.delete_useless_rows(y, x, value)
            self.answer[y][x] = value
            return
        self.bad.put((y, x))

    def check_debug(self):
        for i in range(self.n):
            for j in range(len(self.rows_combinations[i])):
                assert (len(self.rows_combinations[i][j]) == self.m)
        for i in range(self.m):
            for j in range(len(self.cols_combinations[i])):
                assert (len(self.cols_combinations[i][j]) == self.n)
        assert (len(self.rows_combinations) == self.n)
        assert (len(self.cols_combinations) == self.m)

    def solve(self):
        self.rows_combinations = [self.generate_blocks(self.m, self.rowsInput[i]) for i in range(0, self.n)]
        self.cols_combinations = [self.generate_blocks(self.n, self.colsInput[j]) for j in range(0, self.m)]
        self.check_debug()
        for y in range(self.n):
            for x in range(self.m):
                self.try_to_guess(y, x)
        while not self.bad.empty():
            (y, x) = self.bad.get()
            self.try_to_guess(y, x)

    def print_all(self):
        for i in range(0, self.n):
            print(''.join(map(lambda x: '#' if x == 1 else '.' if x == 0 else '_', self.answer[i])))

    def print_all_to_file(self):
        with open('zad_output.txt', 'w') as f:
            for i in range(0, self.n):
                output = ''.join(map(lambda x: '#' if x == 1 else '.', self.answer[i]))
                print(output, file=f)


solution = Solution()
solution.input()
solution.solve()
# solution.print_all()
solution.print_all_to_file()
