#include "regions.h"
#include <iostream>

using namespace std;

int main() {
    map<string, string> regs;   
    map<string, string> centers; 

    int n;
    cout << "Введите количество запросов (N):" << endl;
    cout << ">>> ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << ">>> ";
        string cmd;
        cin >> cmd;
        if (cmd == "EXIT") break;
        processCommand(cmd, regs, centers);
    }

    return 0;
}
