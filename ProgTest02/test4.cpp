#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CPerson {
public:
    CPerson(const string &name, const string &surname, const string &email = "", const unsigned int &salary = 0) :
            mName(name),
            mSurname(surname),
            mEmail(email),
            mSalary(salary) {};

    string mName;
    string mSurname;
    string mEmail;
    unsigned int mSalary;
};

class CPersonalAgenda {
public:
    CPersonalAgenda(void) {}

    ~CPersonalAgenda(void) {
        mVectorByName.clear();
        mVectorByEmail.clear();
    }

    bool add(const string &name,
             const string &surname,
             const string &email,
             unsigned int salary) {
        CPerson person = CPerson(name, surname, email, salary);

        if (mVectorByName.empty() && mVectorByName.empty()) {
            mVectorByName.push_back(person);
            mVectorByEmail.push_back(person);
            return true;
        }

        if (!addToNameVector(person))
            return false;

        if (!addToEmailVector(person))
            return false;

        return true;
    }

//    void printNameVector() const {
//        cout << "/////////////NAME////////////////" << endl;
//        for (const auto &item: mVectorByName) {
//            cout << item.mName << " " << item.mSurname << " " << item.mEmail << " " << item.mSalary << endl;
//        }
//        cout << "////////////////////////" << endl;
//        cout << endl;
//    }
//
//    void printEmailVector() const {
//        cout << "/////////////EMAIL////////////////" << endl;
//        for (const auto &item: mVectorByEmail) {
//            cout << item.mName << " " << item.mSurname << " " << item.mEmail << " " << item.mSalary << endl;
//        }
//        cout << "////////////////////////" << endl;
//        cout << endl;
//    }


    bool del(const string &name,
             const string &surname) {
        CPerson person(name, surname, "");
        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        if (namePos == mVectorByName.end() || (namePos->mName != name && namePos->mSurname != surname))
            return false;
        person.mEmail = namePos->mEmail;

        mVectorByName.erase(namePos);
        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        mVectorByEmail.erase(emailPos);
        return true;
    }

    bool del(const string &email) {
        CPerson person("", "", email);
        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        if (emailPos == mVectorByEmail.end() || emailPos->mEmail != email)
            return false;

        person.mName = emailPos->mName;
        person.mSurname = emailPos->mSurname;

        mVectorByEmail.erase(emailPos);

        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        mVectorByName.erase(namePos);
        return true;
    }

    bool changeName(const string &email,
                    const string &newName,
                    const string &newSurname) {
        CPerson person(newName, newSurname, email);

        std::vector<CPerson>::iterator emailPos;
        if (!checkIfEmailExists(person, emailPos))
            return false;

        std::vector<CPerson>::iterator namePos;
        if (checkIfNameExists(person, namePos))
            return false;

        person.mName = emailPos->mName;
        person.mSurname = emailPos->mSurname;
        person.mSalary = emailPos->mSalary;

        emailPos->mName = newName;
        emailPos->mSurname = newSurname;

        namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        mVectorByName.erase(namePos);

        person.mName = newName;
        person.mSurname = newSurname;

        if (!addToNameVector(person))
            return false;
        return true;
    }

    bool changeEmail(const string &name,
                     const string &surname,
                     const string &newEmail) {
        CPerson person(name, surname, newEmail);

        std::vector<CPerson>::iterator emailPos;
        if (checkIfEmailExists(person, emailPos))
            return false;

        std::vector<CPerson>::iterator namePos;
        if (!checkIfNameExists(person, namePos))
            return false;

        person.mEmail = namePos->mEmail;
        person.mSalary = namePos->mSalary;
        namePos->mEmail = newEmail;

        emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        mVectorByEmail.erase(emailPos);

        person.mEmail = newEmail;

        if (!addToEmailVector(person))
            return false;
        return true;
    }

    bool setSalary(const string &name,
                   const string &surname,
                   unsigned int salary) {
        CPerson person(name, surname, "");
        std::vector<CPerson>::iterator namePos;
        if (!checkIfNameExists(person, namePos))
            return false;
        namePos->mSalary = salary;
        person.mEmail = namePos->mEmail;

        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        emailPos->mSalary = salary;
        return true;
    }

    bool setSalary(const string &email,
                   unsigned int salary) {
        CPerson person("", "", email);
        std::vector<CPerson>::iterator emailPos;
        if (!checkIfEmailExists(person, emailPos))
            return false;
        emailPos->mSalary = salary;
        person.mName = emailPos->mName;
        person.mSurname = emailPos->mSurname;
        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        namePos->mSalary = salary;
        return true;
    }


    unsigned int getSalary(const string &name,
                           const string &surname) const {
        CPerson person(name, surname);
        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        if (namePos == mVectorByName.end() || (namePos->mName != name || namePos->mSurname != surname))
            return 0;
        return namePos->mSalary;
    }

    unsigned int getSalary(const string &email) const {
        CPerson person("", "", email);
        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        if (emailPos == mVectorByEmail.end() || emailPos->mEmail != email)
            return 0;
        return emailPos->mSalary;
    }


    bool getRank(const string &name,
                 const string &surname,
                 int &rankMin,
                 int &rankMax) const {
        CPerson person(name, surname);

        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);

        if (namePos == mVectorByName.end() || !(namePos->mName == name && namePos->mSurname == surname))
            return false;

        unsigned int val = namePos->mSalary;
        findBounds(rankMin, rankMax, val);
        return true;
    }


    bool getRank(const string &email,
                 int &rankMin,
                 int &rankMax) const {
        CPerson person("", "", email);

        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        if (emailPos == mVectorByEmail.end() || emailPos->mEmail != email)
            return false;

        unsigned int val = emailPos->mSalary;

        findBounds(rankMin, rankMax, val);
        return true;
    }

    bool getFirst(string &outName,
                  string &outSurname) const {
        if (mVectorByName.empty())
            return false;
        outName = mVectorByName.begin()->mName;
        outSurname = mVectorByName.begin()->mSurname;
        return true;
    }


    bool getNext(const string &name,
                 const string &surname,
                 string &outName,
                 string &outSurname) const {
        CPerson person(name, surname);
        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        namePos += 1;
        if (namePos == mVectorByName.end())
            return false;
        outSurname = namePos->mSurname;
        outName = namePos->mName;
        return true;
    }

private:
    void findBounds(int &rankMin, int &rankMax, const unsigned int val) const {
        rankMin = 0;
        rankMax = 0;

        for (const auto &item: mVectorByName) {
            if (item.mSalary < val)
                ++rankMin;
            else if (item.mSalary == val)
                ++rankMax;
        }
        rankMax += rankMin - 1;
    }

    static bool cmpName(const CPerson &left, const CPerson &right) {
        if (left.mSurname == right.mSurname) {
            return left.mName < right.mName;
        }
        return left.mSurname < right.mSurname;
    }

    static bool cmpEmail(const CPerson &left, const CPerson &right) {
        return left.mEmail < right.mEmail;
    }

    bool addToNameVector(const CPerson &person) {
        auto namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        if (namePos == mVectorByName.end())
            mVectorByName.push_back(person);
        else if ((namePos->mSurname == person.mSurname) && (namePos->mName == person.mName))
            return false;
        else
            mVectorByName.insert(namePos, person);
        return true;
    }

    bool addToEmailVector(const CPerson &person) {
        auto emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        if (emailPos == mVectorByEmail.end())
            mVectorByEmail.push_back(person);
        else if (emailPos->mEmail == person.mEmail)
            return false;
        else
            mVectorByEmail.insert(emailPos, person);
        return true;
    }

    bool checkIfEmailExists(const CPerson &person,
                            std::vector<CPerson>::iterator &emailPos) {
        emailPos = lower_bound(mVectorByEmail.begin(), mVectorByEmail.end(), person, cmpEmail);
        if ((emailPos != mVectorByEmail.end()) && (emailPos->mEmail == person.mEmail))
            return true;
        return false;
    }

    bool checkIfNameExists(const CPerson &person, std::vector<CPerson>::iterator &namePos) {
        namePos = lower_bound(mVectorByName.begin(), mVectorByName.end(), person, cmpName);
        if ((namePos != mVectorByName.end()) &&
            (namePos->mName == person.mName && namePos->mSurname == person.mSurname))
            return true;
        return false;
    }

    vector<CPerson> mVectorByName;
    vector<CPerson> mVectorByEmail;
};

#ifndef __PROGTEST__

int main(void) {
    string outName, outSurname;
    int lo, hi;

    CPersonalAgenda b1;
    assert (b1.add("John", "Smith", "john", 30000));
    assert (b1.add("John", "Miller", "johnm", 35000));
    assert (b1.add("Peter", "Smith", "peter", 23000));
    assert (!b1.add("Peter", "Smith", "peter", 23000));
    assert (b1.getFirst(outName, outSurname)
            && outName == "John"
            && outSurname == "Miller");
    assert (b1.getNext("John", "Miller", outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (b1.getNext("John", "Smith", outName, outSurname)
            && outName == "Peter"
            && outSurname == "Smith");
    assert (!b1.getNext("Peter", "Smith", outName, outSurname));
    assert (b1.setSalary("John", "Smith", 32000));
    assert (b1.getSalary("john") == 32000);

    assert (b1.getSalary("John", "Smith") == 32000);
    assert (b1.getRank("John", "Smith", lo, hi)
            && lo == 1
            && hi == 1);
    assert (b1.getRank("john", lo, hi)
            && lo == 1
            && hi == 1);
    assert (b1.getRank("peter", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getRank("johnm", lo, hi)
            && lo == 2
            && hi == 2);
    assert (b1.setSalary("John", "Smith", 35000));
    assert (b1.getSalary("John", "Smith") == 35000);
    assert (b1.getSalary("john") == 35000);
    assert (b1.getRank("John", "Smith", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.getRank("john", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.getRank("peter", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getRank("johnm", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.changeName("peter", "James", "Bond"));
    assert (b1.getSalary("peter") == 23000);
    assert (b1.getSalary("James", "Bond") == 23000);
    assert (b1.getSalary("Peter", "Smith") == 0);
    assert (b1.getFirst(outName, outSurname)
            && outName == "James"
            && outSurname == "Bond");
    assert (b1.getNext("James", "Bond", outName, outSurname)
            && outName == "John"
            && outSurname == "Miller");
    assert (b1.getNext("John", "Miller", outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (!b1.getNext("John", "Smith", outName, outSurname));
    assert (b1.changeEmail("James", "Bond", "james"));
    assert (b1.getSalary("James", "Bond") == 23000);
    assert (b1.getSalary("james") == 23000);
    assert (b1.getSalary("peter") == 0);
    assert (b1.del("james"));
    assert (b1.getRank("john", lo, hi)
            && lo == 0
            && hi == 1);
    assert (b1.del("John", "Miller"));
    assert (b1.getRank("john", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getFirst(outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (!b1.getNext("John", "Smith", outName, outSurname));
    assert (b1.del("john"));
    assert (!b1.getFirst(outName, outSurname));
    assert (b1.add("John", "Smith", "john", 31000));
    assert (b1.add("john", "Smith", "joHn", 31000));
    assert (b1.add("John", "smith", "jOhn", 31000));
    CPersonalAgenda b2;
    assert (!b2.getFirst(outName, outSurname));
    assert (b2.add("James", "Bond", "james", 70000));
    assert (b2.add("James", "Smith", "james2", 30000));
    assert (b2.add("Peter", "Smith", "peter", 40000));
    assert (!b2.add("James", "Bond", "james3", 60000));
    assert (!b2.add("Peter", "Bond", "peter", 50000));
    assert (!b2.changeName("joe", "Joe", "Black"));
    assert (!b2.changeEmail("Joe", "Black", "joe"));
    assert (!b2.setSalary("Joe", "Black", 90000));
    assert (!b2.setSalary("joe", 90000));
    assert (b2.getSalary("Joe", "Black") == 0);
    assert (b2.getSalary("joe") == 0);
    assert (!b2.getRank("Joe", "Black", lo, hi));
    assert (!b2.getRank("joe", lo, hi));
    assert (!b2.changeName("joe", "Joe", "Black"));
    assert (!b2.changeEmail("Joe", "Black", "joe"));
    assert (!b2.del("Joe", "Black"));
    assert (!b2.del("joe"));
    assert (!b2.changeName("james2", "James", "Bond"));
    assert (!b2.changeEmail("Peter", "Smith", "james"));
    assert (!b2.changeName("peter", "Peter", "Smith"));
    assert (!b2.changeEmail("Peter", "Smith", "peter"));
    assert (b2.del("Peter", "Smith"));
    assert (!b2.changeEmail("Peter", "Smith", "peter2"));
    assert (!b2.setSalary("Peter", "Smith", 35000));
    assert (b2.getSalary("Peter", "Smith") == 0);
    assert (!b2.getRank("Peter", "Smith", lo, hi));
    assert (!b2.changeName("peter", "Peter", "Falcon"));
    assert (!b2.setSalary("peter", 37000));
    assert (b2.getSalary("peter") == 0);
    assert (!b2.getRank("peter", lo, hi));
    assert (!b2.del("Peter", "Smith"));
    assert (!b2.del("peter"));
    assert (b2.add("Peter", "Smith", "peter", 40000));
    assert (b2.getSalary("peter") == 40000);

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
