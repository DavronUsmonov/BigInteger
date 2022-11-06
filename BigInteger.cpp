#include <string>
#include <iostream>
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
        void operator = (BigInteger other);
        bool operator == (BigInteger other);
        bool operator < (BigInteger other);
    private:
        bool equals(BigInteger int1, BigInteger int2);
        bool lessThan(BigInteger int1, BigInteger int2);
};

int main() {
    BigInteger int1("781231231612");
    BigInteger int2("51371232131741254");
    cout << int1.getInteger() << " " << int1.getSign() << "\n";
    cout << int2.getInteger() << " " << int2.getSign() << "\n";
    cout << (int1 < int2);
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




//private functions
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
            }
        }
    }else { 
        lessThan = int1.getInteger().length() < int2.getInteger().length();
    }
    return (int1.getSign()) ? !lessThan : lessThan;
}





