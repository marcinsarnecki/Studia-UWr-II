# Marcin Sarnecki
# szukam optymalnego miejsca na ciąg jedynek

def opt_dist(list, D):
    x = list.count('1')
    ans = len(list)  # maksymalny wynik
    for i in range(0, len(list) - D + 1):  # zakldamy, ze ciag jedynek znajduje sie na pozycji 'i'
        ans = min(ans,
                  x - list.count('1', i, i + D) +   # jedynki spoza ciagu zamieniamy na zera
                  D - list.count('1', i, i + D))    # zera w ciagu na jedynki
    return ans


# print(opt_dist('0010001000', 5))  # 3
# print(opt_dist('0010001000', 4))  # 4
# print(opt_dist('0010001000', 3))  # 3
# print(opt_dist('0010001000', 2))  # 2
# print(opt_dist('0010001000', 1))  # 1
# print(opt_dist('0010001000', 2))  # 2

with open('zad4_input.txt', 'r') as input, open('zad4_output.txt', 'w') as output:
    for line in input:
        a, b = line.split()
        digits, n = str(a), int(b)
        ans = opt_dist(digits, n)
        output.write(f'{ans}\n')
