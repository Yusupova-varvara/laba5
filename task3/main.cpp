#include "trams.h"
#include <iostream>

using namespace std;

int main() {
    map<string, Tram> db;
    string s;

    while (true) {
        cin >> s;
        if (!proc(s, db))
            break;
    }

    return 0;
}
