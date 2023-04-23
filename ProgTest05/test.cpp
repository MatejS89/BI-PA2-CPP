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

class CCompanyCmp {
public:
    bool operator()(const string &left, const string &right) const {
        return trunc(left) < trunc(right);
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

    CInvoice(const string &seller, const string &buyer, const CInvoice &src) : m_Date(src.m_Date),
                                                                               m_Seller(seller),
                                                                               m_Buyer(buyer),
                                                                               m_Amount(src.m_Amount),
                                                                               m_Vat(src.m_Vat) {};

    bool operator==(const CInvoice &other) const {
        return (m_Date.compare(other.m_Date) == 0 &&
                m_Seller == other.m_Seller &&
                m_Buyer == other.m_Buyer &&
                m_Vat == other.m_Vat &&
                m_Amount == other.m_Amount);
    }

    bool operator!=(const CInvoice &other) const {
        return !(*this == other);
    }

    bool operator<(const CInvoice &other) const {
        if (m_Date.compare(other.m_Date) > 0)
            return true;
        else if (m_Date.compare(other.m_Date) < 0)
            return false;

        if (m_Seller < other.m_Seller) {
            return true;
        } else if (m_Seller > other.m_Seller) {
            return false;
        }

        if (m_Buyer < other.m_Buyer) {
            return true;
        } else if (m_Buyer > other.m_Buyer) {
            return false;
        }

        if (m_Amount < other.m_Amount) {
            return true;
        } else if (m_Amount > other.m_Amount) {
            return false;
        }

        return m_Vat < other.m_Vat;
    }

    CDate date(void) const { return m_Date; }

    string buyer(void) const { return m_Buyer; }

    string seller(void) const { return m_Seller; }

    unsigned int amount(void) const { return m_Amount; }

    double vat(void) const { return m_Vat; }

private:
    CDate m_Date;
    string m_Seller;
    string m_Buyer;
    unsigned int m_Amount;
    double m_Vat;

    friend class CVATRegister;

    friend string trunc(const string &str);
};

class CInvoiceCmp {
public:
    bool operator()(const CInvoice &left, const CInvoice &right) const {
        return left < right;
    }
};

class CSortOpt {
public:
    static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;

    CSortOpt(void) {};

    CSortOpt &addKey(int key,
                     bool ascending = true) {
        m_OptionVec.emplace_back(key, ascending);
        return *this;
    }

private:
    struct sortCriteria {
        sortCriteria(const int key, const bool ascending) : key(key), ascending(ascending) {};
        int key;
        bool ascending;
    };

    void sortList(list<CInvoice> &invoiceList) const {
        invoiceList.sort([this](const CInvoice &left, const CInvoice &right) {
            return sortByCriterium(left, right);
        });
    }

    bool sortByCriterium(const CInvoice &left, const CInvoice &right) const {
        for (const auto &criterium: m_OptionVec) {
            bool ascending = criterium.ascending;
            switch (criterium.key) {
                case 0:
                    if (left.date().compare(right.date()) != 0) {
                        if (ascending)
                            return left.date().compare(right.date()) < 0;
                        else
                            return left.date().compare(right.date()) > 0;
                    }
                    break;
                case 1:
                    if (trunc(left.buyer()) != trunc(right.buyer())) {
                        if (ascending)
                            return trunc(left.buyer()) < trunc(right.buyer());
                        else
                            return trunc(left.buyer()) > trunc(right.buyer());
                    }
                    break;
                case 2:
                    if (trunc(left.seller()) != trunc(right.seller())) {
                        if (ascending)
                            return trunc(left.seller()) < trunc(right.seller());
                        else
                            return trunc(left.seller()) > trunc(right.seller());
                    }
                    break;
                case 3:
                    if (left.amount() != right.amount()) {
                        if (ascending)
                            return left.amount() < right.amount();
                        else
                            return left.amount() > right.amount();
                    }
                    break;
                case 4:
                    if (left.vat() != right.vat()) {
                        if (ascending)
                            return left.vat() < right.vat();
                        else
                            return left.vat() < right.vat();
                    }
                    break;
            }
        }
        return false;
    }

    vector<sortCriteria> m_OptionVec;

    friend class CVATRegister;
};

class CVATRegister {
public:
    CVATRegister(void) {};

    bool registerCompany(const string &name) {
        if (!m_CompanySet.insert(name).second)
            return false;
        return true;
    }

    bool addIssued(const CInvoice &x) {
        string str1 = trunc(x.m_Buyer);
        string str2 = trunc(x.m_Seller);
        if (str1 == str2)
            return false;

        auto it1 = m_CompanySet.find(x.seller());
        if (it1 == m_CompanySet.end())
            return false;

        auto it2 = m_CompanySet.find(x.buyer());
        if (it2 == m_CompanySet.end())
            return false;

        CInvoice tmp(it1->data(), it2->data(), x);

        if (!m_IssuedInvoiceSet.insert(tmp).second)
            return false;
        if (m_AcceptedInvoiceSet.find(tmp) == m_AcceptedInvoiceSet.end()) {
            m_UnmatchedInvoiceMap[tmp.m_Seller].push_back(tmp);
            m_UnmatchedInvoiceMap[tmp.m_Buyer].push_back(tmp);
        } else {
            auto it = std::find(m_UnmatchedInvoiceMap[tmp.m_Seller].begin(),
                                m_UnmatchedInvoiceMap[tmp.m_Seller].end(), tmp);
            m_UnmatchedInvoiceMap[tmp.m_Seller].erase(it);
            it = std::find(m_UnmatchedInvoiceMap[tmp.m_Buyer].begin(),
                           m_UnmatchedInvoiceMap[tmp.m_Buyer].end(), tmp);
            m_UnmatchedInvoiceMap[tmp.m_Buyer].erase(it);
        }
        return true;
    }

    bool addAccepted(const CInvoice &x) {
        string str1 = trunc(x.m_Buyer);
        string str2 = trunc(x.m_Seller);
        if (str1 == str2)
            return false;

        auto it1 = m_CompanySet.find(x.seller());
        if (it1 == m_CompanySet.end())
            return false;

        auto it2 = m_CompanySet.find(x.buyer());
        if (it2 == m_CompanySet.end())
            return false;

        CInvoice tmp(it1->data(), it2->data(), x);

        if (!m_AcceptedInvoiceSet.insert(tmp).second)
            return false;
        for (const auto &item: m_IssuedInvoiceSet) {
            if (item == tmp)
                cout << " MATCH ";
        }
        auto found = m_IssuedInvoiceSet.find(tmp);
        if (found == m_IssuedInvoiceSet.end()) {
            m_UnmatchedInvoiceMap[tmp.m_Seller].push_back(tmp);
            m_UnmatchedInvoiceMap[tmp.m_Buyer].push_back(tmp);
        } else {
            auto it = std::find(m_UnmatchedInvoiceMap[tmp.m_Seller].begin(),
                                m_UnmatchedInvoiceMap[tmp.m_Seller].end(), tmp);
            m_UnmatchedInvoiceMap[tmp.m_Seller].erase(it);
            it = std::find(m_UnmatchedInvoiceMap[tmp.m_Buyer].begin(),
                           m_UnmatchedInvoiceMap[tmp.m_Buyer].end(), tmp);
            m_UnmatchedInvoiceMap[tmp.m_Buyer].erase(it);
        }
        return true;
    }

    bool delIssued(const CInvoice &x);

    bool delAccepted(const CInvoice &x);

    list<CInvoice> unmatched(const string &company,
                             const CSortOpt &sortBy) const {
        for (const auto &optionVec: sortBy.m_OptionVec) {
            cout << optionVec.key << "  " << optionVec.ascending << endl;
        }
        auto it = m_UnmatchedInvoiceMap.find(company);
        if (it == m_UnmatchedInvoiceMap.end())
            return list<CInvoice>();
        list<CInvoice> listCInvoice = it->second;
        if (sortBy.m_OptionVec.empty())
            return listCInvoice;
        sortBy.sortList(listCInvoice);

        for (const auto &item: listCInvoice) {
            cout << item.m_Date << "  " << item.m_Seller << "  " << item.m_Buyer << "  " << item.m_Amount << "  "
                 << item.m_Vat << endl;
        }

        return listCInvoice;
    }

private:

    set<string, CCompanyCmp> m_CompanySet;
    set<CInvoice, CInvoiceCmp> m_AcceptedInvoiceSet;
    map<string, list<CInvoice>, CCompanyCmp> m_UnmatchedInvoiceMap;
    set<CInvoice, CInvoiceCmp> m_IssuedInvoiceSet;
};

#ifndef __PROGTEST__

bool equalLists(const list<CInvoice> &a, const list<CInvoice> &b) {
    for (const auto &item: a) {
        if (a != b)
            return false;
    }
    return true;
}

int main(void) {
    CVATRegister r;
    assert (r.registerCompany("first Company"));
    assert (r.registerCompany("Second     Company"));
    assert (r.registerCompany("ThirdCompany, Ltd."));
    assert (r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany("Third Company, Ltd."));
    assert (!r.registerCompany(" Third  Company,  Ltd.  "));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 20)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 2), "FirSt Company", "Second Company ", 200, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 100, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Second Company ", "First Company", 300, 30)));
    assert (r.addIssued(CInvoice(CDate(2000, 1, 1), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 1), "First Company", "Second Company ", 300, 30)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "First Company", "First   Company", 200, 30)));
    assert (!r.addIssued(CInvoice(CDate(2000, 1, 4), "Another Company", "First   Company", 200, 30)));
    r.unmatched("First Company",
                CSortOpt().addKey(CSortOpt::BY_SELLER, true)
                        .addKey(CSortOpt::BY_BUYER, false)
                        .addKey(CSortOpt::BY_DATE, false)
    );
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER,
                                                                                       false).addKey(CSortOpt::BY_DATE,
                                                                                                     false)),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
                                           CSortOpt::BY_BUYER, true)),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_VAT, true).addKey(CSortOpt::BY_AMOUNT, true).addKey(
                                           CSortOpt::BY_DATE, true).addKey(CSortOpt::BY_SELLER, true).addKey(
                                           CSortOpt::BY_BUYER, true)),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("First Company", CSortOpt()),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Third Company, Ltd.", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000)
                               }));
    assert (equalLists(r.unmatched("second company", CSortOpt().addKey(CSortOpt::BY_DATE, false)),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 2), "first Company", "Second     Company", 200,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Third Company, Ltd.", "Second     Company", 400,
                                                34.000000)
                               }));
    assert (equalLists(r.unmatched("last company", CSortOpt().addKey(CSortOpt::BY_VAT, true)),
                       list<CInvoice>
                               {
                               }));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 2), "First Company", "Second Company ", 200, 30)));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "First Company", " Third  Company,  Ltd.   ", 200, 30)));
    assert (r.addAccepted(CInvoice(CDate(2000, 1, 1), "Second company ", "First Company", 300, 32)));
    assert (equalLists(r.unmatched("First Company",
                                   CSortOpt().addKey(CSortOpt::BY_SELLER, true).addKey(CSortOpt::BY_BUYER, true).addKey(
                                           CSortOpt::BY_DATE, true)),
                       list<CInvoice>
                               {
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                20.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 100,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "first Company", "Second     Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                30.000000),
                                       CInvoice(CDate(2000, 1, 1), "Second     Company", "first Company", 300,
                                                32.000000)
                               }));
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
