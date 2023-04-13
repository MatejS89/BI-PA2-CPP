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
    CString(const char *src) : m_Size(strlen(src) + 1), m_Data(new char[m_Size]) {
        memcpy(m_Data, src, m_Size);
    }

    CString() : m_Size(0), m_Data(nullptr) {}

    ~CString() {
        delete[] m_Data;
    }

    size_t size(void) const {
        return m_Size;
    }

    CString & operator =(const CString& other) {
        if( this->m_Data != other.m_Data)
        {
            delete[] m_Data;
            m_Size = other.m_Size;
            m_Data = new char[m_Size];
            memcpy(m_Data, other.m_Data, m_Size);
        }
        return *this;
    }

    bool operator ==(const CString &right) const
    {
        return strcmp(this->m_Data, right.m_Data) == 0;
    }

    bool operator ==( const char *right) const
    {
        return strcmp(this->m_Data, right) == 0;
    }

    bool operator !=( const CString &right) const
    {
        return !(*this == right);
    }

    friend ostream & operator <<(ostream &os, const CString &src);
private:
    size_t m_Size;
    char * m_Data;
};

class CMail {
public:
    CMail(const char *from,
          const char *to,
          const char *body): m_From(from), m_To(to), m_Body(body) {}

    CMail(): m_From(CString()), m_To(CString()), m_Body(CString()){};

    bool operator ==(const CMail &x) const
    {
        return (this->m_From == x.m_From
                && this->m_To == x.m_To
                && this->m_Body == x.m_Body);
    }

    bool operator !=(const CMail &right) const
    {
        return !(*this == right);
    }

    friend ostream & operator <<(ostream &os,
                                  const CMail &src);

private:
    friend class CMailServer;
    CString m_From, m_To, m_Body;
};

template<typename T>
class Vector
{
public:
    Vector() : m_Data(new T[100]),
               m_Size(0),
               m_Cap(100){};

    ~Vector() {
        delete[] m_Data;
        m_Size = 0;
        m_Cap = 0;
    }

    T &operator[] (int idx) const
    {
        return m_Data[idx];
    }

    void push_back (const T &other)
    {
        if( m_Size >= m_Cap)
        {
            m_Cap += 2;
            m_Cap *= 2;
            T * tmp = new T[m_Cap];
            for( size_t i = 0; i < m_Size; i++ )
                tmp[i] = m_Data[i];
            delete[] m_Data;
            m_Data = tmp;
        }
        m_Data[m_Size] = other;
        m_Size++;
    }

    void print() const {
        for (size_t i = 0; i < m_Size; i++)
        {
            cout << m_Data[i] << endl;
        }
    }

private:
    T * m_Data;
    size_t m_Size;
    size_t m_Cap;
    friend class CMailServer;
    friend class CMailIterator;
};

class CMailIterator {
public:
    explicit operator bool(void) const
    {
        if(m_Vector.m_Size == 0) return false;
        if(pos>=m_Vector.m_Size) return false;
        return true;
    }

    bool operator!(void) const
    {
    }

    const CMail &operator*(void) const
    {
        return *m_Vector[pos];
    }

    CMailIterator &operator++(void)
    {
        pos++;
    }

private:
    size_t pos;
    friend class CMailServer;
    Vector<CMail*> m_Vector;
};

class CMailServer {
public:
    CMailServer(void) {};

    CMailServer(const CMailServer &src);

    CMailServer &operator=(const CMailServer &src) {
    };

    ~CMailServer(void) {
    };

    CMailServer &sendMail(const CMail &m) {
        m_MailVector.push_back(m);
        return *this;
    }

    void print() const {
        cout << "VECBYFROM" << endl;
    }

    CMailIterator outbox(const char *email) const
    {
        CMailIterator tmp;
        tmp.pos = 0;
        for (size_t i = 0; i < m_MailVector.m_Size; i++)
        {
            if(m_MailVector[i].m_From == email)
            {
                tmp.m_Vector.push_back(&m_MailVector[i]);
            }
        }
        return tmp;
    }

    CMailIterator inbox(const char *email) const
    {
        CMailIterator tmp;
        tmp.pos = 0;
        for(size_t i = 0; i < m_MailVector.m_Size; i++)
        {
            if(m_MailVector[i].m_To == email)
            {
                tmp.m_Vector.push_back(&m_MailVector[i]);
            }
        }
        return tmp;
    }

private:
    Vector<CMail> m_MailVector;
};

ostream & operator << (ostream &os,const CString &src)
{
    os << src.m_Data;
}

ostream & operator << (ostream &os,const CMail &src)
{
    os << "From: "<<src.m_From << ", To: " << src.m_To << ", Body: " << src.m_Body;
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
    CMail mail1("john", "peter", "progtest deadline");
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
    assert (i0 && *i0 == CMail("john", "alice", "deadline notice"));
    assert (matchOutput(*i0, "From: john, To: alice, Body: deadline notice"));
    assert (++i0 && *i0 == CMail("peter", "alice", "PR bullshit"));
    assert (matchOutput(*i0, "From: peter, To: alice, Body: PR bullshit"));
//    assert (!++i0);
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
