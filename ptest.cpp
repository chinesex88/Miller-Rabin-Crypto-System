#include <bits/stdc++.h>
#include "ptest.h"
#include "BigNumber.h"
using namespace std;
//useful number
B_int one = 1;
B_int two = 2;
B_int three = 3;
B_int zero = 0;
B_int four = 4;
B_int five = 5;
B_int eight = 8;
//use for speed up
int primetable[]{
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
    37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
    83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
    197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
    263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
    331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
    397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523,
    541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661,
    673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
    751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
    827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
    907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977,
    983, 991, 997};
//return a^b % module
B_int Power(B_int a, B_int b, B_int module)
{
    //useful number.
    B_int one = 1;
    B_int two = 2;
    B_int zero = 0;

    B_int return_val = 1;
    a = a % module;
    while (b > zero)
    {
        //if b is  odd
        if (b % two == one)
            return_val = (return_val * a) % module;

        b = b / two;
        a = (a * a) % module;
    }
    return return_val;
}
//test t times
bool PrimalityTest(B_int n, int t)
{
    /*
    B_int prime;
    for (int i = 0; i < sizeof(primetable) / 4; i++)
    {
        prime = primetable[i];
        if (n % prime == zero && n != prime)
            return false;
    }
    */

    if (n == one)
        return false;
    if (n == two)
        return true;
    //find n = m*2^k
    srand(time(0));
    B_int n_minus_one = n - one;
    B_int m = n_minus_one;
    int tmp = 0;
    while (m % two == zero)
    {

        m = m / two;
        tmp++;
    }
    B_int k = tmp;
    B_int k_minus_one = k - one;
    for (int i = 0; i < t; i++)
    {
        //pick random num in [2,n-2]
        B_int random = rand();
        B_int n_minus_two = n - two;
        random = random % n_minus_two;
        B_int a = two + random;
        //compute y = a^m %n
        B_int y = Power(a, m, n);

        if (y != one && y != n_minus_one)
        {
            B_int j = 1;
            while (j <= k_minus_one && y != n_minus_one)
            {
                y = Power(y, two, n);
                if (y == one)
                    return false;
                j = j + one;
            }
            if (y != n_minus_one)
                return false;
        }
    }
    return true;
}
