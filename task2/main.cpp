#include "Port.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int maxStackWeight, numSections;

    cout << "=== Программа управления контейнерами в порту ===" << endl;
    cout << endl;

    cout << "Введите максимальный размер стека (в тоннах): ";
    cin >> maxStackWeight;
    cin.ignore();

    cout << "Введите количество секций судна: ";
    cin >> numSections;
    cin.ignore();

    cout << endl;

    Port port(maxStackWeight, numSections);

    cout << "Команды:" << endl;
    cout << " ARRIVE <вес> - прибытие контейнера (ID присваивается автоматически: C001, C002...)" << endl;
    cout << " LOAD - загрузить контейнеры на судно" << endl;
    cout << " STACKS - показать состояние стеков" << endl;
    cout << " EXIT - выход из программы" << endl;
    cout << endl;

    string line;
    int containerCounter = 1;

    while (true) {
        cout << ">>> ";
        getline(cin, line);

        if (line == "EXIT") {
            cout << "Выход из программы." << endl;
            break;
        }

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "ARRIVE") {
            int w;
            if (iss >> w) {
                ostringstream oss;
                oss << "C" << setw(3) << setfill('0') << containerCounter;
                string contId = oss.str();
                containerCounter++;
                port.arrive(contId, w);
            } else {
                cout << "Ошибка: Неверный формат команды ARRIVE" << endl;
                cout << "Правильно: ARRIVE <вес>" << endl;
            }
        }
        else if (cmd == "LOAD") {
            port.load();
        }
        else if (cmd == "STACKS") {
            port.printStacks();
        }
        else if (cmd.empty()) {
            continue;
        }
        else {
            cout << "Неизвестная команда: " << cmd << endl;
            cout << "Доступные команды: ARRIVE, LOAD, STACKS, EXIT" << endl;
        }
    }

    return 0;
}
