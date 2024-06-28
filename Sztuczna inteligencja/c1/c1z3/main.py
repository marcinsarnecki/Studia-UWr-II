import random

input_file = 'zad2_input.txt'
output_file = 'zad2_output.txt'
words_file = 'words_for_ai1.txt'

word_set = set()
m = 0


def losowe(line):
    n = len(line)
    starts = []
    stack = []
    found = [0]
    ans = []

    def dfs(pos):
        if pos == n:
            for x in stack:
                ans.append(x)
            found[0] = 1
        if pos >= n:
            return
        if len(starts[pos]) == 0:
            return
        for word in starts[pos]:
            if found[0] == 0:
                stack.append(word)
                dfs(pos + word)
                stack.pop()

    for i in range(0, n):
        starts.append([])
    for i in range(n - 1, -1, -1):  # from right to left
        for j in range(1, min(m, n - i) + 1):
            sub = line[i:i + j]
            if sub in word_set:
                starts[i].append(j)
        random.shuffle(starts[i])

    dfs(0)
    i = 0
    idx = 0
    answer_line = ''
    while i < n:
        answer_line += line[i:i + ans[idx]] + ' '
        i += ans[idx]
        idx += 1
    return answer_line.rstrip()


def process_line(line):
    n = len(line)
    dp = [-1] * n  # dp[i] - best value starting from 'i' to the end of line
    ans = [-1] * n  # ans[i] - length of word starting at 'i'
    for i in range(n - 1, -1, -1):  # from right to left
        for j in range(1, min(m, n - i) + 1):
            sub = line[i:i + j]
            if sub in word_set:
                if i + j == n:  # first word
                    dp[i] = j ** 2
                    ans[i] = j
                elif dp[i + j] != -1 and dp[i + j] + j ** 2 > dp[i]:  # found better value
                    dp[i] = dp[i + j] + j ** 2
                    ans[i] = j
    i = 0
    answer_line = ''
    while i < n:
        answer_line += line[i:i + ans[i]] + ' '
        i += ans[i]
    return answer_line.rstrip()


with open(words_file, 'r', encoding='utf-8') as file:
    words = file.read().splitlines()
    for word in words:
        word = word.strip()
        if len(word) > m:
            m = len(word)
word_set = set(words)

lines = []
for line in open('real_tadeusz.txt', encoding='utf-8-sig'):
    lines.append(line.strip('\n'))


def tadeusz():
    match1 = 0
    match2 = 0
    total = 0
    for line in open('bezspacji.txt', encoding='utf-8'):
        if lines[total] == process_line(line.rstrip()):
            match1 += 1
        if lines[total] == losowe(line.rstrip()):
            match2 += 1
        total += 1
    print('najdluzsze slowa:    {}'.format(1.0 * match1 / total))
    print('losowe slowa:    {}'.format(1.0 * match2 / total))


tadeusz()