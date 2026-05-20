#ifndef TRAMS_H
#define TRAMS_H

#include <string>
#include <vector>
#include <map>

using namespace std;

enum class Cmd {
    CREATE_TRAM,
    TRAMS_IN_STOP,
    STOPS_IN_TRAM,
    TRAMS,
    EXIT,
    UNKNOWN
};

struct Tram {
    vector<string> stops;
};

Cmd toCmd(const string& s);

bool hasDup(vector<string>& v);
void addTram(map<string, Tram>& db, string name, int cnt);
void getStop(map<string, Tram>& db, string stop);
void getTram(map<string, Tram>& db, string name);
void showAll(map<string, Tram>& db);
bool proc(const string& s, map<string, Tram>& db);

#endif
