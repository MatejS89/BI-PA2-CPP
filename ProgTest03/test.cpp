#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
// #define EXTENDED_SYNTAX

class CRangeList;

class CRange {
public:
    CRange(long long beg, long long end) : m_Beg(beg), m_End(end) {
        if (beg > end)
            throw std::logic_error("e");
    }

    friend CRangeList operator+(const CRange &left, const CRange &right);

    friend CRangeList operator-(const CRange &left, const CRange &right);

private:
    long long m_Beg;
    long long m_End;

    friend class CRangeList;
};

class CRangeList {
public:
    CRangeList &operator+=(const CRange &range) {
        if (m_List.empty()) {
            m_List.push_back(range);
            return *this;
        }

        size_t len = m_List.size();

        for (size_t index = 0; index < len; index++) {
            CRange &item = m_List[index];
            CRange nextItem = item;
            if (len != 1 && index + 1 < len)
                nextItem = m_List[index + 1];
            if (range.m_Beg < item.m_Beg && range.m_End < item.m_End) {
                auto it = m_List.begin() + index;
                m_List.insert(it, range);
                break;
            } else if (overlap(range, item)) {
                if (range.m_Beg < item.m_Beg)
                    item.m_Beg = range.m_Beg;
                if (range.m_End > item.m_End)
                    item.m_End = range.m_End;
                break;
            } else if (range.m_Beg > item.m_End && range.m_Beg < nextItem.m_Beg) {
                auto it = m_List.begin() + index + 1;
                m_List.insert(it, range);
                break;
            } else if (len == index + 1) {
                m_List.push_back(range);
                break;
            }
        }

        compactList();
        return *this;
    }

    CRangeList &operator+=(const CRangeList &other) {
        for (const auto &item: other.m_List) {
            *this += item;
        }
        return *this;
    }

    CRangeList &operator=(const CRange &range) {
        m_List.clear();
        *this += range;
        return *this;
    }

    CRangeList &operator=(const CRangeList &other) {
        m_List.clear();
        for (const auto &item: other.m_List) {
            *this += item;
        }
        return *this;
    }

    CRangeList &operator+(const CRange &range) {
        *this += range;
        return *this;
    }

    CRangeList &operator-=(const CRange &range) {
        size_t len = m_List.size();
        if (len == 0)
            return *this;
        for (size_t i = 0; i < len; i++) {
            CRange &item = m_List[i];
            auto it = m_List.begin() + i;
            // TOTAL OVERLAP
            if (range.m_Beg <= item.m_Beg && range.m_End >= item.m_End) {
                m_List.erase(it);
                --i;
                // INSIDE
            } else if (range.m_Beg > item.m_Beg && range.m_End < item.m_End) {
                CRange tmp(range.m_End + 1, item.m_End);
                item.m_End = range.m_Beg - 1;
                m_List.insert(it + 1, tmp);
                // OVERLAP LEFT
            } else if (range.m_Beg <= item.m_Beg && range.m_End <= item.m_End && range.m_End >= item.m_Beg) {
                item.m_Beg = range.m_End + 1;
                // OVERLAP RIGHT
            } else if (range.m_Beg >= item.m_Beg && range.m_Beg <= item.m_End && range.m_End >= item.m_End)
                item.m_End = range.m_Beg - 1;
            len = m_List.size();
        }
//        compactList();
        return *this;
    }

    CRangeList &operator-=(const CRangeList &other) {
        for (const auto &item: other.m_List) {
            *this -= item;
        }
        return *this;
    }

    CRangeList &operator-(const CRange &other) {
        *this -= other;
        return *this;
    }

    bool operator==(const CRangeList &other) const {
        size_t lenThis = this->m_List.size();
        size_t lenOther = other.m_List.size();

        if (lenThis != lenOther)
            return false;

        for (size_t i = 0; i < lenThis; i++) {
            const CRange &left = this->m_List[i];
            const CRange &right = other.m_List[i];
            if (left.m_Beg != right.m_Beg || left.m_End != right.m_End)
                return false;
        }

        return true;
    }

    bool operator!=(const CRangeList &other) const {
        return !(*this == other);
    }

    bool includes(const long long &num) const {
        for (const auto &item: m_List) {
            if (item.m_Beg <= num && item.m_End >= num)
                return true;
        }
        return false;
    }

    bool includes(const CRange &needle) const {
        for (const auto &item: m_List) {
            if (item.m_Beg <= needle.m_Beg && item.m_End >= needle.m_End)
                return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &os, const CRangeList &list);

    void printList(ostream &os) const {
        if (m_List.size() == 0) {
            os << "{}";
            return;
        }
        size_t idx = m_List.size() - 1;
        os << "{";
        for (size_t i = 0; i < idx; i++) {
            printElement(os, i);
            os << ",";
        }
        printElement(os, idx);
        os << "}";
    }

private:
    vector<CRange> m_List;

    bool overlap(const CRange &left, const CRange &right) const {
        if (right.m_End != LLONG_MAX && right.m_Beg != LLONG_MIN) {
            if (left.m_Beg <= right.m_End + 1 && left.m_End >= right.m_Beg - 1)
                return true;
        } else if (right.m_End == LLONG_MAX) {
            if (left.m_Beg <= right.m_End && left.m_End >= right.m_Beg - 1)
                return true;
        } else if (right.m_Beg == LLONG_MIN) {
            if (left.m_Beg <= right.m_End + 1 && left.m_End >= right.m_Beg)
                return true;
        }
        return false;
    }

    void printElement(ostream &os, const size_t i) const {
        if (m_List[i].m_Beg == m_List[i].m_End)
            os << m_List[i].m_Beg;
        else
            os << "<" << m_List[i].m_Beg << ".." << m_List[i].m_End << ">";
    }

    void compactList() {
        size_t len = m_List.size();
        for (size_t i = 0; i < len - 1; i++) {
            CRange &item = m_List[i];
            CRange nextItem = item;
            if (len != 1)
                nextItem = m_List[i + 1];
            if (overlap(item, nextItem)) {
                auto it = m_List.begin() + i;
                m_List.erase(it + 1);
                if (nextItem.m_End > item.m_End)
                    item.m_End = nextItem.m_End;
                --i;
            }
            len = m_List.size();
        }
    }
};

CRangeList operator+(const CRange &left, const CRange &right) {
    CRangeList tmp;
    tmp += left;
    tmp += right;
    return tmp;
}

CRangeList operator-(const CRange &left, const CRange &right) {
    CRangeList tmp;
    tmp += left;
    tmp -= right;
    return tmp;
}

ostream &operator<<(ostream &os, const CRangeList &list) {
    list.printList(os);
    return os;
}

#ifndef __PROGTEST__

string toString(const CRangeList &x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int main(void) {
    CRangeList a, b;

    assert (sizeof(CRange) <= 2 * sizeof(long long));
    a = CRange(5, 10);
    a += CRange(25, 100);
    assert (toString(a) == "{<5..10>,<25..100>}");
    a += CRange(-5, 0);
    a += CRange(8, 50);
    assert (toString(a) == "{<-5..0>,<5..100>}");
    a += CRange(101, 105) + CRange(120, 150) + CRange(160, 180) + CRange(190, 210);
    assert (toString(a) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}");
    a += CRange(106, 119) + CRange(152, 158);
    assert (toString(a) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}");
    a += CRange(-3, 170);
    a += CRange(-30, 1000);
    assert (toString(a) == "{<-30..1000>}");
    b = CRange(-500, -300) + CRange(2000, 3000) + CRange(700, 1001);
    a += b;
    assert (toString(a) == "{<-500..-300>,<-30..1001>,<2000..3000>}");
    a -= CRange(-400, -400);
    assert (toString(a) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}");
    a -= CRange(10, 20) + CRange(900, 2500) + CRange(30, 40) + CRange(10000, 20000);
    assert (toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
    try {
        a += CRange(15, 18) + CRange(10, 0) + CRange(35, 38);
        assert ("Exception not thrown" == nullptr);
    }
    catch (const std::logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown" == nullptr);
    }
    assert (toString(a) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
    b = a;
    assert (a == b);
    assert (!(a != b));
    b += CRange(2600, 2700);
    assert (toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}");
    assert (a == b);
    assert (!(a != b));
    b += CRange(15, 15);
    assert (toString(b) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}");
    assert (!(a == b));
    assert (a != b);
    assert (b.includes(15));
    assert (b.includes(2900));
    assert (b.includes(CRange(15, 15)));
    assert (b.includes(CRange(-350, -350)));
    assert (b.includes(CRange(100, 200)));
    assert (!b.includes(CRange(800, 900)));
    assert (!b.includes(CRange(-1000, -450)));
    assert (!b.includes(CRange(0, 500)));
    a += CRange(-10000, 10000) + CRange(10000000, 1000000000);
    assert (toString(a) == "{<-10000..10000>,<10000000..1000000000>}");
    b += a;
    assert (toString(b) == "{<-10000..10000>,<10000000..1000000000>}");
    b -= a;
    assert (toString(b) == "{}");
    b += CRange(0, 100) + CRange(200, 300) - CRange(150, 250) + CRange(160, 180) - CRange(170, 170);
    assert (toString(b) == "{<0..100>,<160..169>,<171..180>,<251..300>}");
    b -= CRange(10, 90) - CRange(20, 30) - CRange(40, 50) - CRange(60, 90) + CRange(70, 80);
    assert (toString(b) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}");
#ifdef EXTENDED_SYNTAX
    CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
    assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
    ostringstream oss;
    oss << setfill ( '=' ) << hex << left;
    for ( const auto & v : x + CRange ( -100, -100 ) )
      oss << v << endl;
    oss << setw ( 10 ) << 1024;
    assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
