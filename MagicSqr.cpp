/***************************************************************
 * Problem 6: Magic Squares                                    *
 ***************************************************************
 * Following the success of the magic cube, Mr. Rubik invented *
 * its planar version, called magic squares. This is a sheet   *
 * composed of 8 equal-sized squares (see Figure 3).           *
 ***************************************************************
 * 1234                                                        *
 * 8765                                                        *
 *                                                             *
 * Figure 3: Magic Square                                      *
 ***************************************************************
 * In this task we consider the version where each square has  *
 * a different colour. Colours are denoted by the first 8      *
 * positive integers (see Figure 3). A sheet configuration is  *
 * given by the sequence of colours obtained by reading the    *
 * colours of the squares starting at the upper left corner    *
 * and going in clockwise direction. For instance, the         *
 * configuration of Figure 3 is given by the sequence          *
 * (1,2,3,4,5,6,7,8). This configuration is the initial        *
 * configuration.                                              *
 ***************************************************************
 * Three basic transformations, identified by the letters 'A', *
 * 'B' and 'C', can be applied to a sheet:                     *
 * - 'A': exchange the top and bottom row,                     *
 * - 'B': single right circular shifting of the rectangle,     *
 * - 'C': single clockwise rotation of the middle four         *
 *        squares.                                             *
 ***************************************************************
 * All configurations are available using the three basic      *
 * transformations.                                            *
 *                                                             *
 * 1234  A  8765  1234  B  4123  1234  C  1724                 *
 * 8765 --> 1234, 8765 --> 5876, 8765 --> 8635                 *
 *                                                             *
 * Figure 4: Basic transformations                             *
 ***************************************************************
 * You are to write a program that computes a sequence of      *
 * basic transformations that transforms the initial           *
 * configuration of Figure 3 to a specific target              *
 * configuration (Subtask A). Two extra points will be given   *
 * for the solution if the length of the transformation        *
 * sequence does not exceed 300 (Subtask B).                   *
 ***************************************************************
 * https://ioinformatics.org/files/ioi1996problem6.pdf         *
 ***************************************************************/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <map>
typedef enum {A=1,B,C,D} move_t;
#define _ptr ((char*) _buff)
#define SIZE (sizeof (long long))
#define HALFLIFE (sizeof (int))
class MagicSqr {
private:
  int _buff[2] {0,0};
  char _move;
  char _depth;
  unsigned short _parnt;
  void setmove(move_t m);
public:
  MagicSqr(const char* const);
  void spit();
  void xchg(); // A
  void rol();  // str8 B (little endian)
  void ror();  // revs B
  void cw();   // str8 C
  void ccw();  // revs C
  void str8(move_t);
  void revs(move_t);
  void nop() {};
  void setparnt(unsigned short j) { _parnt = j; }
  void setdepth(char depth) { _depth = depth; }
  unsigned short getparnt() { return _parnt; }
  char getdepth() { return _depth; }
  char getmove() { return _move; }
  int64_t key() { return *((int64_t*) _buff); }
};
#define DISP (SIZE + HALFLIFE - 1)
MagicSqr::MagicSqr(const char* const clr):
  _move('N'),
  _depth(0),
  _parnt(0)
{
  for (int j{0}; j < HALFLIFE; ++j) {
    _ptr[j] = clr[j] + '0';
  }
  for (int j{HALFLIFE}; j < SIZE; ++j) {
    _ptr[j] = clr[DISP - j] + '0';
  }
}
void MagicSqr::spit()
{
  static char out[SIZE];
  memcpy(out, _ptr, HALFLIFE);
  printf("%s parnt %d (%c)\n", out, _parnt, _move);
  memcpy(out, _ptr + HALFLIFE, HALFLIFE);
  printf("%s depth %d\n\n", out, _depth);
}
void MagicSqr::xchg()
{
  static int temp;
  temp = _buff[0];
  _buff[0] = _buff[1];
  _buff[1] = temp;
}
void MagicSqr::rol()
{
  for (int j = 0; j < 2; ++j) {
    asm ("mov %1, %%ebx\n\t"
         "rol $8, %%ebx\n\t"
         "mov %%ebx, %0"
         : "+r" (_buff[j])
         : "r"  (_buff[j])
         : "%ebx"
         );
  }
}
void MagicSqr::ror()
{
  for (int j = 0; j < 2; ++j) {
    asm ("mov %1, %%ebx\n\t"
         "ror $8, %%ebx\n\t"
         "mov %%ebx, %0"
         : "+r" (_buff[j])
         : "r"  (_buff[j])
         : "%ebx"
         );
  }
}
void MagicSqr::cw()
//   _ _
// 0 1 2 3
//   _ _ 
// 4 5 6 7
{
  static char t;
  t = _ptr[1];
  _ptr[1] = _ptr[5];
  _ptr[5] = _ptr[6];
  _ptr[6] = _ptr[2];
  _ptr[2] = t;
}
void MagicSqr::ccw()
{
  static char t;
  t = _ptr[1];
  _ptr[1] = _ptr[2];
  _ptr[2] = _ptr[6];
  _ptr[6] = _ptr[5];
  _ptr[5] = t;
}
void MagicSqr::str8(move_t m)
{
  static void (MagicSqr::*f[])() {
    &MagicSqr::nop,
    &MagicSqr::xchg, 
    &MagicSqr::rol,
    &MagicSqr::cw
  };
  (this->*(f[m]))();
  setmove(m);
}
void MagicSqr::revs(move_t m)
{
  static void (MagicSqr::*f[])() {&MagicSqr::nop,
  /*1 2 3 4 5 6 7 8 9 0 1 2 3 4*/ &MagicSqr::xchg, 
  /*    b     o     o     m    */ &MagicSqr::ror,
  /*_ _ _ _ _ _ _ _ _ _ _ _ _ _*/ &MagicSqr::ccw};
  (this->*(f[m]))();
  setmove(m);
}
void MagicSqr::setmove(move_t m)
{
  _move = 'A' - 1 + m;
}
class Block {
private:
  MagicSqr* _magic;
  int _j {0}; // block pointer
public:
  Block(int size)
  {
    _magic = (MagicSqr*) malloc(size * sizeof (MagicSqr));
  }
  ~Block()
  {
    free(_magic);
  }
  MagicSqr& operator[] (int j) { return _magic[j]; }
  int cons(const char* const);
  int fork(int j);
  void unfork() { --_j; };
  void spit(int j);
};
int Block::cons(const char* const clr)
{
  _magic[_j] = MagicSqr(clr);
  return _j++;
}
int Block::fork(int j)
{
  _magic[_j] = _magic[j];
  _magic[_j].setparnt(j);
  _magic[_j].setdepth(_magic[j].getdepth() + 1);
  return _j++;
}
void Block::spit(int j)
{
  for (;;) {
    _magic[j].spit();
    if (_magic[j].getmove() == 'N') break;
    j = _magic[j].getparnt();
  }
}
int main()
{
  const int maxdepth = -1;
  const char start[] {1,2,3,4,5,6,7,8};
  const char final[] {4,6,1,2,8,7,5,3};
  Block block(1<<16);
  // str8
  int f;
  std::queue<int> q;
  std::map<int64_t, int> s;
  q.push(block.cons(start));
  s[block[0].key()] = 0;
  // revs
  int F;
  std::queue<int> Q;
  std::map<int64_t, int> S;
  Q.push(block.cons(final));
  S[block[1].key()] = 1;

  for (;;) {
    // str8
    f = q.front();
    q.pop();
    if (block[f].getdepth() == maxdepth) break; // ugh
    if (S.count(block[f].key())) {
      F = S[block[f].key()];
      break;
    }
    for (int m {A}; m != D; ++m) {
      int j = block.fork(f);      
      block[j].str8((move_t) m);
      if (s.count(block[j].key())) {
        block.unfork();
      } else {
        q.push(j);
        s[block[j].key()] = j;
      }
    }
    // revs
    F = Q.front();
    Q.pop();
    if (s.count(block[F].key())) {
      f = s[block[F].key()];
      break;
    }
    for (int m {A}; m != D; ++m) {
      int j = block.fork(F);      
      block[j].revs((move_t) m);
      if (S.count(block[j].key())) {
        block.unfork();
      } else {
        Q.push(j);
        S[block[j].key()] = j;
      }
    }
  }
  printf("Blocks f=%d, F=%d\n", f, F);
  puts("str8");
  block.spit(f);
  puts("revs");
  block.spit(F);
}
// log:
