#! /usr/bin/env python3
########________<<<<<<<<        ````````--------,,,,,,,,********
from collections import deque as deq
from copy import deepcopy
########========........--------,,,,,,,,********________>>>>>>>>
class MagicSqr:
    """"""
    def __init__(self, str=None):
        ''' 
  Initialize MagicSqr from input string. This constructor's
  called with non empty str only twice for str8 and revs search,
        '''
        if not str: return
        self.buf   = deq((deq(str[:4]), deq(str[4:])))
        self.move  = 'Z'
        self.depth = 0
        self.pare  = None # parent square
        #
        self.buf[1].reverse()

    def copy(self):
        """
  This is like a copy constructor. Because buf is a composite 
  reference object we must use recursive deepcopy.
        """
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
               "{}   p/m: {} {}".format(key[1],
                                        self.pare.__repr__(),
                                        self.move))
        return "\n".join(str) + "\n"

    def __hash__(self):
        """
  This is hashing the string representation, so we can use the
  unique dict mapping, alternatevly we can use directly square
  numeric representation e.g. 12345678 as key in a binary tree. 
        """
        return hash(self.__repr__())

    def __eq__(self, othr):
        ''''''
        return self.__hash__() == othr.__hash__()

    def xchg(self, dummy=None):
        """
  The dummy argument is here, cos we want to use different move
  methods uniformly in a loop.
        """
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
    
    def backtrace(self):
        """"""
        sqr = self
        while sqr:
            print(sqr)
            sqr = sqr.pare

if __name__ == '__main__':
    #
    maxdepth = -1
    move_methods = 'xchg', 'rotate', 'clock'
    #
    sqr = MagicSqr("12345678")
    queue = deq()
    lookup = dict()
    queue.append(sqr)
    lookup[sqr] = sqr
    #
    SQR = MagicSqr("41263785")
    QUEUE = deq()
    LOOKUP = dict()
    QUEUE.append(SQR)
    LOOKUP[SQR] = SQR
    #
    str8 = revs = False
    while True:
        # str8
        sqr = queue.popleft()
        if sqr.depth == maxdepth: break
        if sqr in LOOKUP:
            str8 = True
            break
        for method in move_methods:
            copy = sqr.copy()
            getattr(copy, method)()
            if copy in lookup:
                del copy
            else:
                queue.append(copy)
                lookup[copy] = copy
        # revs
        SQR = QUEUE.popleft()
        if SQR in lookup:
            revs = True
            break
        for method in move_methods:
            copy = SQR.copy()
            getattr(copy, method)(-1)
            if copy in LOOKUP:
                del copy
            else:
                QUEUE.append(copy)
                LOOKUP[copy] = copy
    if str8 or revs: 
        print("\nBacktrace")
        print("=========")
    if str8:
        print('[str8]')
        sqr.backtrace()
        print('[revs]')
        LOOKUP[sqr].backtrace()
    if revs:
        print('[str8]\n')
        lookup[SQR].backtrace()
        print('[revs]\n')
        SQR.backtrace()

# log:
