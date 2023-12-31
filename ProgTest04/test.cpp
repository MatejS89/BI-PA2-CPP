#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
#endif /* __PROGTEST__ */

//--- Classes and declarations of methods ----------------------------------------------------------------------------//
//**----------------------------------------------------------------------------------------------------------------**//
//*-- CString class -------------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

class CString {
public:
    CString();

    CString(const char *src);

    CString(const CString &src);

    CString &operator=(CString other);

    ~CString();

    bool operator==(const CString &right) const;

    friend ostream &operator<<(ostream &os, const CString &src);

private:
    size_t m_Len;
    size_t m_Max;
    char *m_Data;
};
//*------------------------------------------------------------------------------------------------------------------*//
//*-- CVector class -------------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Uses a template to create a vector of different datatypes
template<typename T>
class CVector {
public:
    CVector();

    CVector &operator=(const CVector<T> &other);

    ~CVector();

    const T &operator[](size_t idx) const;

    T &operator[](size_t idx);

    void pushBack(const T &src);

    size_t size() const;

private:
    T *m_Data;
    size_t m_Size;
    size_t m_Cap;
};

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMail class ---------------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

class CMail {
public:
    CMail();

    CMail(const char *from,
          const char *to,
          const char *body);

    CMail(const CMail &other);

    ~CMail();

    bool operator==(const CMail &x) const;

    friend ostream &operator<<(ostream &os,
                               const CMail &m);

private:
    CString m_From, m_To, m_Body;

    friend class CMailBox;

    friend class CMailServer;

    friend class CMailIterator;
};

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailBox class ------------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

class CMailBox {
public:
    CMailBox();

    CMailBox(const CString &mail);

    CMailBox(const CMailBox &other);

    CMailBox &operator=(const CMailBox &other);

    ~CMailBox();

    bool addToInbox(const CMail &mail);

    bool addToOutbox(const CMail &mail);

private:
    CString m_Email;
    CVector<CMail> m_Inbox;
    CVector<CMail> m_Outbox;

    friend class CMailServer;
};

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailIterator class -------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

class CMailIterator {
public:
    CMailIterator();

    ~CMailIterator();

    explicit operator bool() const;

    bool operator!() const;

    const CMail &operator*() const;

    CMailIterator &operator++();

private:
    CMail *m_Ptr;
    size_t m_Pos;
    CVector<CMail> m_MailVector;

    void fillMailVector(const CVector<CMail> &src);

    friend class CMailServer;
};

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailServer class ---------------------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

class CMailServer {
public:
    CMailServer();

    CMailServer(const CMailServer &src);

    CMailServer &operator=(const CMailServer &src);

    ~CMailServer();

    void sendMail(const CMail &m);

    CMailIterator outbox(const char *needle) const;

    CMailIterator inbox(const char *needle) const;

private:
    CVector<CMailBox> m_MailBoxVector;
};
//*------------------------------------------------------------------------------------------------------------------*//

//**----------------------------------------------------------------------------------------------------------------**//
//--- Methods definitions --------------------------------------------------------------------------------------------//
//**----------------------------------------------------------------------------------------------------------------**//

//*-- CString class methods definitions -----------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Creates new instance of a string, the string is empty
CString::CString() : m_Len(0), m_Max(1), m_Data(new char[m_Max]) {
    m_Data[0] = '\0';
}

//--------------------------------------------------------------------------------------------------------------------//

CString::CString(const char *src) : m_Len(strlen(src)),
                                    m_Max(m_Len + 1),
                                    m_Data(new char[m_Max]) {
    memcpy(m_Data, src, m_Max);
}

//--------------------------------------------------------------------------------------------------------------------//

CString::CString(const CString &src) : m_Len(src.m_Len),
                                       m_Max(src.m_Max),
                                       m_Data(new char[m_Max]) {
    memcpy(m_Data, src.m_Data, m_Max);
}

//--------------------------------------------------------------------------------------------------------------------//

CString &CString::operator=(CString other) {
    m_Max = other.m_Max;
    m_Len = other.m_Len;
    swap(m_Data, other.m_Data);
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------//

CString::~CString() {
    delete[] m_Data;
}

//--------------------------------------------------------------------------------------------------------------------//

bool CString::operator==(const CString &right) const {
    return strcmp(m_Data, right.m_Data) == 0;
}

//--------------------------------------------------------------------------------------------------------------------//

ostream &operator<<(ostream &os, const CString &src) {
    os << src.m_Data;
    return os;
}

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CVector class methods definitions -----------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Creates instance of a CVector, only allocates space for 1 element
template<typename T>
CVector<T>::CVector() : m_Size(0), m_Cap(1) {
    m_Data = (new T[m_Cap]);
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename T>
CVector<T>::~CVector() {
    delete[] m_Data;
}

//--------------------------------------------------------------------------------------------------------------------//

// Creates a deep copy of a given vector
// Allocates the same capacity as source vector, creates a copy of each element in the source vector
// Operator = must be overloaded for each datatype we plan to store in this vector
template<typename T>
CVector<T> &CVector<T>::operator=(const CVector<T> &other) {
    if (this != &other) {
        m_Size = other.m_Size;
        m_Cap = other.m_Cap;
        delete[] m_Data;
        m_Data = new T[m_Cap];
        for (size_t i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];
    }
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename T>
const T &CVector<T>::operator[](size_t idx) const {
    return m_Data[idx];
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename T>
T &CVector<T>::operator[](size_t idx) {
    return m_Data[idx];
}

//--------------------------------------------------------------------------------------------------------------------//

// Reallocates the vector and adds the src element at the end
template<typename T>
void CVector<T>::pushBack(const T &src) {
    if (m_Size >= m_Cap) {
        m_Cap += 2;
        m_Cap *= 2;
        T *tmp = new T[m_Cap];
        for (size_t i = 0; i < m_Size; i++) {
            tmp[i] = m_Data[i];
        }
        delete[] m_Data;
        m_Data = tmp;
    }
    m_Data[m_Size++] = src;
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename T>
size_t CVector<T>::size() const {
    return m_Size;
}

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMail class methods definitions -------------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Creates instance which has 3 empty strings as members ( see non-parametric constructor of CString class )
CMail::CMail() : m_From(), m_To(), m_Body() {}

//--------------------------------------------------------------------------------------------------------------------//

// Creates instance of CMail from 3 standard strings
CMail::CMail(const char *from, const char *to, const char *body) : m_From(from),
                                                                   m_To(to),
                                                                   m_Body(body) {}

//--------------------------------------------------------------------------------------------------------------------//

CMail::CMail(const CMail &other) :
        m_From(other.m_From),
        m_To(other.m_To),
        m_Body(other.m_Body) {}

//--------------------------------------------------------------------------------------------------------------------//

CMail::~CMail() = default;

//--------------------------------------------------------------------------------------------------------------------//

// Uses overloaded operator == from CString method to compare strings
bool CMail::operator==(const CMail &x) const {
    return (m_From == x.m_From
            && m_To == x.m_To
            && m_Body == x.m_Body);
}

//--------------------------------------------------------------------------------------------------------------------//

ostream &operator<<(ostream &os, const CMail &m) {
    os << "From: " << m.m_From << ", To: " << m.m_To << ", Body: " << m.m_Body;
    return os;
}

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailBox class methods definitions ----------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Uses non-parametric constructor of CString method
CMailBox::CMailBox() : m_Email(), m_Inbox(), m_Outbox() {}

//--------------------------------------------------------------------------------------------------------------------//

CMailBox::CMailBox(const CString &mail) : m_Email(mail) {}

//--------------------------------------------------------------------------------------------------------------------//

CMailBox::CMailBox(const CMailBox &other) : m_Email(other.m_Email),
                                            m_Inbox(other.m_Inbox),
                                            m_Outbox(other.m_Outbox) {}

//--------------------------------------------------------------------------------------------------------------------//

CMailBox &CMailBox::operator=(const CMailBox &other) {
    if (this != &other) {
        m_Email = other.m_Email;
        m_Inbox = other.m_Inbox;
        m_Outbox = other.m_Outbox;
    }
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------//

CMailBox::~CMailBox() = default;

//--------------------------------------------------------------------------------------------------------------------//

// Tries to add desired mail into an inbox, returns true on success, false on fail
bool CMailBox::addToInbox(const CMail &mail) {
    if (mail.m_To == m_Email) {
        m_Inbox.pushBack(mail);
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------------------------//

// Tries to add desired mail into an outbox, returns true on success, false on fail
bool CMailBox::addToOutbox(const CMail &mail) {
    if (mail.m_From == m_Email) {
        m_Outbox.pushBack(mail);
        return true;
    }
    return false;
}

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailIterator class methods definitions -----------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

CMailIterator::CMailIterator() : m_Ptr(nullptr), m_Pos(0), m_MailVector() {}

//--------------------------------------------------------------------------------------------------------------------//

CMailIterator::~CMailIterator() = default;

//--------------------------------------------------------------------------------------------------------------------//

const CMail &CMailIterator::operator*() const {
    return *m_Ptr;
}

//--------------------------------------------------------------------------------------------------------------------//

// Checks if the element m_Ptr is not out of range of the vector
// if the incremented element is out of range, sets m_Ptr to nullptr
// if the incremented element isn't out of range, sets m_Ptr to incremented element
CMailIterator &CMailIterator::operator++() {
    if (++m_Pos >= m_MailVector.size())
        m_Ptr = nullptr;
    else
        ++m_Ptr;
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------//

CMailIterator::operator bool() const {
    return m_Ptr != nullptr;
}

//--------------------------------------------------------------------------------------------------------------------//

bool CMailIterator::operator!() const {
    return m_Ptr == nullptr;
}

//--------------------------------------------------------------------------------------------------------------------//

// Creates deep copy of a CMail vector if the src vector isn't empty
// if the src vector is empty, m_Ptr remains nullptr ( see default constructor of CMailIterator )
void CMailIterator::fillMailVector(const CVector<CMail> &src) {
    m_MailVector = src;
    if (src.size() != 0)
        m_Ptr = &m_MailVector[0];
}

//*------------------------------------------------------------------------------------------------------------------*//
//*-- CMailServer class methods definitions -------------------------------------------------------------------------*//
//*------------------------------------------------------------------------------------------------------------------*//

// Uses non-parametric constructor of CVector
CMailServer::CMailServer() : m_MailBoxVector() {}

//--------------------------------------------------------------------------------------------------------------------//

CMailServer::CMailServer(const CMailServer &src) {
    m_MailBoxVector = src.m_MailBoxVector;
}

//--------------------------------------------------------------------------------------------------------------------//

CMailServer &CMailServer::operator=(const CMailServer &src) {
    if (this != &src) {
        m_MailBoxVector = src.m_MailBoxVector;
    }
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------//

CMailServer::~CMailServer() = default;

//--------------------------------------------------------------------------------------------------------------------//

// Method assigns the m CMail to appropriate inbox and outbox
// If there isn't a record of recipient or sender present in the m_MailBoxVector
// creates a new CMailBox with appropriate m_Email name
void CMailServer::sendMail(const CMail &m) {
    bool senderFound = false, recipientFound = false;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        if (m_MailBoxVector[i].addToOutbox(m))
            senderFound = true;
        if (m_MailBoxVector[i].addToInbox(m))
            recipientFound = true;
        if (senderFound && recipientFound)
            return;
    }

    if (!recipientFound) {
        CMailBox tmp(m.m_To);
        tmp.addToInbox(m);
        // Check for same name of sender( m_From ) and recipient ( m_To )
        if (m.m_To == m.m_From) {
            tmp.addToOutbox(m);
            m_MailBoxVector.pushBack(tmp);
            return;
        }
        m_MailBoxVector.pushBack(tmp);
    }

    if (!senderFound) {
        CMailBox tmp(m.m_From);
        tmp.addToOutbox(m);
        m_MailBoxVector.pushBack(tmp);
    }
}

//--------------------------------------------------------------------------------------------------------------------//

// Searches m_MailBoxVector, finds a matching m_Email name,
// if the desired name ( needle ) is present in the vector,
// creates a hard copy of the outbox CMail vector into an instance of CMailIterator
// ( see fillMailVector method )
CMailIterator CMailServer::outbox(const char *needle) const {
    CMailIterator tmp;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        const CString &currMail = m_MailBoxVector[i].m_Email;
        if (currMail == needle) {
            const CMailBox &currMailBox = m_MailBoxVector[i];
            tmp.fillMailVector(currMailBox.m_Outbox);
            break;
        }
    }
    return tmp;
}

//--------------------------------------------------------------------------------------------------------------------//

// Searches m_MailBoxVector, finds a matching m_Email name,
// if the desired name ( needle ) is present in the vector,
// creates a hard copy of the inbox CMail vector into an instance of CMailIterator
// ( see fillMailVector method )
CMailIterator CMailServer::inbox(const char *needle) const {
    CMailIterator tmp;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        const CString &currMail = m_MailBoxVector[i].m_Email;
        if (currMail == needle) {
            const CMailBox &currMailBox = m_MailBoxVector[i];
            tmp.fillMailVector(currMailBox.m_Inbox);
            break;
        }
    }
    return tmp;
}

//*------------------------------------------------------------------------------------------------------------------*//
//**----------------------------------------------------------------------------------------------------------------**//

#ifndef __PROGTEST__

bool matchOutput(const CMail &m,
                 const char *str) {
    ostringstream oss;
    oss << m;
    return oss.str() == str;
}

int main(void) {
    char from[100], to[100], body[1024];

    assert (CMail("john", "peter", "progtest deadline") == CMail("john", "peter", "progtest deadline"));
    assert (!(CMail("john", "peter", "progtest deadline") == CMail("john", "progtest deadline", "peter")));
    assert (!(CMail("john", "peter", "progtest deadline") == CMail("peter", "john", "progtest deadline")));
    assert (!(CMail("john", "peter", "progtest deadline") == CMail("peter", "progtest deadline", "john")));
    assert (!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "john", "peter")));
    assert (!(CMail("john", "peter", "progtest deadline") == CMail("progtest deadline", "peter", "john")));
    CMailServer s0;
    s0.sendMail(CMail("john", "peter", "some important mail"));
    strncpy(from, "john", sizeof(from));
    strncpy(to, "thomas", sizeof(to));
    strncpy(body, "another important mail", sizeof(body));
    s0.sendMail(CMail(from, to, body));
    strncpy(from, "john", sizeof(from));
    strncpy(to, "alice", sizeof(to));
    strncpy(body, "deadline notice", sizeof(body));
    s0.sendMail(CMail(from, to, body));
    s0.sendMail(CMail("alice", "john", "deadline confirmation"));
    s0.sendMail(CMail("peter", "alice", "PR bullshit"));
    CMailIterator i0 = s0.inbox("alice");
//    cout << *i0;
    assert (i0 && *i0 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
    assert (++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
    assert (!++i0);

    CMailIterator i1 = s0.inbox("john");
    assert (i1 && *i1 == CMail("alice", "john", "deadline confirmation"));
    assert (matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
    assert (!++i1);

    CMailIterator i2 = s0.outbox("john");
    assert (i2 && *i2 == CMail("john", "peter", "some important mail"));
    assert (matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
    assert (++i2 && *i2 == CMail("john", "thomas", "another important mail"));
    assert (matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
    assert (++i2 && *i2 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
    assert (!++i2);

    CMailIterator i3 = s0.outbox("thomas");
    assert (!i3);

    CMailIterator i4 = s0.outbox("steve");
    assert (!i4);

    CMailIterator i5 = s0.outbox("thomas");
    s0.sendMail(CMail("thomas", "boss", "daily report"));
    assert (!i5);

    CMailIterator i6 = s0.outbox("thomas");
    assert (i6 && *i6 == CMail("thomas", "boss", "daily report"));
    assert (matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
    assert (!++i6);

    CMailIterator i7 = s0.inbox("alice");
    s0.sendMail(CMail("thomas", "alice", "meeting details"));
    assert (i7 && *i7 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
    assert (++i7 && *i7 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i7, "From: peter, To: alice, Body: PR bullshit"));
    assert (!++i7);

    CMailIterator i8 = s0.inbox("alice");
    assert (i8 && *i8 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
    assert (++i8 && *i8 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i8, "From: peter, To: alice, Body: PR bullshit"));
    assert (++i8 && *i8 == CMail("thomas", "alice", "meeting details"));
    assert (matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
    assert (!++i8);

    CMailServer s1(s0);
    s0.sendMail(CMail("joe", "alice", "delivery details"));
    s1.sendMail(CMail("sam", "alice", "order confirmation"));
    CMailIterator i9 = s0.inbox("alice");
    assert (i9 && *i9 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
    assert (++i9 && *i9 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i9, "From: peter, To: alice, Body: PR bullshit"));
    assert (++i9 && *i9 == CMail("thomas", "alice", "meeting details"));
    assert (matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
    assert (++i9 && *i9 == CMail("joe", "alice", "delivery details"));
    assert (matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
    assert (!++i9);

    CMailIterator i10 = s1.inbox("alice");
    assert (i10 && *i10 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
    assert (++i10 && *i10 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i10, "From: peter, To: alice, Body: PR bullshit"));
    assert (++i10 && *i10 == CMail("thomas", "alice", "meeting details"));
    assert (matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
    assert (++i10 && *i10 == CMail("sam", "alice", "order confirmation"));
    assert (matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
    assert (!++i10);

    CMailServer s2;
    s2.sendMail(CMail("alice", "alice", "mailbox test"));
    CMailIterator i11 = s2.inbox("alice");
    assert (i11 && *i11 == CMail("alice", "alice", "mailbox test"));
    assert (matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
    assert (!++i11);

    s2 = s0;
    s0.sendMail(CMail("steve", "alice", "newsletter"));
    s2.sendMail(CMail("paul", "alice", "invalid invoice"));
    CMailIterator i12 = s0.inbox("alice");
    assert (i12 && *i12 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
    assert (++i12 && *i12 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i12, "From: peter, To: alice, Body: PR bullshit"));
    assert (++i12 && *i12 == CMail("thomas", "alice", "meeting details"));
    assert (matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
    assert (++i12 && *i12 == CMail("joe", "alice", "delivery details"));
    assert (matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
    assert (++i12 && *i12 == CMail("steve", "alice", "newsletter"));
    assert (matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
    assert (!++i12);

    CMailIterator i13 = s2.inbox("alice");
    assert (i13 && *i13 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
    assert (++i13 && *i13 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i13, "From: peter, To: alice, Body: PR bullshit"));
    assert (++i13 && *i13 == CMail("thomas", "alice", "meeting details"));
    assert (matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
    assert (++i13 && *i13 == CMail("joe", "alice", "delivery details"));
    assert (matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
    assert (++i13 && *i13 == CMail("paul", "alice", "invalid invoice"));
    assert (matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
    assert (!++i13);

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
