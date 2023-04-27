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
    CElement(int id, const CRect &coords) :
            m_ElementId(id),
            m_RelCoords(coords),
            m_AbsCoords(coords) {};

    virtual unique_ptr<CElement> clone() const {};

protected:
    CRect m_RelCoords;
    CRect m_AbsCoords;
    int m_ElementId;

private:
    void calculateCoords(const CRect &windowCoords) {
        m_AbsCoords.m_X = round(windowCoords.m_W * m_RelCoords.m_X + windowCoords.m_X);
        m_AbsCoords.m_Y = round(windowCoords.m_H * m_RelCoords.m_Y + windowCoords.m_Y);
        m_AbsCoords.m_H = round(windowCoords.m_H * m_RelCoords.m_H);
        m_AbsCoords.m_W = round(windowCoords.m_W * m_RelCoords.m_W);
    }

    friend class CWindow;
};

class CWindow {
public:
    CWindow(int id,
            const string &title,
            const CRect &absPos) :
            m_WindowId(id),
            m_WindowCoords(absPos),
            m_Title(title) {};

    CWindow &add(const CElement &src) {
        unique_ptr<CElement> tmp(src.clone());
        tmp->calculateCoords(m_WindowCoords);
        m_Elements.push_back(move(tmp));
        return *this;
    }
    // add
    // search
    // setPosition
private:


    CRect m_WindowCoords;
    int m_WindowId;
    string m_Title;
    vector<std::unique_ptr<CElement>> m_Elements;
};

class CButton : public CElement {
public:
    CButton(int id,
            const CRect &relPos,
            const string &name) : CElement(id, relPos), m_ButtonName(name) {};

    CButton(const CButton &src) : CElement(src.m_ElementId, src.m_RelCoords),
                                  m_ButtonName(src.m_ButtonName) {};

    unique_ptr<CElement> clone() const override {
        return make_unique<CButton>(*this);
    }

private:
    string m_ButtonName;
};

class CInput {
public:
    CInput(int id,
           const CRect &relPos,
           const string &value);
    // setValue
    // getValue
};

class CLabel {
public:
    CLabel(int id,
           const CRect &relPos,
           const string &label);
};

class CComboBox {
public:
    CComboBox(int id,
              const CRect &relPos);
    // add
    // setSelected
    // getSelected
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
    assert (sizeof(CButton) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    assert (sizeof(CInput) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    assert (sizeof(CLabel) - sizeof(string) < sizeof(CComboBox) - sizeof(vector<string>));
    CWindow a(0, "Sample window", CRect(10, 10, 600, 480));

    a.add(CButton(1, CRect(0.1, 0.8, 0.3, 0.1), "Ok")).add(CButton(2, CRect(0.6, 0.8, 0.3, 0.1), "Cancel"));
    cout << "AHOJ" << endl;
//    a.add(CLabel(10, CRect(0.1, 0.1, 0.2, 0.1), "Username:"));
//    a.add(CInput(11, CRect(0.4, 0.1, 0.5, 0.1), "chucknorris"));
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
