#include "ptest.h"
#include "BigNumber.h"
#include <bits/stdc++.h>
using namespace std;

/*B_int gcd(B_int a, B_int b)
{
    B_int q, r1, r2, r;
    if (a > b)
    {
        r1 = a;
        r2 = b;
    }
    else
    {
        r1 = b;
        r2 = a;
    }
    while (r2 > zero)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
    }
    return r1;
}*/

//b must < a
void BezoutIdentity(B_int a, B_int b, B_int &rx, B_int &ry)
{
    B_int x = 0;
    B_int y = 1;
    B_int last_x = 1;
    B_int last_y = 0;
    B_int tmp1, tmp2, tmp3;
    while (b != zero)
    {
        B_int q = a / b;
        tmp1 = a % b;
        a = b;
        b = tmp1;
        tmp2 = x;
        x = last_x - q * x;
        last_x = tmp2;
        tmp3 = y;
        y = last_y - q * y;
        last_y = tmp3;
    }
    rx = last_x;
    ry = last_y;
}
//generate n-bit big_number
B_int big_num_generator(int bit)
{
    srand(time(0));
    stringstream ss;
    string s, tmp;
    unsigned out;
    int k = bit / 32;
    for (int i = 0; i < k; i++)
    {
        out = (rand() % (4294967295 - 2147483649)) + 2147483649;
        ss << std::hex << out;
        ss >> tmp;
        s = s + tmp;
        // cout << "out " << std::hex << out << " s " << s << endl;
        tmp.erase();
        ss.str("");
        ss.clear();
    }
    return BigNumber(s);
}
//generating n-bit prime
B_int KeyGenerator(int bit)
{
    B_int return_num;
    while (1)
    {
        return_num = big_num_generator(bit);
        if (PrimalityTest(return_num, 3))
            return return_num;
    }
    return BigNumber("0");
}
//依照範例IO以k個字元為單位打一個空格印出共k*l個字元
void print_for_blank(string text, int k, int l)
{
    //要補給個0
    string out;
    int append_zero = 8 * l - text.length();
    out.assign(append_zero, '0');
    out.append(text);
    for (int i = 0; i < out.length() / k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("%c", out[i * k + j]);
        }
        printf(" ");
    }
}
B_int encyption(B_int ptext, B_int n)
{
    return (ptext * ptext) % n;
}
B_int sqrt_p_3(B_int a, B_int p)
{
    return Power(a, (p + one) / four, p);
}
B_int sqrt_p_5(B_int a, B_int p)
{
    B_int d;
    B_int neg_1 = p - one;
    d = Power(a, (p - one) / four, p);
    if (d == one)
        return Power(a, (p + three) / eight, p);
    else if (d == neg_1)
        return (two * a * Power(four * a, (p - five) / eight, p)) % p;
    return neg_1;
}
bool check_repet(B_int in)
{
    string s = in.getString();
    string s1;
    s1.assign(s, s.length() - 4, 4);
    string s2;
    s2.assign(s, s.length() - 8, 4);
    if (s1 == s2)
        return true;
    return false;
}
B_int decyption(B_int ctext, B_int p, B_int q, B_int n)
{
    B_int r, s, x, y;
    //only deal with p,q % 4 == 3, p,q%8 == 5
    if (p % four == three)
    {
        r = sqrt_p_3(ctext, p);
    }
    else
    {
        r = sqrt_p_5(ctext, p);
    }
    if (q % four == three)
    {
        s = sqrt_p_3(ctext, q);
    }
    else
    {
        s = sqrt_p_5(ctext, q);
    }
    B_int c, d;
    if (p > q)
        BezoutIdentity(p, q, c, d);
    else
        BezoutIdentity(q, p, d, c);
    x = (r * d * q + s * c * p) % n;
    y = (r * d * q - s * c * p) % n;

    if (x < zero)
        x = -x;
    if (y < zero)
        y = -y;

    if (check_repet(x))
        return x;
    else if (check_repet((-x + n)))
        return (-x + n);
    else if (check_repet(y))
        return y;
    else if (check_repet(-y + n))
        return (-y + n);
    return 0;
}
int main()
{

    //Miller Rabin primary test
    B_int bit_256_prime;
    printf("<Miller-Rabin>\n");
    bit_256_prime = KeyGenerator(256);

    //test output 格式 keygenerator需要跑太久了QQ
    //bit_256_prime = big_num_generator(256);

    //output 256bit prime;
    print_for_blank(bit_256_prime.getString(), 8, 8);
    printf("\n\n");

    //Rabin encryption
    string p, q;
    string tmp;
    printf("<Rabin Encryption>\n");
    printf("p = ");
    for (int i = 0; i < 4; i++)
    {
        cin >> tmp;
        p = p + tmp;
    }
    printf("q = ");
    for (int i = 0; i < 4; i++)
    {
        cin >> tmp;
        q = q + tmp;
    }
    B_int P(p);
    B_int Q(q);
    B_int N = P * Q;
    printf("n = pq = ");
    print_for_blank(N.getString(), 8, 8);
    printf("\n\n");
    //plaintext
    string ptext;
    printf("Plaintext: ");
    for (int i = 0; i < 7; i++)
    {
        cin >> tmp;
        ptext = ptext + tmp;
    }
    //16bit repetition padding
    ptext.append(tmp, tmp.length() - 4, 4);
    //16bit repitation padding
    //ptext = ptext + tmp;
    B_int PTEXT(ptext);
    B_int CTEXT = encyption(PTEXT, N);
    printf("Ciphertext = ");
    print_for_blank(CTEXT.getString(), 8, 8);
    printf("\n\n");

    /*decryption*/
    printf("<Rabin Decrpytion>\n");
    string ctext;
    printf("Ciphertext = ");
    for (int i = 0; i < 8; i++)
    {
        cin >> tmp;
        ctext = ctext + tmp;
    }
    B_int CTEXT_2(ctext);

    q.erase();
    p.erase();
    printf("Private Key:\n");
    printf("p = ");
    for (int i = 0; i < 4; i++)
    {
        cin >> tmp;
        p = p + tmp;
    }
    P = p;
    printf("q = ");
    for (int i = 0; i < 4; i++)
    {
        cin >> tmp;
        q = q + tmp;
    }
    Q = q;
    N = P * Q;
    PTEXT = decyption(CTEXT_2, P, Q, N);
    printf("Plaintext = ");
    string text;
    text = PTEXT.getString();
    text.assign(text, 0, text.length() - 4);
    print_for_blank(text, 8, 7);
    //big_num_generator(128).print();
    return 0;
}