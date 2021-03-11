## Magic Squares
This is Rubik's Square I guess, the text and the link are in the description!
Yea, I think this is the 3rd similar problem, but this time I got it
right. We have initial and final positions of the magic square, although I
didn't find any magic, most probably cos I'm very poor mathematician. In chess
for example when there is a problem find mate in 2 or smth we don't know the
final position, so it's one way search, here we can start from both ends in
different directions. First I've wrote the program in C++, than in Python, 
but in both programs there are lot of unnecessary things, and than started writing
it in C with moar clear mind what to do exactly, but have lost interest:)
```Python
+------+------+------+------+------+------+------+------+------+------+------+
|      |      |      |      |      |      |      |      |      |      |      |
|      |      |      |      |      |      |      |      |      |      |      |
+------+------+------+------+------+------+------+------+------+------+------+
|      | 3584 |      | REVS |      |      | Prog | rami | call | y bo | th e |
|      | 6721 |      |      |      |      | xecu | tion | s st | art  | from |
+------B------+------+------+------+------+------+------+------+------+------+
|      | 5843 |      | 3584 |      |      | the  | bott | om T | he s | econ |
|      | 7216 |      | 6721 |      |      | d on | e wi | th r | ever | se m |
+------+------C------+--B---+------+------+------+------+------+------+------+
|      | 5413 |      | 4358 | 8435 |      | oves | But  | we c | an g | et t |
|      | 7826 |      | 1672 B 2167 |      | he f | ull  | move | s go | ing  |
+------+--B---+------+------+-A----+------+------+------+------+------+------+
|      | 4135 |      |      | 2167 |      | firs | t up | and  | then | down |
|      | 8267 |      |      | 8435 |      | BCBC | BBBC | BBBA | CBBB | C    |
+------+----B-+------+------+---C--+------+------+------+------+------+------+
| 3541 B 1354 |      |      | 2417 |      |      |      |      |      |      |
| 6782 | 2678 |      |      | 8365 |      |      |      |      |      |      |
C------+------+------+------+---B--+------+------+------+------+------+------+
| 3481 |      |      |      | 7241 |      |      |      |      |      |      |
| 6572 |      |      |      | 5836 |      |      |      |      |      |      |
+---B--+------+------+------+------B------+------+------+------+------+------+
| 4813 |      |      |      | 1724 |      |      |      |      |      |      |
| 5726 |      |      |      | 6583 |      |      |      |      |      |      |
+--C---+------+------+------+--B---+------+------+------+------+------+------+
| 4123 |      |      |      | 4172 | 4612 |      |      |      |      |      |
| 5876 |      |      |      | 3658 C 3578 |      |      |      |      |      |
+----B-+------+------+------+------+------+------+------+------+------+------+
| 1234 | str8 |      |      |      |      |      |      |      |      |      |
| 8765 |      |      |      |      |      |      |      |      |      |      |
+------+------+------+------+------+------+------+------+------+------+------+
```
