#include "warehouse.h"

int main() {
    Warehouse warehouse;
    string cmd;

    cout << "Команды:" << endl;
    cout << "  ADD <товар> <кол-во> <адрес>" << endl;
    cout << "  REMOVE <товар> <кол-во> <адрес>" << endl;
    cout << "  INFO" << endl;
    cout << "  EXIT" << endl << endl;

    warehouse.processCommand();  
    return 0;
}
