/*
 * CS:APP Data Lab
 *
 * 唐泽楠 24307140056
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/*
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* shift 1 into the sign bit */
  return 1 << 31;
}

// P2
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* x^y = (x|y) & ~(x&y), and x|y = ~(~x & ~y) by De Morgan */
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* x>>31 is all ones exactly when x<0; mask the negation -x = ~x+1 */
  return (~x + 1) & (x >> 31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* extract byte src, clear byte dst, then insert */
  int s = src << 3;
  int d = dst << 3;
  int byte = (x >> s) & 0xFF;
  int mask = 0xFF << d;
  return (x & ~mask) | (byte << d);
}

// P5
/*
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* arithmetic shift, then clear the n copied sign bits;
     ((1<<31)>>n)<<1 has exactly the top n bits set (0 when n==0) */
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* m = 0x0F0F0F0F selects every low nibble */
  int m = 0x0F | (0x0F << 8);
  m = m | (m << 16);
  return ((x >> 4) & m) | ((x & m) << 4);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* x|(x+1) fills the lowest 0 bit; the lowest 0 bit of y is ~y & (y+1) */
  int y = x | (x + 1);
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* fold halves with xor; bit 0 ends up as the parity of all 32 bits */
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return (x & 1) ^ 1;
}

// P9
/*
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* logical right shift by m = n mod 32, left part shifted by (32-m) mod 32 */
  int m = n & 31;
  int right = (x >> m) & ~(((1 << 31) >> m) << 1);
  int left = x << ((~m + 1) & 31);
  return right | left;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* add (half-1) plus the quotient's lsb, then truncate: rounds half to even */
  int half = 1 << (n + ~0);
  int bias = half + ~0 + ((x >> n) & 1);
  return ((x + bias) >> n) << n;
}

// P11
/*
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* (x&y) + ((x^y)>>1) is floor((x+y)/2) without overflow;
     when the sum is odd and x>y the midpoint rounds toward x, i.e. +1.
     x>y is decided by the sign of y-x when signs agree (no overflow),
     or by the sign of y when signs differ. */
  int sx = x >> 31;
  int sy = y >> 31;
  int d = sx ^ sy;
  int yx = y + ~x + 1;
  int gt = ((~d & yx) | (d & sy)) >> 31;
  int fl = (x & y) + ((x ^ y) >> 1);
  int odd = (x ^ y) & 1;
  return fl + (odd & gt);
}


// P12
/*
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* p<=q: if signs differ it is p<0; otherwise q-p never overflows and
     p<=q iff the sign bit of q-p is 0. All flags are 0 or all ones. */
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int dax = sa ^ sx;
  int dxb = sx ^ sb;
  int xa = x + ~a + 1;
  int bx = b + ~x + 1;
  int ax = ~xa + 1;
  int xb = ~bx + 1;
  int le_ax = (dax & sa) | (~dax & ~(xa >> 31));
  int le_xb = (dxb & sx) | (~dxb & ~(bx >> 31));
  int le_bx = (dxb & sb) | (~dxb & ~(xb >> 31));
  int le_xa = (dax & sx) | (~dax & ~(ax >> 31));
  return ((le_ax & le_xb) | (le_bx & le_xa)) & 1;
}

// P13
/*
 * mul5Sat - return x*5, and if x*5 overflow, change the result to
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* x*5 fits iff -0x19999999 <= x <= 0x19999999; c-x and x+c cannot
     overflow under the matching sign guard */
  int c = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x99;
  int sx = x >> 31;
  int above = ~sx & ((c + ~x + 1) >> 31);
  int below = sx & ((x + c) >> 31);
  int smin = 1 << 31;
  int smax = ~smin;
  int p = (x << 2) + x;
  int ov = above | below;
  return (above & smax) | (below & smin) | (~ov & p);
}

// P14
/*
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* track how many times 2^32 is lost by wrapping: each add contributes
     k in {-1,0,1} (sign of the overflow), and the two contributions can
     never have the same nonzero sign, so their sum is the answer */
  int w = x + y;
  int t = w + z;
  int o1 = ((x ^ w) & (y ^ w)) >> 31;
  int o2 = ((w ^ t) & (z ^ t)) >> 31;
  int k1 = o1 & ((x >> 31) | 1);
  int k2 = o2 & ((w >> 31) | 1);
  return k1 + k2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  unsigned m;
  unsigned r;
  if (exp == 0xFF)
    return uf;
  if (exp == 0) {
    /* subnormal: magnitude field scales linearly, halve 3*frac to even;
       a carry into the exponent field is exactly the subnormal->normal case */
    m = frac + (frac << 1);
    r = m & 1;
    m = m >> 1;
    m = m + (r & m & 1);
    return sign | m;
  }
  /* normal: m = 3*M in [3*2^23, 3*2^24); target value is m * 2^(exp-151) */
  m = frac | 0x800000;
  m = m + (m << 1);
  if (m >> 25) {
    /* mantissa is m/4, exponent grows by one; round 2 dropped bits to even */
    r = m & 3;
    m = m >> 2;
    if (r == 3 || (r == 2 && (m & 1)))
      m = m + 1;
    exp = exp + 1;
  } else {
    /* mantissa is m/2, exponent unchanged; round 1 dropped bit to even */
    r = m & 1;
    m = m >> 1;
    m = m + (r & m & 1);
  }
  if (m >> 24) {
    m = m >> 1;
    exp = exp + 1;
  }
  if (exp >= 0xFF)
    return sign | 0x7F800000;
  return sign | (exp << 23) | (m & 0x7FFFFF);
}

// P16
/*
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  unsigned m;
  unsigned k;
  unsigned low;
  unsigned half;
  unsigned mint;
  if (exp == 0xFF)
    return uf;
  if (exp <= 125)
    return sign;
  if (exp == 126) {
    /* magnitude in [0.5, 1): exactly 0.5 ties to 0, everything else to 1 */
    if (frac == 0)
      return sign;
    return sign | 0x3F800000;
  }
  if (exp >= 150)
    return uf;
  /* 1 <= |f| < 2^23: drop k = 150-exp fraction bits of M with round-to-even */
  m = frac | 0x800000;
  k = 150 - exp;
  low = m & ((1 << k) - 1);
  half = 1 << (k - 1);
  mint = m >> k;
  if (low > half || (low == half && (mint & 1)))
    mint = mint + 1;
  m = mint << k;
  if (m >> 24) {
    m = m >> 1;
    exp = exp + 1;
  }
  return sign | (exp << 23) | (m & 0x7FFFFF);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned ux = x;
  unsigned h = 31;
  unsigned exp;
  unsigned frac;
  unsigned shift;
  unsigned rest;
  unsigned halfbit;
  if (x == 0)
    return 0;
  if (x < 0) {
    sign = 0x80000000;
    ux = -x;
  }
  /* h = index of the highest set bit of ux */
  while (!(ux >> h))
    h = h - 1;
  exp = h + 127;
  if (h <= 23) {
    frac = ux << (23 - h);
  } else {
    /* more than 24 significant bits: round the dropped part to even */
    shift = h - 23;
    frac = ux >> shift;
    rest = ux & ((1 << shift) - 1);
    halfbit = 1 << (shift - 1);
    if (rest > halfbit || (rest == halfbit && (frac & 1)))
      frac = frac + 1;
    if (frac >> 24) {
      frac = frac >> 1;
      exp = exp + 1;
    }
  }
  return sign | (exp << 23) | (frac & 0x7FFFFF);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* classic divide and conquer popcount with 2/4-bit group masks */
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0F | (0x0F << 8);
  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* swap halves, then bytes, nibbles, pairs and single bits;
     each mask is derived from the previous one by m ^ (m << w) */
  int m16 = 0xFF | (0xFF << 8);
  int m8 = m16 ^ (m16 << 8);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);
  x = (x << 16) | ((x >> 16) & m16);
  x = ((x & m8) << 8) | ((x >> 8) & m8);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m1) << 1) | ((x >> 1) & m1);
  return x;
}
