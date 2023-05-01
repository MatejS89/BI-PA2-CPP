#ifndef __PROGTEST__

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

template<typename M_>
class CContest {
public:
    CContest() {};

    ~CContest() {};

    CContest &addMatch(const string &team1, const string &team2, const M_ &result) {
        pair tmp = make_pair(team1, team2);
        pair tmp2 = make_pair(team2, team1);
        if (m_Matches.count(tmp) != 0 || m_Matches.count(tmp2) != 0)
            throw logic_error("DUPLICATE MATCH!");
        m_Matches.insert(make_pair(tmp, result));
        return *this;
    }

    bool isOrdered(const function<int(const M_ &match)> &cmp) const {
        set<int> wins;
        map<string, set<string>> graph;
        for (const auto &match: m_Matches) {
            const auto &result = match.second;
            const auto &team1 = match.first.first;
            const auto &team2 = match.first.second;
            if (cmp(result) > 0)
                graph[team1].insert(team2);
            else if (cmp(result) < 0)
                graph[team2].insert(team1);
            else
                return false;
        }

        for (const auto &team: graph) {
            const auto &teamName = team.first;
            queue<string> q;
            set<string> visited;
            int teamWins = 0;
            q.push(teamName);
            visited.insert(teamName);
            while (!q.empty()) {
                string curr = q.front();
                q.pop();
                for (const auto &neighbor: graph[curr]) {
                    if (visited.count(neighbor) == 0) {
                        visited.insert(neighbor);
                        teamWins++;
                        q.push(neighbor);
                    }
                }
            }
            if (!wins.insert(teamWins).second)
                return false;
        }
        return true;
    }

    list<string> results(const function<int(const M_ &match)> &cmp) const {
        map<string, int> leaderboard;
        map<string, set<string>> graph;
        for (const auto &match: m_Matches) {
            const auto &result = match.second;
            const auto &team1 = match.first.first;
            const auto &team2 = match.first.second;
            leaderboard.insert({team1, 0});
            leaderboard.insert({team2, 0});
            if (cmp(result) > 0)
                graph[team1].insert(team2);
            else if (cmp(result) < 0)
                graph[team2].insert(team1);
            else
                throw logic_error("DRAW FOUND");
        }

        for (const auto &team: graph) {
            const auto &teamName = team.first;
            queue<string> q;
            set<string> visited;
            int teamWins = 0;
            q.push(teamName);
            visited.insert(teamName);
            while (!q.empty()) {
                string curr = q.front();
                q.pop();
                for (const auto &neighbor: graph[curr]) {
                    if (visited.count(neighbor) == 0) {
                        visited.insert(neighbor);
                        teamWins++;
                        q.push(neighbor);
                    }
                }
            }
            leaderboard[teamName] = teamWins;
        }

        map<int, string> byWins;
        for (const auto &item: leaderboard) {
            if (!byWins.emplace(item.second, item.first).second)
                throw logic_error("ORDER NOT POSSIBLE");
        }

        list<string> tmp;
        for (const auto &item: byWins) {
            tmp.emplace_back(item.second);
        }
        tmp.reverse();
        return tmp;
    }

private:
    map<pair<string, string>, M_> m_Matches;
};

#ifndef __PROGTEST__

struct CMatch {
public:
    CMatch(int a,
           int b)
            : m_A(a),
              m_B(b) {
    }

    int m_A;
    int m_B;
};

class HigherScoreThreshold {
public:
    HigherScoreThreshold(int diffAtLeast)
            : m_DiffAtLeast(diffAtLeast) {
    }

    int operator()(const CMatch &x) const {
        return (x.m_A > x.m_B + m_DiffAtLeast) - (x.m_B > x.m_A + m_DiffAtLeast);
    }

private:
    int m_DiffAtLeast;
};

int HigherScore(const CMatch &x) {
    return (x.m_A > x.m_B) - (x.m_B > x.m_A);
}

int main(void) {
    CContest<CMatch> x;
    x.addMatch("C++", "Pascal", CMatch(10, 3))
            .addMatch("C++", "Java", CMatch(8, 1))
            .addMatch("Pascal", "Basic", CMatch(40, 0))
            .addMatch("Java", "PHP", CMatch(6, 2))
            .addMatch("Java", "Pascal", CMatch(7, 3))
            .addMatch("PHP", "Basic", CMatch(10, 0));

    assert (!x.isOrdered(HigherScore));
    try {
        list<string> res = x.results(HigherScore);
        assert ("Exception missing!" == nullptr);
    }
    catch (const logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == nullptr);
    }

    x.addMatch("PHP", "Pascal", CMatch(3, 6));

    assert (x.isOrdered(HigherScore));
    try {
        list<string> res = x.results(HigherScore);
        assert ((res == list<string>{"C++", "Java", "Pascal", "PHP", "Basic"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == nullptr);
    }


    assert (!x.isOrdered(HigherScoreThreshold(3)));
    try {
        list<string> res = x.results(HigherScoreThreshold(3));
        assert ("Exception missing!" == nullptr);
    }
    catch (const logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == nullptr);
    }

    assert (x.isOrdered([](const CMatch &x) {
        return (x.m_A < x.m_B) - (x.m_B < x.m_A);
    }));
    try {
        list<string> res = x.results([](const CMatch &x) {
            return (x.m_A < x.m_B) - (x.m_B < x.m_A);
        });
        assert ((res == list<string>{"Basic", "PHP", "Pascal", "Java", "C++"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == nullptr);
    }

    CContest<bool> y;

    y.addMatch("Python", "PHP", true)
            .addMatch("PHP", "Perl", true)
            .addMatch("Perl", "Bash", true)
            .addMatch("Bash", "JavaScript", true)
            .addMatch("JavaScript", "VBScript", true);

    assert (y.isOrdered([](bool v) {
        return v ? 10 : -10;
    }));
    try {
        list<string> res = y.results([](bool v) {
            return v ? 10 : -10;
        });
        assert ((res == list<string>{"Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript"}));
    }
    catch (...) {
        assert ("Unexpected exception!" == nullptr);
    }

    y.addMatch("PHP", "JavaScript", false);
    assert (!y.isOrdered([](bool v) {
        return v ? 10 : -10;
    }));
    try {
        list<string> res = y.results([](bool v) {
            return v ? 10 : -10;
        });
        assert ("Exception missing!" == nullptr);
    }
    catch (const logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == nullptr);
    }

    try {
        y.addMatch("PHP", "JavaScript", false);
        assert ("Exception missing!" == nullptr);
    }
    catch (const logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == nullptr);
    }

    try {
        y.addMatch("JavaScript", "PHP", true);
        assert ("Exception missing!" == nullptr);
    }
    catch (const logic_error &e) {
    }
    catch (...) {
        assert ("Invalid exception thrown!" == nullptr);
    }
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
