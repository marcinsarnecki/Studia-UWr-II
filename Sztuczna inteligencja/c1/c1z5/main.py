from itertools import combinations
from random import randint

BLOTKARZ_RANGE = 9


def get_blotkarz_card():
    return randint(0, 3), randint(2, 2 + BLOTKARZ_RANGE - 1)  # color, card


def get_figurant_card():
    return randint(0, 3), randint(11, 14)  # 11-14 jack queen king ace


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


def gen_all_blotkarz_cards():
    return [(color, card) for color in range(0, 4) for card in range(2, 11)]


def gen_all_figurant_cards():
    return [(color, card) for color in range(0, 4) for card in range(11, 15)]


def gen_all_blotkarz_hands():
    return list(combinations(gen_all_blotkarz_cards(), 5))


def gen_all_figurant_hands():
    return list(combinations(gen_all_figurant_cards(), 5))


def score_blotkarz(cards):
    bdict = {x: 0 for x in range(2, 11)}
    for card in cards:
        bdict[card[1]] += 1
    pairs = {2: 0, 3: 0, 4: 0}
    for card in bdict:
        if bdict[card] > 1:
            pairs[bdict[card]] += 1
    cards.sort(key=lambda x: x[1])
    straight = all(cards[i][1] == cards[i + 1][1] - 1 for i in range(0, 4))
    color = all(cards[i][0] == cards[i + 1][0] for i in range(0, 4))
    if straight and color:
        return 8
    if pairs[4] != 0:
        return 7
    if pairs[3] != 0 and pairs[2] != 0:
        return 6
    if color:
        return 5
    if straight:
        return 4
    if pairs[3] != 0:
        return 3
    return pairs[2]


def score_figurant(cards):
    # print('fcards = ', cards)
    bdict = {x: 0 for x in range(11, 15)}
    for card in cards:
        bdict[card[1]] += 1
    pairs = {2: 0, 3: 0, 4: 0}
    for card in bdict:
        if bdict[card] > 1:
            pairs[bdict[card]] += 1
    cards.sort(key=lambda x: x[1])
    if pairs[4] != 0:
        return 7
    if pairs[3] != 0 and pairs[2] != 0:
        return 6
    if pairs[3] != 0:
        return 3
    return pairs[2]


all_blotkarz_scores = [score_blotkarz(list(b)) for b in gen_all_blotkarz_hands()]

all_figurant_scores = [score_figurant(list(f)) for f in gen_all_figurant_hands()]

wins = 0
a = len(all_blotkarz_scores) * len(all_figurant_scores)
for b in all_blotkarz_scores:
    for f in all_figurant_scores:
        if f < b:
            wins += 1
print(1.0 * wins / a)
