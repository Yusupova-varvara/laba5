#ifndef REGIONS_H
#define REGIONS_H

#include <string>
#include <map>

using namespace std;

void addRegion(map<string, string>& regs, map<string, string>& centers, const string& regName, const string& centerName);
void renameCenter(map<string, string>& regs, map<string, string>& centers, const string& oldName, const string& newName);
void showRegion(const map<string, string>& regs, const string& regName);
void showAllRegions(const map<string, string>& regs);
void processCommand(string cmd, map<string, string>& regs, map<string, string>& centers);

#endif
