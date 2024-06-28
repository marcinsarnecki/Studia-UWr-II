# Marcin Sarnecki
# Każdą linię przetwarzam programowaniem dynamicznym - dla każdego pola obliczam najlepszy wynik, jeśli
# słowa mogą zaczynać się w tym miejscu i wypełnić całą linię od tego miejsca, przetwarzam od prawej do lewej


input_file = 'zad2_input.txt'
output_file = 'zad2_output.txt'
words_file = 'words_for_ai1.txt'

word_set = set()
m = 0


def process_line(line):
    n = len(line)
    dp = [-1] * n  # dp[i] - najlepsza wartość zaczynając od miejsca 'i'
    ans = [-1] * n  # ans[i] - długość słowa zaczynającego się w 'i' w optymalnym podziale
    for i in range(n-1, -1, -1):  # od prawej do lewej
        for j in range(1, min(m, n - i) + 1):
            sub = line[i:i+j]
            if sub in word_set:
                if i + j == n:  # pierwsze słowo
                    dp[i] = j ** 2
                    ans[i] = j
                elif dp[i+j] != -1 and dp[i+j] + j**2 > dp[i]: # lepszy wynik
                    dp[i] = dp[i+j] + j**2
                    ans[i] = j
    i = 0
    answer_line = ''
    while i < n:
        answer_line += line[i:i+ans[i]] + ' '
        i += ans[i]
    # print(answer_line)
    return answer_line


with open(words_file, 'r', encoding='utf-8') as file:
    words = file.read().splitlines()
    for word in words:
        word = word.strip()
        if len(word) > m:
            m = len(word)
word_set = set(words)
with open(output_file, 'w', encoding='utf-8') as output:
    for single_line in open(input_file, encoding='utf-8'):
        output.write(process_line(single_line.rstrip()) + '\n')




