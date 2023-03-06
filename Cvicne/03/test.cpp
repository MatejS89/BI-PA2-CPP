#ifndef __PROGTEST__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>

using namespace std;
#endif /* __PROGTEST__ */

struct entity {
    string name;
    string surname;
    string num;
};

size_t matchName(const string &name, const vector<entity> &arr, ostream &out) {
    size_t matches = 0;
    for (const auto &i: arr)
        if (name == i.name || name == i.surname) {
//            cout << i.name << " " << i.surname << " " << i.num << endl;
            out << i.name << " " << i.surname << " " << i.num << endl;
            matches++;
        }
    return matches;
}

bool checkNumber(const string &num) {
    if (num.length() != 9 || num[0] == '0')
        return false;
    for (char i: num)
        if (!isdigit(i))
            return false;
    return true;
}

bool report(const string &fileName, ostream &out) {
    vector<entity> arr;
    ifstream ifs;
    ifs.open(fileName, ios::in);
    if (!ifs)
        return false;
    string line;
    while (getline(ifs, line)) {
        if (line.empty())
            break;
        char check;
        entity ent;
        string number;
        istringstream lineFs(line);
        if (!(lineFs >> ent.name >> ent.surname >> number)) {
            return false;
        }
        lineFs >> check;
        if (!lineFs.eof()) {
            ifs.close();
            return false;
        }
        if (!checkNumber(number)) {
            ifs.close();
            return false;
        }
        ent.num = number;
        arr.push_back(ent);
    }
    string needle;
    while (ifs >> needle) {
        size_t cnt = 0;
        cnt += matchName(needle, arr, out);
//        cout << "-> " << cnt << endl;
        out << "-> " << cnt << endl;
    }
    ifs.close();
    return true;
}

#ifndef __PROGTEST__

int main() {
    ostringstream oss;
    oss.str("");
    assert (report("tests/test0_in.txt", oss) == true);
    assert (oss.str() ==
            "John Christescu 258452362\n"
            "John Harmson 861647702\n"
            "-> 2\n"
            "-> 0\n"
            "Josh Dakhov 264112084\n"
            "Dakhov Speechley 865216101\n"
            "-> 2\n"
            "John Harmson 861647702\n"
            "-> 1\n");
    oss.str("");
    assert (report("tests/test4_in.txt", oss) == true);
    assert (oss.str() ==
            "John Christescu 258452362\n"
            "John Harmson 861647702\n"
            "-> 2\n"
            "-> 0\n"
            "Josh Dakhov 264112084\n"
            "Dakhov Speechley 865216101\n"
            "-> 2\n"
            "John Harmson 861647702\n"
            "-> 1\n");
    oss.str("");
    assert (report("tests/test1_in.txt", oss) == false);
    assert (report("tests/test2_in.txt", oss) == false);
    assert (report("tests/test3_in.txt", oss) == false);
    assert (report("tests/test5_in.txt", oss) == false);

    return 0;
}

#endif /* __PROGTEST__ */
