#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#endif /* __PROGTEST__ */

class utf2Fib {
private:
    vector<uint32_t> seq;
    string encoded;
    string remainder;
    uint32_t convertedNum;

    void extendFib(const uint32_t num) {
        size_t i = seq.size();
        while (num >= seq.back()) {
            seq.push_back(seq[i - 1] + seq[i - 2]);
            ++i;
        }
    }

    void extendFibToIndex(const size_t index) {
        size_t i = seq.size();
        while (index >= i) {
            seq.push_back(seq[i - 1] + seq[i - 2]);
            ++i;
        }

    }

    size_t findIndexInSeq(uint32_t num) {
        size_t i = 0;
        while (num >= seq[i]) {
            if (seq[i + 1] > num)
                break;
            ++i;
        }
        return i;
    }

    static void reverseString(string &conv) {
        size_t len = conv.length();
        size_t n = len - 1;
        for (size_t j = 0; j < len / 2; ++j) {
            swap(conv[j], conv[n]);
            --n;
        }
    }

    bool hexDump(ofstream &ofs) {
        size_t i = 0;
        while (i < encoded.length()) {
            string subStr = encoded.substr(i, 8);
            reverseString(subStr);
            ofs.put(stoi(subStr, nullptr, 2));
            if (!(ofs.good()))
                return false;
            i += 8;
        }
        return true;
    }

public:
    utf2Fib() {
        seq.push_back(1);
        seq.push_back(2);
    }

    bool encodeToFib(uint32_t num, ofstream &ofs) {
        extendFib(num);
        size_t i = findIndexInSeq(num);
        string conv;

        while (true) {
            if (seq[i] <= num) {
                num -= seq[i];
                conv.insert(0, 1, '1');
            } else {
                conv.insert(0, 1, '0');
            }
            if (i == 0)
                break;
            i--;
        }
        conv += "1";

        encoded += conv;

        if (encoded.length() % 8 == 0) {
            if (!hexDump(ofs))
                return false;
            encoded.clear();
        }
        return true;
    }

    bool checkRemainder(ofstream &ofs) {
        if (!encoded.empty()) {
            if (!hexDump(ofs))
                return false;
        }
        return true;
    }

    bool fib2UTF8(string &binary, ofstream &ofs) {
        reverseString(binary);
        binary = remainder + binary;
        if (binary.length() > 37)
            return false;
        size_t index = 0;
        while ((index = binary.find("11")) != string::npos) {
            string part = binary.substr(0, index + 1);
            if (!processPart(part, ofs))
                return false;
            binary = binary.substr(index + 2, binary.length() - 1);
        }
        remainder = binary;
        return true;
    }

    bool processPart(string &part, ofstream &ofs) {
        size_t len = part.length();
        convertedNum = 0;
        extendFibToIndex(len);
        for (size_t i = 0; i < len; i++) {
            if (part[i] == '1')
                convertedNum += seq[i];
        }
        --convertedNum;
        if (convertedNum < 0 || convertedNum > 0x10ffff)
            return false;
        string bits;
        utf8_to_bits(bits);
        ofs.write(reinterpret_cast<const char *>(bits.data()), bits.size());
        if (!(ofs.good()))
            return false;
        return true;
    }


    void utf8_to_bits(string &bits) {
        if (convertedNum <= 0b01111111) {
            bits += static_cast<uint8_t>(convertedNum);
        } else if (convertedNum <= 0b11111111111) {
            bits += 0b11000000 | (convertedNum >> 6);
            bits += 0b10000000 | (convertedNum & 0b00111111);
        } else if (convertedNum <= 0b1111111111111111) {
            bits += 0b11100000 | (convertedNum >> 12);
            bits += 0b10000000 | ((convertedNum >> 6) & 0b00111111);
            bits += 0b10000000 | (convertedNum & 0b00111111);
        } else if (convertedNum <= 0b111111111111111111111) {
            bits += 0b11110000 | (convertedNum >> 18);
            bits += 0b10000000 | ((convertedNum >> 12) & 0b00111111);
            bits += 0b10000000 | ((convertedNum >> 6) & 0b00111111);
            bits += 0b10000000 | (convertedNum & 0b00111111);
        }
    }

    string convertToBin(uint32_t c) {
        string binaryStr;
        unsigned char byte = c;
        for (int i = 7; i >= 0; i--) {
            if (((byte >> i) & 1) == 1)
                binaryStr += '1';
            else
                binaryStr += '0';
        }
        return binaryStr;
    }
};


bool checkValidUtf8(uint32_t num, int &followingBytes, uint32_t &tmp) {
    if (followingBytes == 0) {
        if ((num & 0b10000000) == 0) {
            tmp = (tmp << 6) + num;
        } else if ((num & 0b11100000) == 0b11000000) {
            num &= 0b00011111;
            followingBytes = 1;
            tmp = (tmp << 6) + num;
        } else if ((num & 0b11110000) == 0b11100000) {
            num &= 0b00001111;
            followingBytes = 2;
            tmp = (tmp << 6) + num;
        } else if ((num & 0b11111000) == 0b11110000) {
            num &= 0b00000111;
            followingBytes = 3;
            tmp = (tmp << 6) + num;
        } else {
            return false;
        }
    } else {
        if ((num & 0b11000000) != 0b10000000) {
            return false;
        }
        num &= 0b01111111;
        tmp = (tmp << 6) + num;
        followingBytes--;
    }
    return true;
}

bool utf8ToFibonacci(const char *inFile,
                     const char *outFile) {
    ifstream ifs(inFile, ios::binary);
    if (!ifs.is_open() || ifs.fail())
        return false;

    ofstream ofs(outFile, ios::binary);
    if (!ofs.is_open() || ofs.fail())
        return false;

    utf2Fib toFib;
    int followingBytes = 0;
    uint32_t tmp = 0;
    char c;

    while (ifs.get(c)) {
        string binaryStr = toFib.convertToBin(c);
        uint32_t num = stoi(binaryStr, 0, 2);
        if (!checkValidUtf8(num, followingBytes, tmp))
            return false;

        if (followingBytes == 0) {
            if (!toFib.encodeToFib(tmp + 1, ofs))
                return false;
            tmp = 0;
        }
    }
    if (followingBytes != 0)
        return false;
    if (!toFib.checkRemainder(ofs))
        return false;

    return true;
}

bool fibonacciToUtf8(const char *inFile,
                     const char *outFile) {
    ifstream ifs(inFile, ios::binary);
    if (!ifs.is_open() || ifs.fail())
        return false;

    ofstream ofs(outFile, ios::binary);
    if (!ofs.is_open() || ofs.fail())
        return false;

    utf2Fib toUtf8;
    string binaryStr;
    char c;

    while (ifs.get(c)) {
        binaryStr = toUtf8.convertToBin(c);
        if (!toUtf8.fib2UTF8(binaryStr, ofs)) {
            return false;
        }
    }

    if (binaryStr.find('1') != string::npos)
        return false;

    return true;
}

#ifndef __PROGTEST__

bool identicalFiles(const char *file1,
                    const char *file2) {
    ifstream fs1, fs2;
    fs1.open(file1, ios::binary | ios::ate);
    fs2.open(file2, ios::binary | ios::ate);

    if (fs1.fail() || fs2.fail())
        return false;

    if (fs1.tellg() != fs2.tellg())
        return false;

    fs1.seekg(0);
    fs2.seekg(0);
    char c1, c2;
    while (fs1.get(c1) && fs2.get(c2))
        if (c1 != c2)
            return false;

    return true;
}

int main(int argc, char *argv[]) {
    assert (utf8ToFibonacci("example/src_0.utf8", "output.fib")
            && identicalFiles("output.fib", "example/dst_0.fib"));
    assert (utf8ToFibonacci("example/src_1.utf8", "output.fib")
            && identicalFiles("output.fib", "example/dst_1.fib"));
    assert (utf8ToFibonacci("example/src_2.utf8", "output.fib")
            && identicalFiles("output.fib", "example/dst_2.fib"));
    assert (utf8ToFibonacci("example/src_3.utf8", "output.fib")
            && identicalFiles("output.fib", "example/dst_3.fib"));
    assert (utf8ToFibonacci("example/src_4.utf8", "output.fib")
            && identicalFiles("output.fib", "example/dst_4.fib"));
    assert (!utf8ToFibonacci("example/src_5.utf8", "output.fib"));
    assert (fibonacciToUtf8("example/src_6.fib", "output.utf8")
            && identicalFiles("output.utf8", "example/dst_6.utf8"));
    assert (fibonacciToUtf8("example/src_7.fib", "output.utf8")
            && identicalFiles("output.utf8", "example/dst_7.utf8"));
    assert (fibonacciToUtf8("example/src_8.fib", "output.utf8")
            && identicalFiles("output.utf8", "example/dst_8.utf8"));
    assert (fibonacciToUtf8("example/src_9.fib", "output.utf8")
            && identicalFiles("output.utf8", "example/dst_9.utf8"));
    assert (fibonacciToUtf8("example/src_10.fib", "output.utf8")
            && identicalFiles("output.utf8", "example/dst_10.utf8"));
    assert (!utf8ToFibonacci("example/in_1331672.bin", "output.fib"));
    assert (!utf8ToFibonacci("example/in_1322558.bin", "output.fib"));
    assert (!utf8ToFibonacci("example/in_1339192.bin", "output.fib"));
    assert (fibonacciToUtf8("example/in_1323330.bin", "output.utf8"));
    assert (!fibonacciToUtf8("example/in_5027244.bin", "output.utf8"));
    assert (fibonacciToUtf8("example/test.fib", "output.utf8"));

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
