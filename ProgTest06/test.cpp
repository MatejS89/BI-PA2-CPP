#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>

using namespace std;

class CRect {
public:
    CRect(double x,
          double y,
          double w,
          double h)
            : m_X(x),
              m_Y(y),
              m_W(w),
              m_H(h) {
    }

    friend ostream &operator<<(ostream &os,
                               const CRect &x) {
        return os << '(' << x.m_X << ',' << x.m_Y << ',' << x.m_W << ',' << x.m_H << ')';
    }

    double m_X;
    double m_Y;
    double m_W;
    double m_H;
};

#endif /* __PROGTEST__ */

class CElement {
public:
    CElement(int id, const CRect &coords) : m_ElementId(id), m_RelElemCoords(coords), m_AbsElemCoords(
            0, 0, 0, 0) {};

    virtual ostream &printElement(ostream &os) const = 0;

protected:
    int m_ElementId;
    CRect m_RelElemCoords;
    CRect m_AbsElemCoords;

    friend class CWindow;
};

typedef unique_ptr<CElement> APtr;

class CButton : public CElement {
public:
    CButton(int id,
            const CRect &relPos,
            const string &name) : CElement(id, relPos), m_ButtonName(name) {};
//            "+- [1] Button \"Ok\" (70,394,180,48)\n"

    ostream &printElement(ostream &os) const override {
        cout << "+- [" << CElement::m_ElementId << "] Button \"" << m_ButtonName << "\" " << CElement::m_AbsElemCoords
             << "\n";
        return os;
    }

private:
    const string m_ButtonName;
};

class CInput : public CElement {
public:
    CInput(int id,
           const CRect &relPos,
           const string &value) : CElement(id, relPos), m_InputName(value) {};

    CInput &setValue(const string &src) {
        m_InputName = src;
        return *this;
    }

    ostream &printElement(ostream &os) const override {
        cout << "+- [" << CElement::m_ElementId << "] Button \"" << m_InputName << "\" " << CElement::m_AbsElemCoords
             << "\n";
        return os;
    }

    string getValue() const {
        return m_InputName;
    }

private:
    string m_InputName;
};

class CLabel : public CElement {
public:
    CLabel(int id,
           const CRect &relPos,
           const string &label) : CElement(id, relPos), m_LabelName(label) {};

    ostream &printElement(ostream &os) const override {
        cout << "+- [" << CElement::m_ElementId << "] Label \"" << m_LabelName << "\" " << CElement::m_AbsElemCoords
             << "\n";
        return os;
    }

private:
    const string m_LabelName;
};

class CComboBox : public CElement {
public:
    CComboBox(int id,
              const CRect &relPos) : CElement(id, relPos), m_Selected(0) {};
    // add
    // setSelected
    // getSelected
private:
    vector<string> m_Contents;
    size_t m_Selected;
};

class CWindow {
public:
    CWindow(int id,
            const string &title,
            const CRect &absPos) : m_Id(id), m_Title(title), m_AbsPos(absPos) {};

    CWindow &add(CButton src) {
//        src.printElement(cout);
        calculateAbsCoords(src);
        m_MapElements.insert(
                make_pair(src.m_ElementId,
                          make_unique<CButton>(src)));
        return *this;
    }

    CWindow &add(CLabel src) {
        calculateAbsCoords(src);
        m_MapElements.insert(
                make_pair(src.m_ElementId,
                          make_unique<CLabel>(src)));
        return *this;
    }

    CWindow &add(CInput src) {
        calculateAbsCoords(src);
        m_MapElements.insert(
                make_pair(src.m_ElementId,
                          make_unique<CInput>(src)));
        return *this;
    }


    ostream &printWindow(ostream &os) const {
        for (const auto &mapElement: m_MapElements) {
            mapElement.second->printElement(os);
        }
        return os;
    }

    // add
    // search
    // setPosition
private:
    void calculateAbsCoords(CElement &src) {
        src.m_AbsElemCoords.m_X = round(m_AbsPos.m_W * src.m_RelElemCoords.m_X + m_AbsPos.m_X);
        src.m_AbsElemCoords.m_Y = round(m_AbsPos.m_H * src.m_RelElemCoords.m_Y + m_AbsPos.m_Y);
        src.m_AbsElemCoords.m_H = round(m_AbsPos.m_H * src.m_RelElemCoords.m_H);
        src.m_AbsElemCoords.m_W = round(m_AbsPos.m_W * src.m_RelElemCoords.m_W);
    }

    map<int, APtr> m_MapElements;

    int m_Id;
    string m_Title;
    CRect m_AbsPos;
};

// output operators

#ifndef __PROGTEST__

template<typename _T>
string toString(const _T &x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int main(void) {
//    assert (sizeof(CButton) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
//    assert (sizeof(CInput) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
//    assert (sizeof(CLabel) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    CWindow a(0, "Sample window", CRect(10, 10, 600, 480));
    a.add(CButton(1, CRect(0.1, 0.8, 0.3, 0.1), "Ok")).add(CButton(2, CRect(0.6, 0.8, 0.3, 0.1), "Cancel"));
    a.add(CLabel(10, CRect(0.1, 0.1, 0.2, 0.1), "Username:"));
    a.add(CInput(11, CRect(0.4, 0.1, 0.5, 0.1), "chucknorris"));
    a.printWindow(cout);
//    a.add(CComboBox(20, CRect(0.1, 0.3, 0.8, 0.1)).add("Karate").add("Judo").add("Box").add("Progtest"));
//    assert (toString(a) ==
//            "[0] Window \"Sample window\" (10,10,600,480)\n"
//            "+- [1] Button \"Ok\" (70,394,180,48)\n"
//            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//            "+- [10] Label \"Username:\" (70,58,120,48)\n"
//            "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
//            "+- [20] ComboBox (70,154,480,48)\n"
//            "   +->Karate<\n"
//            "   +- Judo\n"
//            "   +- Box\n"
//            "   +- Progtest\n");
//    CWindow b = a;
//    assert (toString(*b.search(20)) ==
//            "[20] ComboBox (70,154,480,48)\n"
//            "+->Karate<\n"
//            "+- Judo\n"
//            "+- Box\n"
//            "+- Progtest\n");
//    assert (dynamic_cast<CComboBox &> ( *b.search(20)).getSelected() == 0);
//    dynamic_cast<CComboBox &> ( *b.search(20)).setSelected(3);
//    assert (dynamic_cast<CInput &> ( *b.search(11)).getValue() == "chucknorris");
//    dynamic_cast<CInput &> ( *b.search(11)).setValue("chucknorris@fit.cvut.cz");
//    b.add(CComboBox(21, CRect(0.1, 0.5, 0.8, 0.1)).add("PA2").add("OSY").add("Both"));
//    assert (toString(b) ==
//            "[0] Window \"Sample window\" (10,10,600,480)\n"
//            "+- [1] Button \"Ok\" (70,394,180,48)\n"
//            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//            "+- [10] Label \"Username:\" (70,58,120,48)\n"
//            "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
//            "+- [20] ComboBox (70,154,480,48)\n"
//            "|  +- Karate\n"
//            "|  +- Judo\n"
//            "|  +- Box\n"
//            "|  +->Progtest<\n"
//            "+- [21] ComboBox (70,250,480,48)\n"
//            "   +->PA2<\n"
//            "   +- OSY\n"
//            "   +- Both\n");
//    assert (toString(a) ==
//            "[0] Window \"Sample window\" (10,10,600,480)\n"
//            "+- [1] Button \"Ok\" (70,394,180,48)\n"
//            "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//            "+- [10] Label \"Username:\" (70,58,120,48)\n"
//            "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
//            "+- [20] ComboBox (70,154,480,48)\n"
//            "   +->Karate<\n"
//            "   +- Judo\n"
//            "   +- Box\n"
//            "   +- Progtest\n");
//    b.setPosition(CRect(20, 30, 640, 520));
//    assert (toString(b) ==
//            "[0] Window \"Sample window\" (20,30,640,520)\n"
//            "+- [1] Button \"Ok\" (84,446,192,52)\n"
//            "+- [2] Button \"Cancel\" (404,446,192,52)\n"
//            "+- [10] Label \"Username:\" (84,82,128,52)\n"
//            "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
//            "+- [20] ComboBox (84,186,512,52)\n"
//            "|  +- Karate\n"
//            "|  +- Judo\n"
//            "|  +- Box\n"
//            "|  +->Progtest<\n"
//            "+- [21] ComboBox (84,290,512,52)\n"
//            "   +->PA2<\n"
//            "   +- OSY\n"
//            "   +- Both\n");
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
