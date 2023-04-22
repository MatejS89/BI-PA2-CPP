#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>

using namespace std;

class CDate {
public:
    //---------------------------------------------------------------------------------------------
    CDate(int y,
          int m,
          int d)
            : m_Year(y),
              m_Month(m),
              m_Day(d) {
    }

    //---------------------------------------------------------------------------------------------
    int compare(const CDate &x) const {
        if (m_Year != x.m_Year)
            return m_Year - x.m_Year;
        if (m_Month != x.m_Month)
            return m_Month - x.m_Month;
        return m_Day - x.m_Day;
    }

    //---------------------------------------------------------------------------------------------
    int year(void) const {
        return m_Year;
    }

    //---------------------------------------------------------------------------------------------
    int month(void) const {
        return m_Month;
    }

    //---------------------------------------------------------------------------------------------
    int day(void) const {
        return m_Day;
    }

    //---------------------------------------------------------------------------------------------
    friend ostream &operator<<(ostream &os,
                               const CDate &x) {
        char oldFill = os.fill();
        return os << setfill('0') << setw(4) << x.m_Year << "-"
                  << setw(2) << static_cast<int> ( x.m_Month ) << "-"
                  << setw(2) << static_cast<int> ( x.m_Day )
                  << setfill(oldFill);
    }
    //---------------------------------------------------------------------------------------------
private:
    int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;
};

#endif /* __PROGTEST__ */

class CCompanyCmp {
public:
    bool operator()(const string &left, const string &right) {
        return trunc(left) < trunc(right);
    }

private:
    string trunc(const string &str) {
        string tmp;
        size_t firstChar = str.find_first_not_of(" \t\n");
        size_t lastChar = str.find_last_not_of(" \t\n");
        for (size_t i = firstChar; i <= lastChar; i++) {
            if (!std::isspace(str[i])) {
                tmp += tolower(str[i]);
            } else if (std::isspace(str[i]) && !std::isspace(str[i + 1])) {
                tmp += str[i];
            }
        }
        return tmp;
    }
};

class CInvoice {
public:
    CInvoice(const CDate &date,
             const string &seller,
             const string &buyer,
             unsigned int amount,
             double vat) : m_Date(date),
                           m_Seller(seller),
                           m_Buyer(buyer),
                           m_Amount(amount),
                           m_Vat(vat) {};

    CDate date(void) const { return m_Date; }

    string buyer(void) const { return m_Buyer; }

    string seller(void) const { return m_Buyer; }

    unsigned int amount(void) const { return m_Amount; }

    double vat(void) const { return m_Vat; }

private:
    CDate m_Date;
    string m_Seller;
    string m_Buyer;
    unsigned int m_Amount;
    double m_Vat;
};

class CSortOpt {
public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;

    CSortOpt(void);

    CSortOpt &addKey(int key,
                     bool ascending = true);

private:
    // todo
};

class CVATRegister {
public:
    CVATRegister(void) {}

    bool registerCompany(const string &name) {
        return m_CompSet.insert(name).second;
    }

    bool addIssued(const CInvoice &x);

    bool addAccepted(const CInvoice &x);

    bool delIssued(const CInvoice &x);

    bool delAccepted(const CInvoice &x);

    list<CInvoice> unmatched(const string &company,
                             const CSortOpt &sortBy) const;

    void printSet(void) const {
        for (const auto &item: m_CompSet)
            cout << item << endl;
    }

private:
    set<string, CCompanyCmp> m_CompSet;
};

#ifndef __PROGTEST__

bool equalLists(const list<CInvoice> &a, const list<CInvoice> &b) {
    // todo
}

int main(void) {
    CVATRegister r;
    assert (r.registerCompany("first Company"));
    assert (r.registerCompany("Second     Company"));
    assert (r.registerCompany("ThirdCompany, Ltd."));
    assert (r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany(" Third  Company,  Ltd.  "));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
//    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
//    assert (!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
//    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
//    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER,
//                                                                                       false).addKey(CSortOpt::BY_DATE,
//                                                                                                     false)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000)
//                               }));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
//                                           CSortOpt::BY_BUYER, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000)
//                               }));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(
//                                           CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
//                                           CSortOpt::BY_BUYER, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000)
//                               }));
//    assert (equalLists(r.unmatched("First Company", CSortOpt()),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000)
//                               }));
//    assert (equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400,
//                                                34.000000)
//                               }));
//    assert (equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)),
//                       list<CInvoice>
//                               {
//                               }));
//    assert (r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
//    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
//    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
//                                           CSortOpt::BY_DATE, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                32.000000)
//                               }));
//    assert (!r.delIssued(CInvoice(CDate(2001, 1, 1), "First Company", "Second Company ", 200, 30)));
//    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "A First Company", "Second Company ", 200, 30)));
//    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Hand", 200, 30)));
//    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 1200, 30)));
//    assert (!r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company", 200, 130)));
//    assert (r.delIssued(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company", 200, 30)));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
//                                           CSortOpt::BY_DATE, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                32.000000)
//                               }));
//    assert (r.delAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
//                                           CSortOpt::BY_DATE, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                32.000000)
//                               }));
//    assert (r.delIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
//    assert (equalLists(r.unmatched("First Company",
//                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
//                                           CSortOpt::BY_DATE, true)),
//                       list<CInvoice>
//                               {
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                20.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                30.000000),
//                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
//                                                32.000000)
//                               }));
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
