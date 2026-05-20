#include "regions.h"
#include <iostream>

using namespace std;

void addRegion(map<string, string>& regs, map<string, string>& centers, const string& regName, const string& centerName) {
    if (regs.count(regName)) {
        cout << "Ошибка: Регион " + regName + " уже создан" << endl;
    }
    else if (centers.count(centerName)) {
        cout << "Ошибка: " + centerName + " уже является административным центром другого региона" << endl;
    }
    else {
        regs[regName] = centerName;
        centers[centerName] = regName;
        cout << "Новый регион " + regName + " с административным центром " + centerName << endl;
    }
}

void renameCenter(map<string, string>& regs, map<string, string>& centers, const string& oldName, const string& newName) {
    if (oldName == newName) {
        cout << "Ошибка: Нельзя переименовать " + oldName + " в то же название" << endl;
    }
    else if (centers.count(newName)) {
        cout << "Ошибка: " + newName + " уже является административным центром другого региона" << endl;
    }
    else if (!centers.count(oldName)) {
        cout << "Ошибка: Административный центр " + oldName + " не найден" << endl;
    }
    else {
        string regName = centers[oldName];
        centers[newName] = regName;
        regs[regName] = newName;
        centers.erase(oldName);
        cout << "Административный центр " + oldName + " переименован в административный центр " + newName << endl;
    }
}

void showRegion(const map<string, string>& regs, const string& regName) {
    if (!regs.count(regName)) {
        cout << "Ошибка: Регион " + regName + " не найден" << endl;
    }
    else {
        cout << "Регион " + regName + " имеет административный центр " + regs.at(regName) << endl;
    }
}

void showAllRegions(const map<string, string>& regs) {
    if (regs.empty()) {
        cout << "Ошибка: Регионы не найдены" << endl;
        return;
    }
    
    bool first = true;
    for (auto& pair : regs) {
        if (!first) 
            cout << ", ";
        cout << pair.first << " – " << pair.second;
        first = false;
    }
    cout << endl;
}

void processCommand(string cmd, map<string, string>& regs, map<string, string>& centers) {
    if (cmd == "CHANGE") {
        string regName, centerName;
        cin >> regName >> centerName;
        addRegion(regs, centers, regName, centerName);
    }
    else if (cmd == "RENAME") {
        string oldName, newName;
        cin >> oldName >> newName;
        renameCenter(regs, centers, oldName, newName);
    }
    else if (cmd == "ABOUT") {
        string regName;
        cin >> regName;
        showRegion(regs, regName);
    }
    else if (cmd == "ALL") {
        showAllRegions(regs);
    }
    else if (cmd == "EXIT") {
        return;
    }
    else {
        cout << "Неизвестная команда" << endl;
    }
}
