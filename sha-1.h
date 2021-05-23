#ifndef SHA1_H
#define SHA1_H
#endif // SHA1_H

#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <string>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define NUM 8
#define HEX 16
#define WID 32
#define BLOCK 512

using namespace std;

class SHA_1 {
public:
    char bin2hex(int a, int b, int c, int d);
    string hex2bin(char a);
    // convert number a to 'base'-base with 'length'
    vector<int> baseConvert(const unsigned long long &a, int base, int length);
    vector<int> char2hex(const string &word);
    string hex2char(const vector<int> &a);
    string char2binary(const char a);
    // AND, OR, XOR, NOT, ADD operations in byte
    string AND(const string &a, const string &b);
    string OR(const string &a, const string &b);
    string XOR(const string &a, const string &b);
    string NOT(const string &a);
    string ADD(const string &a, const string &b);
    // rotate left
    string ROTL(const string &a, int s);
    //Ft logic function
    string Ft(int t, const string &B, const string &C, const string &D);
    // Kt round constant
    string Kt(int t);
    // initialize variables H0-H4
    void initVars();
    vector<vector<int> > padding(const string &b_msg);
    // rearrange to 16 sub-blocks
    vector<vector<string> > rearrange(const vector<vector<int> > &result);
    // generate a SHA-1 digest
    string generate_SHA1(const string &msg);
private:
    string H0;
    string H1;
    string H2;
    string H3;
    string H4;
};
