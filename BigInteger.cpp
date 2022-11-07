#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class BigInteger { 
    private: 
        string bigInt;
        bool negative;
    public: 
        BigInteger();
        BigInteger(string bigIntStr);
        BigInteger(int number);
        void setInteger(string bigIntStr);
        const string& getInteger();   
        void setSign(bool sign);
        const bool& getSign();
        BigInteger absoluteValue();
        void operator = (BigInteger other);
        bool operator == (BigInteger other);
        bool operator < (BigInteger other);
        bool operator > (BigInteger other);
        BigInteger operator + (BigInteger other);
        BigInteger operator - (BigInteger other);
    private:
        BigInteger(string bigIntStr, bool sign);
        bool equals(BigInteger int1, BigInteger int2);
        bool lessThan(BigInteger int1, BigInteger int2);
        bool greaterThan(BigInteger int1, BigInteger int2);
        BigInteger add(BigInteger int1, BigInteger int2);
};

int main() {
    //tests
    int i = 0;
    while(i < 10) {
        cout << "BigInt 1: ";
        string input1;
        string input2;
        cin >> input1;
        BigInteger int1(input1);
        cout << "BigInt 2: ";
        cin >> input2;
        BigInteger int2(input2);
        cout << int1.getInteger() << " " << int1.getSign() << "\n";
        cout << int2.getInteger() << " " << int2.getSign() << "\n";
        BigInteger intSum = int1 - int2;
        cout << intSum.getInteger() << " " << intSum.getSign() << "\n";
        i++;
    }
}


//public functions
BigInteger::BigInteger() {
    bigInt = "0";
    negative = false;
}
BigInteger::BigInteger(string bigIntStr) {
    setInteger(bigIntStr);
}

BigInteger::BigInteger(int number) {
    negative = number < 0;
    bigInt = to_string(abs(number));
}

void BigInteger::setInteger(string bigIntStr) {
    if(bigIntStr.length() > 0 && bigIntStr.at(0) == '-') negative = true;
    else negative = false;
    int i = (negative) ? 1 : 0;
    while(i < bigIntStr.length() && bigIntStr.at(i) == '0') i++;
    int fin = i;
    while(i < bigIntStr.length()) {
        if(!isdigit(bigIntStr[i])) throw invalid_argument("Invalid string.");
        i++;
    }
    if(fin == bigIntStr.length()) {
        bigInt = "0";
        negative = false;
    }else bigInt = bigIntStr.substr(fin);
}

const string& BigInteger::getInteger() {
    return bigInt;
}

void BigInteger::setSign(bool sign) {
    negative = sign;
}

const bool& BigInteger::getSign() {
    return negative;
}

BigInteger BigInteger::absoluteValue() {
    return BigInteger(getInteger());
}

void BigInteger::operator = (BigInteger other) {
    setInteger(other.getInteger());
    setSign(other.getSign());
}

bool BigInteger::operator == (BigInteger other) {
    return equals(*this, other);
}

bool BigInteger::operator < (BigInteger other) {
    return lessThan(*this, other);
}

bool BigInteger::operator > (BigInteger other) {
    return greaterThan(*this, other);
}

BigInteger BigInteger::operator + (BigInteger other) {
    return add(*this, other);
}

BigInteger BigInteger::operator - (BigInteger other) {
    BigInteger temp(other.getInteger(), !other.getSign());
    return add(*this, temp);
}

//private functions
BigInteger::BigInteger(string bigIntStr, bool sign) {
    string temp = (sign) ? "-" : "";
    temp += bigIntStr;
    setInteger(temp);
}

bool BigInteger::equals(BigInteger int1, BigInteger int2) {
    return (int1.getInteger() == int2.getInteger() && int1.getSign() == int2.getSign());
}

bool BigInteger::lessThan(BigInteger int1, BigInteger int2) {   
    if(int1.getSign() != int2.getSign()) return (int1.getSign()) ? true : false;
    if(equals(int1,int2)) return false;
    bool lessThan = true;
    if(int1.getInteger().length() == int2.getInteger().length()) {
        string int1str = int1.getInteger();
        string int2str = int2.getInteger();
        for(int i = 0; i < int1str.length(); i++) {
            if(int1str.at(i) > int2str.at(i)) {
                lessThan = false;
                break;
            }else if(int1str.at(i) < int2str.at(i)) {
                lessThan = true;
                break;
            }
        }
    }else { 
        lessThan = int1.getInteger().length() < int2.getInteger().length();
    }
    return (int1.getSign()) ? !lessThan : lessThan;
}

bool BigInteger::greaterThan(BigInteger int1, BigInteger int2) {
    if(int1.getSign() != int2.getSign()) return (int1.getSign()) ? false : true;
    if(equals(int1,int2)) return false;
    bool greaterThan = true;
    if(int1.getInteger().length() == int2.getInteger().length()) {
        string int1str = int1.getInteger();
        string int2str = int2.getInteger();
        for(int i = 0; i < int1str.length(); i++) {
            if(int1str.at(i) < int2str.at(i)) {
                greaterThan = false;
                break;
            }else if(int1str.at(i) > int2str.at(i)) {
                greaterThan = true;
                break;
            }
        }
    }else { 
        greaterThan = int1.getInteger().length() > int2.getInteger().length();
    }
    return (int1.getSign()) ? !greaterThan : greaterThan;
}

BigInteger BigInteger::add(BigInteger int1, BigInteger int2) {
    int carry = 0;
    string finStr = "";
    bool finSign = false;
    if(int1.getSign() == int2.getSign()) {
        finSign = int1.getSign();
        string int1Str = int1.getInteger();
        string int2Str = int2.getInteger();
        int a = int1Str.length()-1;
        int b = int2Str.length()-1;
        while(a > -1 && b > -1) {
            int sum = int1Str[a] + int2Str[b] + carry - (2 * '0');
            char dig = (sum%10) + '0'; 
            finStr += dig;
            carry = sum/10;
            a--;
            b--;
        }
        while(a > -1) {
            int sum = int1Str[a] + carry - '0';
            char dig = (sum%10) + '0';
            finStr += dig;
            carry = sum/10;
            a--;
        }
        while(b > -1) {
            int sum = int2Str[b] + carry - '0';
            char dig = (sum%10) + '0';
            finStr += dig;
            carry = sum/10;
            b--;
        }
        if(carry > 0) finStr += (carry + '0');
    }else {
        BigInteger int1S = (int1 < int2.absoluteValue()) ? int2: int1;
        BigInteger int2S = (int1 < int2.absoluteValue()) ? int1: int2;
        string int1Str = int1S.getInteger();
        string int2Str = int2S.getInteger();
        finSign = (int1S.getSign()) ? true : false;
        int a = int1Str.length()-1;
        int b = int2Str.length()-1;
        while(a > -1 && b > -1) {
            int difference = int1Str[a] - int2Str[b] - carry;
            char dig = (difference < 0) ? 10 + difference + '0' : difference + '0';
            finStr += dig;
            carry = (difference < 0) ? 1 : 0;
            a--;
            b--;
        }
        while(a > -1) {
            int difference = int1Str[a] - carry - '0';
            char dig = (difference < 0) ? 10 + difference + '0' : difference + '0';
            finStr += dig;
            carry = (difference < 0) ? 1 : 0;
            a--;
        }
    }
    reverse(finStr.begin(), finStr.end());
    if(finSign) finStr = "-" + finStr;
    BigInteger sum(finStr);
    return sum;
}






