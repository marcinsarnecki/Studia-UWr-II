# Marcin Sarnecki
# losuje karty i sprawdzam po kolei od najmocniejszych układów pokerowych kto wygrywa


from random import randint

BLOTKARZ_RANGE = 9

def get_blotkarz_card():
    return randint(0, 3), randint(2, 2 + BLOTKARZ_RANGE - 1)  # color, card


def get_figurant_card():
    return randint(0,3), randint(11, 14)  # 11-14 jack queen king ace


def blotkarz():
    cards = set()
    while len(cards) < 5:
        cards.add(get_blotkarz_card())
    return sorted(cards, key=lambda x: (x[1], x[0]))


def figurant():
    cards = set()
    while len(cards) < 5:
        cards.add(get_figurant_card())
    return sorted(cards, key=lambda x: (x[1], x[0]))


def pick_winner(b, f):
    f_colors, f_cards = zip(*f)
    b_colors, b_cards = zip(*b)
    # print(f)
    # print(f_cards)
    # print(f_colors)
    # print(b)
    # print(b_cards)
    # print(b_colors)

    # poker (blotkarz tylko moze)
    if b_cards[0] == b_cards[4] + 4 and len(set(b_cards)) == 5 and b_colors[0] == b_colors[4]:
        return 'b'
    # kareta, pierwszy sprawdzany figurant bo ma wyzsze karty
    if f_cards[0] == f_cards[3] or f_cards[1] == f_cards[4]:
        return 'f'
    if b_cards[0] == b_cards[3] or b_cards[1] == b_cards[4]:
        return 'b'
    # full (trojka + para) wygrywa gracz z lepsza trojka wiec oczywiscie f najpierw
    if (f_cards[0] == f_cards[1] and f_cards[2] == f_cards[4]) or (f_cards[0] == f_cards[2] and f_cards[3] == f_cards[4]):
        return 'f'
    if (b_cards[0] == b_cards[1] and b_cards[2] == b_cards[4]) or (b_cards[0] == b_cards[2] and b_cards[3] == b_cards[4]):
        return 'b'
    # kolor
    if f_colors[0] == f_colors[4]:
        return 'f'
    if b_colors[0] == b_colors[4]:
        return 'b'
    # strit
    if b_cards[0] == b_cards[4] + 4 and len(set(b_cards)) == 5:
        return 'b'
    # pomocnicze zliczanie kart
    count_b = [0] * 15
    count_f = [0] * 15
    for card in b_cards:
        count_b[card] += 1
    for card in f_cards:
        count_f[card] += 1
    # trojka
    for i in range(2, 11):
        if count_b[i] == 3:
            return 'b'
    for i in range(11, 15):
        if count_f[i] == 3:
            return 'f'
    # dwie pary
    pairs_b = 0
    pairs_f = 0
    for i in range(2, 11):
        if count_b[i] == 2:
            pairs_b += 1
    for i in range(11, 15):
        if count_f[i] == 2:
            pairs_f += 1
    if pairs_f == 2:
        return 'f'
    if pairs_b == 2:
        return 'b'
    # para
    if pairs_f == 1:
        return 'f'
    if pairs_b == 1:
        return 'b'
    # najwyzsza karta
    return 'f'


for i in range(9, 1, -1):
    BLOTKARZ_RANGE = i
    b = 0
    f = 0
    for i in range(10000):
        if pick_winner(blotkarz(), figurant()) == 'f':
            f += 1
        else:
            b += 1
    percent = (b / (b + f)) * 100.0
    print("blotkarz {}: {:.2f}%".format(BLOTKARZ_RANGE, percent))

