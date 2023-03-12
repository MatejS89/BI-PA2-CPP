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
#include <sstream>


using namespace std;
#endif /* __PROGTEST__ */

class fibonacci {
private:
    vector<int> seq;
    string converted;

    void extendFib(const int num) {
        size_t i = seq.size();
        while (num >= seq.back()) {
            seq.push_back(seq[i - 1] + seq[i - 2]);
            i++;
        }
//        cout << "FIB" << endl;
//        for (const auto &item: seq) {
//            cout << item << endl;
//        }
        cout << endl;
    }

    size_t findIndexInSeq(const int num) {
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

    void fillZeroes() {
        size_t len = converted.length();
        size_t n = len % 8;
        if (n == 0)
            return;
        converted.insert(len, n, '0');
    }


public:
    fibonacci() {
        seq.push_back(1);
        seq.push_back(2);
    }

    bool convertToFib(int num) {
        extendFib(num);
        size_t i = findIndexInSeq(num);
        string conv;
        while (true) {
            if (seq[i] <= num) {
                num -= seq[i];
                conv += "1";
            } else {
                conv += "0";
            }
            if (i == 0)
                break;
            i--;
        }

        conv.insert(0, 1, '1');
//        reverseString(conv);
//        cout << conv << endl;
        converted.append(conv);
//        fillZeroes();
        cout << converted;

        return true;
    }

    bool hexDump(const string &out) {
        ofstream ofs;
        ofs.open(out, ios::ate | ios::binary);
        if (ofs.fail())
            return false;
        fillZeroes();
        for (const auto &item: converted) {
            int dec = stoi(item, nullptr, 2);
            ofs << hex << dec << endl;
        }
        return true;
    }

//    void printArr() {
//        for (const auto &item: converted) {
//            cout << "ARRR:" << item << endl;
//        }
//    }
};

bool utf8ToFibonacci(const char *inFile,
                     const char *outFile) {
    ifstream ifs;
    ifs.open(inFile, ios::binary);

    if (ifs.fail())
        return false;
    fibonacci fib;
    char c;
    string comb;
    while (ifs.get(c)) {
        int num = int(c);
        num++;
//        cout << num << endl;
        fib.convertToFib(num);
    }

//    if (!(fib.hexDump(outFile)))
//        return false;
//    fib.printArr();
    return true;
}

bool fibonacciToUtf8(const char *inFile,
                     const char *outFile) {
    cout << "FIB TO HEX" << endl;
    ifstream ifs;
    ifs.open(inFile, ios::binary);
    char c;

    while (ifs.get(c)) {
        int num = int(c);
        cout << num << endl;
    }

    return true;
}

#ifndef __PROGTEST__

bool identicalFiles(const char *file1,
                    const char *file2) {
    ifstream fs1, fs2;
    fs1.open(file1, ios::binary | ios::ate);
    fs2.open(file1, ios::binary | ios::ate);

    if (fs1.fail() || fs2.fail())
        return false;

    if (fs1.tellg() != fs2.tellg())
        return false;

    fs1.seekg(0);
    fs2.seekg(0);

    return true;
}

int main(int argc, char *argv[]) {
    utf8ToFibonacci("example/src_0.utf8", "output.fib");
//    utf8ToFibonacci("example/src_1.utf8", "output.fib");
//    utf8ToFibonacci("example/src_11.fib", "output.fib");
//    utf8ToFibonacci("example/dst_0.fib", "output.fib");
//    assert (utf8ToFibonacci("example/src_0.utf8", "output.fib")
//            && identicalFiles("output.fib", "example/dst_0.fib"));
//    assert (utf8ToFibonacci("example/src_1.utf8", "output.fib")
//            && identicalFiles("output.fib", "example/dst_1.fib"));
//    assert (utf8ToFibonacci("example/src_2.utf8", "output.fib")
//            && identicalFiles("output.fib", "example/dst_2.fib"));
//    assert (utf8ToFibonacci("example/src_3.utf8", "output.fib")
//            && identicalFiles("output.fib", "example/dst_3.fib"));
//    assert (utf8ToFibonacci("example/src_4.utf8", "output.fib")
//            && identicalFiles("output.fib", "example/dst_4.fib"));
//    assert (!utf8ToFibonacci("example/src_5.utf8", "output.fib"));
//    assert (fibonacciToUtf8("example/src_6.fib", "output.utf8")
//            && identicalFiles("output.utf8", "example/dst_6.utf8"));
//    assert (fibonacciToUtf8("example/src_7.fib", "output.utf8")
//            && identicalFiles("output.utf8", "example/dst_7.utf8"));
//    assert (fibonacciToUtf8("example/src_8.fib", "output.utf8")
//            && identicalFiles("output.utf8", "example/dst_8.utf8"));
//    assert (fibonacciToUtf8("example/src_9.fib", "output.utf8")
//            && identicalFiles("output.utf8", "example/dst_9.utf8"));
//    assert (fibonacciToUtf8("example/src_10.fib", "output.utf8")
//            && identicalFiles("output.utf8", "example/dst_10.utf8"));
//    assert (!fibonacciToUtf8("example/src_11.fib", "output.utf8"));

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
