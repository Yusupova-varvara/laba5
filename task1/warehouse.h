#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Cell {
    string itemName;      
    int itemCount;        
};

struct Warehouse {
    int zones = 2;          
    int shelves = 15;       
    int section = 3;        
    int shelvesHigh = 5;    
    int maxNumProd = 10;    

    int filledZoneA = 0, filledZoneB = 0;  

    map<string, Cell> warehouseData;  

    Warehouse();

    bool isValidAddress(string addr);  

    void addItem(string name, int count, string addr);     
    void removeItem(string name, int count, string addr);  
    void displayInfo();  
    void processCommand(); 
};

#endif
