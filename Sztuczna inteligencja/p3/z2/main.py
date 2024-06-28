from queue import Queue
import copy


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

    def check_in_rows(self, y, x, value, rows_combinations):
        return all(rows_combinations[y][i][x] == value for i in range(len(rows_combinations[y])))

    def check_in_cols(self, y, x, value, cols_combinations):
        return all(cols_combinations[x][i][y] == value for i in range(len(cols_combinations[x])))

    def delete_useless_rows(self, y, x, value, rows_combinations):
        rows_combinations[y] = [row for row in rows_combinations[y] if row[x] == value]

    def delete_useless_cols(self, y, x, value, cols_combinations):
        cols_combinations[x] = [col for col in cols_combinations[x] if col[y] == value]

    def try_to_guess(self, y, x, rows_combinations, cols_combinations, answer):
        value = rows_combinations[y][0][x]
        if self.check_in_rows(y, x, value, rows_combinations):
            self.delete_useless_cols(y, x, value, cols_combinations)
            answer[y][x] = value
            return True
        value = cols_combinations[x][0][y]
        if self.check_in_cols(y, x, value, cols_combinations):
            self.delete_useless_rows(y, x, value, rows_combinations)
            answer[y][x] = value
            return True

    def check_for_empty_combinations(self, rows_combinations, cols_combinations):
        for y in range(self.n):
            if len(rows_combinations[y]) == 0:
                return True
        for x in range(self.m):
            if len(cols_combinations[x]) == 0:
                return True
        return False

    def try_to_reduce_bad(self, rows_combinations, cols_combinations, bad, answer):
        while True:
            new_bad = []
            changed = False
            for (y, x) in bad:
                if len(rows_combinations[y]) == 0 or len(cols_combinations[x]) == 0:
                    return []
                if self.try_to_guess(y, x, rows_combinations, cols_combinations, answer):
                    changed = True
                else:
                    new_bad.append((y, x))
            bad = new_bad
            if not changed:
                return bad

    def backtracking_search(self, rows_combinations, cols_combinations, bad, answer):
        bad = self.try_to_reduce_bad(rows_combinations, cols_combinations, bad, answer)
        if self.check_for_empty_combinations(rows_combinations, cols_combinations):
            return False, []
        if len(bad) > 0:
            (y, x) = bad.pop(0)
            answer_new = copy.deepcopy(answer)
            rows_combinations_new = copy.deepcopy(rows_combinations)
            cols_combinations_new = copy.deepcopy(cols_combinations)
            answer_new[y][x] = 0
            self.delete_useless_rows(y, x, 0, rows_combinations_new)
            self.delete_useless_cols(y, x, 0, cols_combinations_new)
            res, final_answer = self.backtracking_search(rows_combinations_new, cols_combinations_new, bad.copy(), answer_new)
            if res:
                return True, final_answer
            answer_new = copy.deepcopy(answer)
            rows_combinations_new = copy.deepcopy(rows_combinations)
            cols_combinations_new = copy.deepcopy(cols_combinations)
            answer_new[y][x] = 1
            self.delete_useless_rows(y, x, 1, rows_combinations_new)
            self.delete_useless_cols(y, x, 1, cols_combinations_new)
            res, final_answer = self.backtracking_search(rows_combinations_new, cols_combinations_new, bad.copy(), answer_new)
            if res:
                return True, final_answer
            return False, []
        return True, answer

    def solve(self):
        self.rows_combinations = [self.generate_blocks(self.m, self.rowsInput[i]) for i in range(0, self.n)]
        self.cols_combinations = [self.generate_blocks(self.n, self.colsInput[j]) for j in range(0, self.m)]
        bad = []
        for y in range(self.n):
            for x in range(self.m):
                if not self.try_to_guess(y, x, self.rows_combinations, self.cols_combinations, self.answer):
                    bad.append((y, x))
        res, answer = self.backtracking_search(self.rows_combinations, self.cols_combinations, bad, self.answer)
        if res:
            self.print_all(answer)
        else:
            print('no answer exists! :( error')

    def print_all(self, answer):
        for i in range(0, self.n):
            print(''.join(map(lambda x: '#' if x == 1 else '.' if x == 0 else '_', answer[i])))
        self.answer = answer

    def print_all_to_file(self):
        with open('zad_output.txt', 'w') as f:
            for i in range(0, self.n):
                output = ''.join(map(lambda x: '#' if x == 1 else '.', self.answer[i]))
                print(output, file=f)


solution = Solution()
solution.input()
solution.solve()
solution.print_all_to_file()
