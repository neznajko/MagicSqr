#! /usr/bin/env python3
########________<<<<<<<<        ````````--------,,,,,,,,********
from collections import deque as deq
from copy import deepcopy
########========........--------,,,,,,,,********________>>>>>>>>
class MagicSqr:
    """"""
    def __init__(self, str=None):
        ''''''
        if not str: return
        self.buf   = deq((deq(str[:4]), deq(str[4:])))
        self.move  = 'Z'
        self.depth = 0
        self.pare  = None
        #
        self.buf[1].reverse()

    def copy(self):
        """"""
        sqr = MagicSqr()
        sqr.buf   = deepcopy(self.buf)
        sqr.depth = self.depth + 1
        sqr.pare  = self
        return sqr

    def key(self): return ["".join(x) for x in self.buf]

    def __repr__(self):
        return "".join(self.key())

    def __str__(self):
        """"""
        key = self.key()
        str = ("{} depth: {}".format(key[0], self.depth),
               "{}  move: {}".format(key[1], self.move))
        return "\n".join(str) + "\n"

    def __hash__(self):
        """"""
        return hash("".join(self.key()))

    def __eq__(self, othr):
        ''''''
        return self.__hash__() == othr.__hash__()

    def xchg(self, dummy=None):
        """"""
        self.buf.rotate()
        self.move = 'A'

    def rotate(self, n=1):
        ''''''
        for x in self.buf: x.rotate(n)
        self.move = 'B'

    def cw(self):
        """"""
        t = self.buf[0][1]
        self.buf[0][1] = self.buf[1][1]
        self.buf[1][1] = self.buf[1][2]
        self.buf[1][2] = self.buf[0][2]
        self.buf[0][2] = t

    def ccw(self):
        ''''''
        t = self.buf[0][1]
        self.buf[0][1] = self.buf[0][2]
        self.buf[0][2] = self.buf[1][2]
        self.buf[1][2] = self.buf[1][1]
        self.buf[1][1] = t

    def clock(self, clockwise=1):
        """"""
        if clockwise == 1:
            self.cw()
        else:
            self.ccw()
        self.move = 'C'

if __name__ == '__main__':
    #
    maxdepth = 1
    move_methods = 'xchg', 'rotate', 'clock'
    #
    sqr = MagicSqr("12345678")
    queue = deq()
    lookup = dict()
    queue.append(sqr)
    lookup[sqr] = sqr
    #
    print(sqr)
    for method in move_methods:
        getattr(sqr, method)()
        print(sqr)
# log:
