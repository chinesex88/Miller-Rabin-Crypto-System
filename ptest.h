#include <cstdio>
#include "BigNumber.h"

typedef class BigNumber B_int;
bool PrimalityTest(B_int n, int t);
B_int primegenerator(int bit);
B_int Power(B_int a, B_int b, B_int module);
//useful number
extern B_int one;
extern B_int two;
extern B_int three;
extern B_int zero;
extern B_int four;
extern B_int five;
extern B_int eight;