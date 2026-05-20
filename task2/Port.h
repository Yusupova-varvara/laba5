#ifndef PORT_H
#define PORT_H

#include <string>
#include <vector>
using namespace std;

class Port {
public:
    Port(int maxStackWeight, int numSections);
    void arrive(const string& containerId, int weight);
    void load();
    void printStacks() const;

private:
    struct Container {
        string id;
        int weight;
        Container(const string& i, int w) : id(i), weight(w) {}
    };

    struct Stack {
        vector<Container> items;
        int curWeight;

        Stack() : curWeight(0) {}

        void pushContainer(const Container& c) {
            items.push_back(c);
            curWeight += c.weight;
        }

        Container popContainer() {
            Container c = items.back();
            items.pop_back();
            curWeight -= c.weight;
            return c;
        }

        bool canAddWeight(int w, int maxW) const {
            return curWeight + w <= maxW;
        }

        bool hasNoItems() const {
            return items.empty();
        }

        int getStackWeight() const {
            return curWeight;
        }

        const vector<Container>& getStackItems() const {
            return items;
        }
    };

    int maxWeightPerStack;
    int shipSections;
    vector<Stack> portStacks;
    string generateContainerId();
    int nextId;
};

#endif
