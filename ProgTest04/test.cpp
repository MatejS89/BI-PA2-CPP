#include <ctime>
#include <ostream>

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

class CString {
public:
    CString(const char *src);

    CString();

    ~CString();

    CString(const CString &src);

    CString &operator=(CString other);

    friend ostream &operator<<(ostream &os, const CString &src);

    bool operator==(const CString &right) const;

    bool operator!=(const CString &right);

private:
    size_t m_Len;
    size_t m_Max;
    char *m_Data;
};

template<typename T>
class CVector {
public:
    CVector();

    ~CVector();

    CVector(const CVector &src);

    CVector &operator=(const CVector<T> &other);

    T &operator[](size_t idx) const;

    void push_back(const T &src);

    void print(ostream &os) const;

    size_t size() const;

private:
    T *m_Data;
    size_t m_Size;
    size_t m_Cap;
};

class CMail {
public:
    CMail(const char *from,
          const char *to,
          const char *body);

    CMail();

    CMail(const CMail &other);

    CMail &operator=(const CMail &other);

    bool operator==(const CMail &x) const;

    friend ostream &operator<<(ostream &os,
                               const CMail &m);

private:
    CString m_From, m_To, m_Body;

    friend class CMailBox;

    friend class CMailServer;

    friend class CMailIterator;
};

class CMailBox {
public:
    CMailBox();

    CMailBox(const CString &mail);

    ~CMailBox();

    CMailBox(const CMailBox &other);

    CMailBox &operator=(const CMailBox &other);

    bool addToInbox(const CMail &mail);

    bool addToOutbox(const CMail &mail);

    friend ostream &operator<<(ostream &os, const CMailBox &mailBox);

private:
    CString m_Email;
    CVector<CMail> m_Inbox;
    CVector<CMail> m_Outbox;

    friend class CMailServer;
};

//class CMailVector {
//private:
//    CVector<CMail> m_MailVector;
//
//    friend class CMailIterator;
//
//    friend class CMailServer;
//};

class CMailIterator {
public:
    CMailIterator();

    explicit operator bool(void) const;

    bool operator!(void) const;

    const CMail &operator*(void) const;

    CMailIterator &operator++(void);

private:
    CMail *m_Ptr;
    size_t m_Pos;
    CVector<CMail> m_MailVector;

    friend class CMailServer;
};

class CMailServer {
public:
    CMailServer(void);

    CMailServer(const CMailServer &src);

    CMailServer &operator=(const CMailServer &src);

    ~CMailServer(void);

    void sendMail(const CMail &m);

    void print(ostream &os) const;

    CMailIterator outbox(const char *email) const;

    CMailIterator inbox(const char *email) const;

private:
    CVector<CMailBox> m_MailBoxVector;
};

CString::CString(const char *src) : m_Len(strlen(src)),
                                    m_Max(m_Len + 1),
                                    m_Data(new char[m_Max]) {
    memcpy(m_Data, src, m_Max);
}

CString::CString() : m_Len(0), m_Max(1), m_Data(new char[m_Max]) {
    m_Data[0] = '\0';
}

CString::~CString() {
    delete[] m_Data;
}

CString::CString(const CString &src) : m_Len(src.m_Len),
                                       m_Max(src.m_Max),
                                       m_Data(new char[m_Max]) {
    memcpy(m_Data, src.m_Data, m_Max);
}

CString &CString::operator=(CString other) {
    m_Max = other.m_Max;
    m_Len = other.m_Len;
    swap(m_Data, other.m_Data);
    return *this;
}

ostream &operator<<(ostream &os, const CString &src) {
    os << src.m_Data;
    return os;
}

bool CString::operator==(const CString &right) const {
    return strcmp(m_Data, right.m_Data) == 0;
}

bool CString::operator!=(const CString &right) {
    return !(*this == right);
}

template<typename T>
CVector<T>::CVector() : m_Size(0), m_Cap(100) {
    m_Data = (new T[m_Cap]);
}

template<typename T>
CVector<T>::~CVector() {
    delete[] m_Data;
}

template<typename T>
CVector<T>::CVector(const CVector<T> &src) : m_Size(src.m_Size),
                                             m_Cap(src.m_Cap) {
    m_Data = new T[m_Cap];
    for (size_t i = 0; i < src.m_Size; i++)
        m_Data[i] = src.m_Data[i];
}

template<typename T>
CVector<T> &CVector<T>::operator=(const CVector<T> &other) {
    if (this == &other)
        return *this;
    m_Size = other.m_Size;
    m_Cap = other.m_Cap;
    delete[] m_Data;
    m_Data = new T[m_Cap];
    for (size_t i = 0; i < m_Size; i++)
        m_Data[i] = other.m_Data[i];
    return *this;
}

template<typename T>
T &CVector<T>::operator[](size_t idx) const {
    return m_Data[idx];
}

template<typename T>
void CVector<T>::push_back(const T &src) {
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

template<typename T>
void CVector<T>::print(ostream &os) const {
    os << "BEGIN: " << endl;
    for (size_t i = 0; i < m_Size; i++) {
        cout << m_Data[i];
    }
    os << "END" << endl;
}

template<typename T>
size_t CVector<T>::size() const {
    return m_Size;
}

CMail::CMail(const char *from, const char *to, const char *body) : m_From(from),
                                                                   m_To(to),
                                                                   m_Body(body) {}

bool CMail::operator==(const CMail &x) const {
    return (m_From == x.m_From
            && m_To == x.m_To
            && m_Body == x.m_Body);
}

CMail &CMail::operator=(const CMail &other) {
    if (this != &other) {
        m_From = other.m_From;
        m_To = other.m_To;
        m_Body = other.m_Body;
    }
    return *this;
}

CMail::CMail(const CMail &other) :
        m_From(other.m_From),
        m_To(other.m_To),
        m_Body(other.m_Body) {}

CMail::CMail() : m_From(), m_To(), m_Body() {}

ostream &operator<<(ostream &os, const CMail &m) {
    os << "From: " << m.m_From << ", To: " << m.m_To << ", Body: " << m.m_Body;
    return os;
}

CMailBox::CMailBox() : m_Email(), m_Inbox(), m_Outbox() {}

CMailBox::CMailBox(const CString &mail) : m_Email(mail) {}

CMailBox::~CMailBox() {}

CMailBox::CMailBox(const CMailBox &other) : m_Email(other.m_Email),
                                            m_Inbox(other.m_Inbox),
                                            m_Outbox(other.m_Outbox) {}

CMailBox &CMailBox::operator=(const CMailBox &other) {
    if (this != &other) {
        m_Email = other.m_Email;
        m_Inbox = other.m_Inbox;
        m_Outbox = other.m_Outbox;
    }
    return *this;
}

bool CMailBox::addToInbox(const CMail &mail) {
    if (mail.m_To == m_Email) {
        m_Inbox.push_back(mail);
        return true;
    }
    return false;
}

bool CMailBox::addToOutbox(const CMail &mail) {
    if (mail.m_From == m_Email) {
        m_Outbox.push_back(mail);
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const CMailBox &mailBox) {
    os << "\nMAIL:\n\n" << mailBox.m_Email << "\n" << endl;

    os << "OUTBOX:\n";
    mailBox.m_Outbox.print(os);

    os << "\nINBOX:\n";
    mailBox.m_Inbox.print(os);

    os << "\nEND OF MAILBOX\n" << endl;
    return os;
}

CMailServer::CMailServer() : m_MailBoxVector() {}

CMailServer::~CMailServer() {}

CMailServer::CMailServer(const CMailServer &src) {
    m_MailBoxVector = src.m_MailBoxVector;
}

CMailServer &CMailServer::operator=(const CMailServer &src) {
    if (this != &src) {
        m_MailBoxVector = src.m_MailBoxVector;
    }
    return *this;
}

void CMailServer::sendMail(const CMail &m) {
    bool senderFound = false;
    bool recepientFound = false;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        if (m_MailBoxVector[i].addToOutbox(m))
            senderFound = true;
        if (m_MailBoxVector[i].addToInbox(m))
            recepientFound = true;
        if (senderFound && recepientFound)
            break;
    }

    if (!senderFound) {
        CMailBox tmp(m.m_From);
        tmp.addToOutbox(m);
        m_MailBoxVector.push_back(tmp);
    }

    if (!recepientFound) {
        CMailBox tmp(m.m_To);
        tmp.addToInbox(m);
        m_MailBoxVector.push_back(tmp);
    }
}

void CMailServer::print(ostream &os) const {
    os << "\nSERVER BEGIN" << endl;
    m_MailBoxVector.print(os);
    os << "\nSERVER END" << endl;
}

CMailIterator CMailServer::outbox(const char *email) const {
    CMailIterator tmp;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        if (m_MailBoxVector[i].m_Email == email) {
            for (size_t j = 0; j < m_MailBoxVector[i].m_Outbox.size(); j++)
                tmp.m_MailVector.push_back(m_MailBoxVector[i].m_Outbox[j]);
        }
    }
    tmp.m_Ptr = &tmp.m_MailVector[0];
    return tmp;
}

CMailIterator CMailServer::inbox(const char *email) const {
    CMailIterator tmp;
    for (size_t i = 0; i < m_MailBoxVector.size(); i++) {
        if (m_MailBoxVector[i].m_Email == email) {
            for (size_t j = 0; j < m_MailBoxVector[i].m_Inbox.size(); j++)
                tmp.m_MailVector.push_back(m_MailBoxVector[i].m_Inbox[j]);
        }
    }
    tmp.m_Ptr = &tmp.m_MailVector[0];
    return tmp;
}

CMailIterator::CMailIterator() : m_Ptr(nullptr), m_Pos(0), m_MailVector() {}

const CMail &CMailIterator::operator*() const {
    return *m_Ptr;
}

CMailIterator &CMailIterator::operator++() {
    ++m_Ptr;
    return *this;
}

CMailIterator::operator bool() const {
    return m_Ptr != nullptr;
}

#ifndef __PROGTEST__

bool matchOutput(const CMail &m,
                 const char *str) {
    ostringstream oss;
    oss << m;
    return oss.str() == str;
}

int main(void) {
    char from[100], to[100], body[1024];

//    CString a("Ahoj");
//
//    CString b(a);
//
//    if (a == b)
//        cout << "SAME" << endl;
//
//    CString c = b;
//
//    CVector<CString> vec;
//
//    vec.push_back(a);
//    vec.push_back(b);
//    vec.push_back(c);
//
//    CVector<CString> vec2 = vec;
//
//    vec2.print(cout);
//
//    CMail mail1("Ahoj", "Cau", "1");
//    CMail mail2("1", "2", "3");
//
//    CVector<CMail> vecMail;
//    vecMail.push_back(mail1);
//    vecMail.push_back(mail2);
//
//    CVector<CMail> vecMail2 = vecMail;
//
//    CMail mail3("SERUS", "KAMO", "#");
//
//    vecMail.push_back(mail3);
//
//    vecMail2.print(cout);
//
//    vecMail.print(cout);
//
//    CMailServer server;
//
//    server.sendMail(mail1);
//    server.sendMail(mail2);
//    server.sendMail(mail3);
//
//    CMailServer server2(server);
//    server.print(cout);
//    server2.sendMail(CMail("novy", "mail", "2"));
//
//    CMailServer server3 = server2;
//    server2.sendMail(CMail("2", "4", "6"));
//    server3.sendMail(CMail("3", "5", "7"));
//
//    server2.print(cout);
//
//    server3.print(cout);
//    vec.print(cout);
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
    cout << *i0;
    assert (i0 && *i0 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
    assert (++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
    assert (!++i0);
//
//    CMailIterator i1 = s0.inbox("john");
//    assert (i1 && *i1 == CMail("alice", "john", "deadline confirmation"));
//    assert (matchOutput(*i1, "From: alice, To: john, Body: deadline confirmation"));
//    assert (!++i1);
//
//    CMailIterator i2 = s0.outbox("john");
//    assert (i2 && *i2 == CMail("john", "peter", "some important mail"));
//    assert (matchOutput(*i2, "From: john, To: peter, Body: some important mail"));
//    assert (++i2 && *i2 == CMail("john", "thomas", "another important mail"));
//    assert (matchOutput(*i2, "From: john, To: thomas, Body: another important mail"));
//    assert (++i2 && *i2 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i2, "From: john, To: alice, Body: deadline notice"));
//    assert (!++i2);
//
//    CMailIterator i3 = s0.outbox("thomas");
//    assert (!i3);
//
//    CMailIterator i4 = s0.outbox("steve");
//    assert (!i4);
//
//    CMailIterator i5 = s0.outbox("thomas");
//    s0.sendMail(CMail("thomas", "boss", "daily report"));
//    assert (!i5);
//
//    CMailIterator i6 = s0.outbox("thomas");
//    assert (i6 && *i6 == CMail("thomas", "boss", "daily report"));
//    assert (matchOutput(*i6, "From: thomas, To: boss, Body: daily report"));
//    assert (!++i6);
//
//    CMailIterator i7 = s0.inbox("alice");
//    s0.sendMail(CMail("thomas", "alice", "meeting details"));
//    assert (i7 && *i7 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i7, "From: john, To: alice, Body: deadline notice"));
//    assert (++i7 && *i7 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i7, "From: peter, To: alice, Body: PR bullshit"));
//    assert (!++i7);
//
//    CMailIterator i8 = s0.inbox("alice");
//    assert (i8 && *i8 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i8, "From: john, To: alice, Body: deadline notice"));
//    assert (++i8 && *i8 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i8, "From: peter, To: alice, Body: PR bullshit"));
//    assert (++i8 && *i8 == CMail("thomas", "alice", "meeting details"));
//    assert (matchOutput(*i8, "From: thomas, To: alice, Body: meeting details"));
//    assert (!++i8);
//
//    CMailServer s1(s0);
//    s0.sendMail(CMail("joe", "alice", "delivery details"));
//    s1.sendMail(CMail("sam", "alice", "order confirmation"));
//    CMailIterator i9 = s0.inbox("alice");
//    assert (i9 && *i9 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i9, "From: john, To: alice, Body: deadline notice"));
//    assert (++i9 && *i9 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i9, "From: peter, To: alice, Body: PR bullshit"));
//    assert (++i9 && *i9 == CMail("thomas", "alice", "meeting details"));
//    assert (matchOutput(*i9, "From: thomas, To: alice, Body: meeting details"));
//    assert (++i9 && *i9 == CMail("joe", "alice", "delivery details"));
//    assert (matchOutput(*i9, "From: joe, To: alice, Body: delivery details"));
//    assert (!++i9);
//
//    CMailIterator i10 = s1.inbox("alice");
//    assert (i10 && *i10 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i10, "From: john, To: alice, Body: deadline notice"));
//    assert (++i10 && *i10 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i10, "From: peter, To: alice, Body: PR bullshit"));
//    assert (++i10 && *i10 == CMail("thomas", "alice", "meeting details"));
//    assert (matchOutput(*i10, "From: thomas, To: alice, Body: meeting details"));
//    assert (++i10 && *i10 == CMail("sam", "alice", "order confirmation"));
//    assert (matchOutput(*i10, "From: sam, To: alice, Body: order confirmation"));
//    assert (!++i10);
//
//    CMailServer s2;
//    s2.sendMail(CMail("alice", "alice", "mailbox test"));
//    CMailIterator i11 = s2.inbox("alice");
//    assert (i11 && *i11 == CMail("alice", "alice", "mailbox test"));
//    assert (matchOutput(*i11, "From: alice, To: alice, Body: mailbox test"));
//    assert (!++i11);
//
//    s2 = s0;
//    s0.sendMail(CMail("steve", "alice", "newsletter"));
//    s2.sendMail(CMail("paul", "alice", "invalid invoice"));
//    CMailIterator i12 = s0.inbox("alice");
//    assert (i12 && *i12 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i12, "From: john, To: alice, Body: deadline notice"));
//    assert (++i12 && *i12 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i12, "From: peter, To: alice, Body: PR bullshit"));
//    assert (++i12 && *i12 == CMail("thomas", "alice", "meeting details"));
//    assert (matchOutput(*i12, "From: thomas, To: alice, Body: meeting details"));
//    assert (++i12 && *i12 == CMail("joe", "alice", "delivery details"));
//    assert (matchOutput(*i12, "From: joe, To: alice, Body: delivery details"));
//    assert (++i12 && *i12 == CMail("steve", "alice", "newsletter"));
//    assert (matchOutput(*i12, "From: steve, To: alice, Body: newsletter"));
//    assert (!++i12);
//
//    CMailIterator i13 = s2.inbox("alice");
//    assert (i13 && *i13 == CMail("john", "alice", "deadline notice"));
//    assert (matchOutput(*i13, "From: john, To: alice, Body: deadline notice"));
//    assert (++i13 && *i13 == CMail("peter", "alice", "PR bullshit"));
//    assert (matchOutput(*i13, "From: peter, To: alice, Body: PR bullshit"));
//    assert (++i13 && *i13 == CMail("thomas", "alice", "meeting details"));
//    assert (matchOutput(*i13, "From: thomas, To: alice, Body: meeting details"));
//    assert (++i13 && *i13 == CMail("joe", "alice", "delivery details"));
//    assert (matchOutput(*i13, "From: joe, To: alice, Body: delivery details"));
//    assert (++i13 && *i13 == CMail("paul", "alice", "invalid invoice"));
//    assert (matchOutput(*i13, "From: paul, To: alice, Body: invalid invoice"));
//    assert (!++i13);

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
