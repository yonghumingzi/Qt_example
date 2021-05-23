#include "sha-1.h"

string transMap[2] = {"0", "1"};

map<char, string> hex2binMap = {
    {'0',"0000"}, {'1',"0001"},{'2',"0010"},{'3',"0011"},{'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
    {'8',"1000"}, {'9',"1001"},{'A',"1010"},{'B',"1011"},{'B',"1100"},{'D',"1101"},{'E',"1110"},{'F',"1111"}
};

map<string, char> bin2hexMap = {
    {"0000",'0'}, {"0001",'1'},{"0010",'2'},{"0011",'3'},{"0100",'4'},{"0101",'5'},{"0110",'6'},{"0111",'7'},
    {"1000",'8'}, {"1001",'9'},{"1010",'A'},{"1011",'B'},{"1100",'C'},{"1101",'D'},{"1110",'E'},{"1111",'F'}
};

char SHA_1::bin2hex(int a, int b, int c, int d){
    return bin2hexMap[transMap[a] + transMap[b] + transMap[c] + transMap[d]];
}

string SHA_1::hex2bin(char a) {
    return hex2binMap[a];
}

// convert number a to 'base'-base with 'length'
vector<int> SHA_1::baseConvert(const unsigned long long &a, int base, int length) {
    vector<int> result;
    stack<int> tmpstack;
    int res;
    unsigned long long a1 = a;
    do {
        res = a1 % base;
        tmpstack.push(res);
        a1 /= base;
    } while (a1);

    for (int i = 0; i < length - tmpstack.size(); i++)
        result.push_back(0);

    while (!tmpstack.empty()) {
        result.push_back(tmpstack.top());
        tmpstack.pop();
    }
    return result;
}

vector<int> SHA_1::char2hex(const string &word) {
    vector<int> result(NUM, 0);
    for (int i = 0; i < NUM; i++) {
        if (word[i] >= '0' && word[i] <= '9')
            result[i] = word[i] - '0';
        else if (word[i] >= 'A' && word[i] <= 'Z')
            result[i] = 10 + word[i] - 'A';
    }
    return result;
}

string SHA_1::hex2char(const vector<int> &a) {
    string result;
    for (int i = 0; i < NUM; i++) {
        if (a[i] >= 0 && a[i] <= 9)
            result += a[i] + '0';
        else if (a[i] >= 10 && a[i] <= 15)
            result += a[i] - 10 + 'A';
    }
    return result;
}

string SHA_1::char2binary(char c)
{
    string result;
    char tmp;
    for(int i=0; i<8; i++)
    {
        if ((c >>(i-1)) & 0x01 == 1)
            result += "1";
        else
            result += "0";
    }
    for(int a=1;a<5;a++)
    {
        tmp = result[a];
        result[a] = result[8-a];
        result[8-a] = tmp;
    }
   return result;
}

string SHA_1::ADD(const string &a, const string &b) {
    vector<int> A = char2hex(a);
    vector<int> B = char2hex(b);
    vector<int> Result(NUM, 0);
    int sign = 0;
    for (int i = NUM - 1; i >= 0; i--) {
        Result[i] = A[i] + B[i] + sign;
        sign = Result[i] / HEX;
        Result[i] %= HEX;
    }
    return hex2char(Result);
}

string SHA_1::AND(const string &a, const string &b) {
    vector<int> a_int = char2hex(a);
    vector<int> b_int = char2hex(b);
    vector<int> r_int(NUM, 0);
    for (int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] & b_int[i];
    return hex2char(r_int);
}

string SHA_1::OR(const string &a, const string &b) {
    vector<int> a_int = char2hex(a);
    vector<int> b_int = char2hex(b);
    vector<int> r_int(NUM, 0);
    for (int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] | b_int[i];
    return hex2char(r_int);
}

string SHA_1::XOR(const string &a, const string &b) {
    vector<int> a_int = char2hex(a);
    vector<int> b_int = char2hex(b);
    vector<int> r_int(NUM, 0);
    for (int i = 0; i < NUM; i++)
        r_int[i] = a_int[i] ^ b_int[i];
    return hex2char(r_int);
}

string SHA_1::NOT(const string &a) {
    vector<int> a_int = char2hex(a);
    vector<int> r_int(NUM, 0);
    for (int i = 0; i < NUM; i++)
        r_int[i] = HEX - 1 - a_int[i];
    return hex2char(r_int);
}

// rotate left
string SHA_1::ROTL(const string &a, int s) {
    vector<int> A = char2hex(a);
    unsigned long a_int = 0;
    for (int i = 0; i < NUM; i++)
        a_int += A[NUM - 1 - i] * pow(HEX, i);
    a_int = (a_int >> (NUM * 4 - s)) | (a_int << s);
    vector<int> A1 = baseConvert(a_int, HEX, NUM);
    return hex2char(A1);
}

//Ft logic function
string SHA_1::Ft(int t, const string &B, const string &C, const string &D) {
    if (t >= 0 && t < 20)
        return OR(AND(B, C), AND(NOT(B), D));
    else if (t >= 20 && t < 40)
        return XOR(XOR(B, C), D);
    else if (t >= 40 && t < 60)
        return OR(OR(AND(B, C), AND(B, D)), AND(C, D));
    else if (t >= 60 && t < 80)
        return XOR(XOR(B, C), D);
}

// Kt round constant
string SHA_1::Kt(int t) {
    if (t >= 0 && t < 20)
        return "5A827999";
    else if (t >= 20 && t < 40)
        return "6ED9EBA1";
    else if (t >= 40 && t < 60)
        return "8F1BBCDC";
    else if (t >= 60 && t < 80)
        return "CA62C1D6";
}

// initialize variables H0-H4
void SHA_1::initVars(){
    H0 = "67452301";
    H1 = "EFCDAB89";
    H2 = "98BADCFE";
    H3 = "10325476";
    H4 = "C3D2E1F0";
}

vector<vector<int>> SHA_1::padding(const string &bytes_msg) {
    unsigned long long length = bytes_msg.size();
    int d = (447 - length) % BLOCK;
    vector<int> l = baseConvert(length, 2, 64);
    vector<vector<int>> result;
    string str_result;
    str_result += bytes_msg;
    str_result += '1';
    for (int i = 0; i < d; i++)
        str_result += '0';
    for (int i = 0; i < l.size(); i++)
        str_result += '0' + l[i];

    int n = str_result.size() / BLOCK;
    result.resize(n, vector<int>(BLOCK, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < BLOCK; j++)
            result[i][j] = str_result[i * BLOCK + j] - '0';
    return result;
}

// rearrange to 16 sub-blocks
vector<vector<string>> SHA_1::rearrange(const vector<vector<int>> &result) {
    vector<vector<string>> exp_result(result.size(), vector<string>(HEX, ""));
    for (int i = 0; i < exp_result.size(); i++)
        for (int j = 0; j < HEX; j++)
            for(int k = 0; k < WID; k+=4)
                exp_result[i][j] += bin2hex(result[i][j*WID+k], result[i][j*WID+k+1], result[i][j*WID+k+2], result[i][j*WID+k+3]);
    return exp_result;
}

// generate a SHA-1 digest
string SHA_1::generate_SHA1(const string &msg) {
    initVars();
    string bytes_msg;
    string tmp;
    for (int i = 0; i < msg.size(); i++)
        bytes_msg += char2binary(msg[i]);

    vector<vector<int>> y = padding(bytes_msg);
    vector<vector<string>> exp_y = rearrange(y);
    vector<string> W(80, "");
    for (int i = 0; i < y.size(); i++) {
        // expand to 80 groups
        for (int t = 0; t < 16; t++)
            W[t] = exp_y[i][t];
        for (int t = 16; t < 80; t++) {
            W[t] = ROTL(XOR(XOR(XOR(W[t-3], W[t-8]), W[t-14]), W[t-16]), 1);
        }
        string A = H0;
        string B = H1;
        string C = H2;
        string D = H3;
        string E = H4;
        // 4 rounds computation
        for (int t = 0; t < 80; t++) {
            tmp = ADD(ADD(ADD(ADD(ROTL(A, 5), Ft(t, B, C, D)), E), W[t]), Kt(t));
            E = D;
            D = C;
            C = ROTL(B, 30);
            B = A;
            A = tmp;
        }
        H0 = ADD(H0, A);
        H1 = ADD(H1, B);
        H2 = ADD(H2, C);
        H3 = ADD(H3, D);
        H4 = ADD(H4, E);
    }
    string result = H0 + H1 + H2 + H3 + H4;
    // transform to lower case
    transform(result.begin(), result.end(), result.begin(),::tolower);
    return result;
}
