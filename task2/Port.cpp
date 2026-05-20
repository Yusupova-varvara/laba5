#include "Port.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Port::Port(int maxStackWeight, int numSections)
    : maxWeightPerStack(maxStackWeight), shipSections(numSections), nextId(1) {
}

string Port::generateContainerId() {
    ostringstream oss;
    oss << "C" << setw(3) << setfill('0') << nextId;
    nextId++;
    return oss.str();
}

void Port::arrive(const string& containerId, int weight) {
    if (weight > maxWeightPerStack) {
        cout << "Ошибка: Вес контейнера " << weight << " превышает максимальный вес стека " << maxWeightPerStack << endl;
        return;
    }

    for (size_t i = 0; i < portStacks.size(); i++) {
        if (portStacks[i].canAddWeight(weight, maxWeightPerStack)) {
            portStacks[i].pushContainer(Container(containerId, weight));
            cout << "Контейнер " << containerId << " размещен в стек " << (i + 1) << endl;
            return;
        }
    }

    Stack newStack;
    newStack.pushContainer(Container(containerId, weight));
    portStacks.push_back(newStack);
    cout << "Контейнер " << containerId << " размещен в стек " << portStacks.size() << endl;
}

void Port::load() {
    if (portStacks.empty()) {
        cout << "Нет контейнеров для загрузки" << endl;
        return;
    }

    vector<Container> allContainers;

    for (auto& st : portStacks) {
        while (!st.hasNoItems()) {
            allContainers.push_back(st.popContainer());
        }
    }

    if (allContainers.empty()) {
        cout << "Нет контейнеров для загрузки" << endl;
        return;
    }

    struct ShipSection {
        vector<string> containerList;
        int totalWeight;
        ShipSection() : totalWeight(0) {}
    };

    vector<ShipSection> sections(shipSections);

    for (const auto& cont : allContainers) {
        int minIdx = 0;
        for (int i = 1; i < shipSections; i++) {
            if (sections[i].totalWeight < sections[minIdx].totalWeight) {
                minIdx = i;
            }
        }

        sections[minIdx].containerList.push_back(cont.id);
        sections[minIdx].totalWeight += cont.weight;
    }

    for (int i = 0; i < shipSections; i++) {
        cout << "Секция " << (i + 1) << " (" << sections[i].totalWeight << " тонн): ";
        for (size_t j = 0; j < sections[i].containerList.size(); j++) {
            if (j > 0) cout << ", ";
            cout << sections[i].containerList[j];
        }
        cout << endl;
    }

    portStacks.clear();
}

void Port::printStacks() const {
    cout << "\nСостояние стеков" << endl;
    if (portStacks.empty()) {
        cout << "Нет стеков" << endl;
        return;
    }

    for (size_t i = 0; i < portStacks.size(); i++) {
        cout << "Стек " << (i + 1) << " (вес: " << portStacks[i].getStackWeight() << "/" << maxWeightPerStack << "): ";
        const auto& items = portStacks[i].getStackItems();
        for (size_t j = 0; j < items.size(); j++) {
            if (j > 0) cout << ", ";
            cout << items[j].id << "(" << items[j].weight << ")";
        }
        cout << endl;
    }
}
