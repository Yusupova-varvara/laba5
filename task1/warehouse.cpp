#include "warehouse.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

Warehouse::Warehouse() {
    char zoneList[] = { 'A', 'B' };
    for (char currentZone : zoneList) {
        for (int rackNum = 1; rackNum <= shelves; rackNum++) {
            for (int sectNum = 1; sectNum <= section; sectNum++) {
                for (int levelNum = 1; levelNum <= shelvesHigh; levelNum++) {
                    string fullAddress = string(1, currentZone) + to_string(rackNum) + to_string(sectNum) + to_string(levelNum);
                    warehouseData[fullAddress] = Cell();
                }
            }
        }
    }
}

void Warehouse::processCommand() {
    string userInput;
    while (true) {
        getline(cin, userInput);
        if (userInput == "EXIT") 
            break;
        else if (userInput == "INFO") {
            this->displayInfo(); 
            continue;
        }

        int firstSpace = userInput.find(' ', 0);
        string commandType = userInput.substr(0, firstSpace);

        int secondSpace = userInput.find(' ', firstSpace + 1);
        string itemName = userInput.substr(firstSpace + 1, secondSpace - firstSpace - 1);

        int thirdSpace = userInput.find(' ', secondSpace + 1);
        int itemCount = stoi(userInput.substr(secondSpace + 1, thirdSpace - secondSpace - 1));

        string targetAddress = userInput.substr(thirdSpace + 1);

        if (commandType == "ADD")
            this->addItem(itemName, itemCount, targetAddress);  
        else if (commandType == "REMOVE")
            this->removeItem(itemName, itemCount, targetAddress); 
    }
    return;
}

bool Warehouse::isValidAddress(string addr) {
    return (warehouseData.count(addr) == 0);
}

void Warehouse::addItem(string name, int count, string addr) {
    if (isValidAddress(addr)) {
        cout << "Ошибка: Адрес " << addr << " не существует на складе" << endl;
        return;
    }

    Cell& targetCell = warehouseData[addr];

    if (!targetCell.itemName.empty() && targetCell.itemName != name) {
        cout << "Ошибка: Ячейка занята товаром " << targetCell.itemName << endl;
        return;
    }

    else if (targetCell.itemCount + count > maxNumProd) {
        cout << "Ошибка: Превышена вместимость (максимум " << maxNumProd << ")" << endl;
        return;
    }

    else {
        targetCell.itemName = name;
        targetCell.itemCount += count;
        if (addr[0] == 'A')
            filledZoneA += count;
        else
            filledZoneB += count;
        cout << "Добавлено " << count << " " << name << " в " << addr << endl;
    }
}

void Warehouse::removeItem(string name, int count, string addr) {
    if (isValidAddress(addr)) {
        cout << "Ошибка: Адрес " << addr << " не существует на складе" << endl;
        return;
    }

    Cell& targetCell = warehouseData[addr];

    if (targetCell.itemName.empty() || targetCell.itemName != name) {
        cout << "Ошибка: Товар " << name << " не найден" << endl;
        return;
    }

    if (targetCell.itemCount < count) {
        cout << "Ошибка: Недостаточно товара (есть " << targetCell.itemCount << ")" << endl;
        return;
    }

    targetCell.itemCount -= count;
    if (targetCell.itemCount == 0) {
        targetCell.itemName = "";
        cout << "Удалено " << count << " " << name << " (ячейка пуста)" << endl;
    }
    else {
        cout << "Удалено " << count << " " << name << " (остаток " << targetCell.itemCount << ")" << endl;
    }

    if (addr[0] == 'A') 
        filledZoneA -= count;
    else 
        filledZoneB -= count;
}

void Warehouse::displayInfo() {
    int totalCapacity = 4500;   
    int zoneCapacity = 2250;    
    int totalFilled = filledZoneA + filledZoneB;

    cout << fixed << setprecision(2) << endl;
    cout << "Загруженность склада: " << (double)totalFilled / totalCapacity * 100 << " %" << endl;
    cout << "Загруженность зоны А: " << (double)filledZoneA / zoneCapacity * 100 << " %" << endl;
    cout << "Загруженность зоны Б: " << (double)filledZoneB / zoneCapacity * 100 << " %" << endl;

    vector<string> filledCells;
    vector<string> emptyCells;

    for (auto& entry : warehouseData) {
        string addr = entry.first;
        Cell currentCell = entry.second;

        if (currentCell.itemCount > 0) 
            filledCells.push_back(addr);
        else 
            emptyCells.push_back(addr);
    }

    sort(filledCells.begin(), filledCells.end());
    sort(emptyCells.begin(), emptyCells.end());

    cout << endl << "Заполненные ячейки:" << endl;
    if (filledCells.empty()) 
        cout << "  (нет)" << endl;
    else {
        for (string addr : filledCells) {
            cout << "  " << addr << ": " << warehouseData[addr].itemName << " (" << warehouseData[addr].itemCount << ")" << endl;
        }
    }

    cout << endl << "Пустые ячейки:" << endl;
    if (emptyCells.empty()) 
        cout << "  (нет)" << endl;
    else {
        for (int i = 0; i < 5 && i < emptyCells.size(); i++)  
            cout << emptyCells[i] << "  ";
        if (emptyCells.size() > 5) 
            cout << "... и еще " << (emptyCells.size() - 5) << " ячеек";
        cout << endl;
    }
    cout << endl;
}
