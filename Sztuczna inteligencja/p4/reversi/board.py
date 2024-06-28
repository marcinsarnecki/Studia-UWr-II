import sys
from copy import deepcopy


class Board:
    __dirs = [(0, 1), (1, 0), (-1, 0), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def __init__(self):
        self.board = [[-1 for _ in range(8)] for _ in range(8)]
        self.whites = {(3, 3), (4, 4)}
        self.blacks = {(3, 4), (4, 3)}
        self.board[3][3] = True  # if white player
        self.board[3][4] = False
        self.board[4][3] = False
        self.board[4][4] = True
        self.movesMade = 0

    # this adds new disk and flips all other oponent's pieces
    # when new disk is added we need to check all directions
    def addDisk(self, r, c, color):
        setToAdd = self.whites if color else self.blacks  # we will be removing
        setToRemove = self.blacks if color else self.whites
        setToAdd.add((r, c))
        self.board[r][c] = color
        toAdd = set()
        for (rD, cD) in Board.__dirs:
            pom = set()
            eR = r + rD
            eC = c + cD
            while (8 > eR > -1 and 8 > eC > -1 and
                   self.board[eR][eC] == (not color)):
                pom.add((eR, eC))
                eR += rD
                eC += cD
                if 8 > eR > -1 and 8 > eC > -1 and self.board[eR][eC] == color:
                    for x in pom:
                        toAdd.add(x)
                    break

        for x in toAdd:
            self.board[x[0]][x[1]] = color
            setToAdd.add(x)
            setToRemove.remove(x)
        self.movesMade += 1

    def __inBounds(self, y, x):
        return 8 > y > -1 and 8 > x > -1

    def __getPossibilityInDirection(self, sR, sC, dR, dC, color):
        while (self.__inBounds(sR + dR, sC + dC) and
               self.board[sR + dR][sC + dC] == (not color)):
            sR += dR
            sC += dC
            if (self.__inBounds(sR + dR, sC + dC) and
                    self.board[sR + dR][sC + dC] == -1):
                return (sR + dR, sC + dC)

        return False

    def getAllPossibilitiesToMove(self, color):
        allPoss = set()
        for (r, c) in self.getPositions(color):
            for (dR, dC) in self.__dirs:
                res = self.__getPossibilityInDirection(r, c, dR, dC, color)
                if res:
                    allPoss.add(res)
        return list(allPoss)

    def getPositions(self, color):
        toClone = self.whites if color else self.blacks
        return {x for x in toClone}

    def printBoard(self):
        for x in self.board:
            line = ""
            for i in x:
                if i == -1:
                    line += '.'
                if i == True:
                    line += '#'
                if i == False:
                    line += 'o'
            print(line, file=sys.stderr)
        print(file=sys.stderr)

    def isDone(self):
        return self.movesMade == 60

    def calculate(self):
        return len(self.blacks), len(self.whites)

    def copy(self):
        ret = Board()
        ret.board = deepcopy(self.board)
        ret.whites = deepcopy(self.whites)
        ret.blacks = deepcopy(self.blacks)
        ret.movesMade = self.movesMade
        return ret

    def isWinner(self, PLAYER_COLOR):
        w = len(self.whites)
        b = len(self.blacks)
        if w == b:
            return 0.5
        if PLAYER_COLOR:
            return w > b
        else:
            return b > w
