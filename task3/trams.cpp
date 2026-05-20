#include "trams.h"
#include <iostream>

using namespace std;

Cmd toCmd(const string& s) {
    if (s == "CREATE_TRAM") return Cmd::CREATE_TRAM;
    if (s == "TRAMS_IN_STOP") return Cmd::TRAMS_IN_STOP;
    if (s == "STOPS_IN_TRAM") return Cmd::STOPS_IN_TRAM;
    if (s == "TRAMS") return Cmd::TRAMS;
    if (s == "EXIT") return Cmd::EXIT;
    return Cmd::UNKNOWN;
}

bool hasDup(vector<string>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[i] == v[j]) 
                return true;
        }
    }
    return false;
}

void addTram(map<string, Tram>& db, string name, int cnt) {
    if (db.count(name)) {
        cout << "Ошибка: Трамвай с именем " << name << " уже создан" << endl;
        return;
    }

    if (cnt < 2) {
        cout << "Ошибка: Трамвай не может быть создан с одной остановкой" << endl;
        return;
    }

    vector<string> v;
    for (int i = 0; i < cnt; i++) {
        string x;
        cin >> x;
        v.push_back(x);
    }

    if (hasDup(v)) {
        cout << "Ошибка: Трамвай не может быть создан с двумя одинаковыми остановками" << endl;
        return;
    }

    db[name] = { v };
    cout << "Трамвай " << name << " создан" << endl;
}

void getStop(map<string, Tram>& db, string stop) {
    bool ok = false;

    for (auto& it : db) {
        for (auto& x : it.second.stops) {
            if (x == stop) {
                ok = true;
                break;
            }
        }
    }

    if (!ok) {
        cout << "Ошибка: Остановка " << stop << " не найдена" << endl;
        return;
    }

    cout << "Трамваи на остановке " << stop << ": ";

    bool first = true;
    for (auto& it : db) {
        for (auto& x : it.second.stops) {
            if (x == stop) {
                if (!first) 
                    cout << ", ";
                cout << it.first;
                first = false;
                break;
            }
        }
    }
    cout << endl;
}

void getTram(map<string, Tram>& db, string name) {
    if (!db.count(name)) {
        cout << "Ошибка: Трамвай " << name << " не найден" << endl;
        return;
    }

    cout << "Остановки трамвая " << name << ": ";
    for (int i = 0; i < db[name].stops.size(); i++) {
        if (i > 0) cout << " ";
        cout << db[name].stops[i];
    }
    cout << endl;

    for (auto& s : db[name].stops) {
        cout << "  Остановка " << s << ": ";

        bool first = true;
        for (auto& it : db) {
            if (it.first == name) continue;

            for (auto& x : it.second.stops) {
                if (x == s) {
                    if (!first) cout << ", ";
                    cout << it.first;
                    first = false;
                    break;
                }
            }
        }

        if (first) cout << "-";
        cout << endl;
    }
}

void showAll(map<string, Tram>& db) {
    if (db.empty()) {
        cout << "Ошибка: Трамваи не найдены" << endl;
        return;
    }

    for (auto& it : db) {
        cout << "Трамвай " << it.first << ": ";
        for (int i = 0; i < it.second.stops.size(); i++) {
            if (i > 0) cout << " ";
            cout << it.second.stops[i];
        }
        cout << endl;
    }
}

bool proc(const string& s, map<string, Tram>& db) {
    Cmd c = toCmd(s);
    
    switch (c) {
        case Cmd::CREATE_TRAM: {
            string name;
            int cnt;
            cin >> name >> cnt;
            addTram(db, name, cnt);
            break;
        }
        case Cmd::TRAMS_IN_STOP: {
            string stop;
            cin >> stop;
            getStop(db, stop);
            break;
        }
        case Cmd::STOPS_IN_TRAM: {
            string name;
            cin >> name;
            getTram(db, name);
            break;
        }
        case Cmd::TRAMS:
            showAll(db);
            break;
        case Cmd::EXIT:
            return false;
        case Cmd::UNKNOWN:
            cout << "Неизвестная команда" << endl;
            break;
    }
    return true;
}
