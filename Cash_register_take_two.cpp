#include "iostream"
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main () {
    vector<pair<string, vector<int>>> Receipt;
    string line;
    istringstream iss;
    while(getline(cin, line)) {
        iss.clear();
        iss.str(line);

        string item;
        int price;

        while(iss.good()) {
            iss >> item >> price;
        }

        int i;
        bool found = false;
        for(i = 0; i < Receipt.size(); i++) {
            if(Receipt[i].first == item) {
                found = true;
                break;
            }
        }

        if(found) {
            Receipt[i].second.emplace_back(price);
        }
        else {
            vector<int> term;
            term.emplace_back(price);
            Receipt.emplace_back(make_pair(item, term));
        }
    }

    int total = 0;
    for(int i = 0; i < Receipt.size(); i++) {
        int current_item = 0;
        for(int j = 0; j < Receipt[i].second.size(); j++) {
            current_item += Receipt[i].second[j];
        }
        cout << Receipt[i].first << " " << Receipt[i].second.size() << " " << Receipt[i].second.front() << " " << current_item << endl;

        total += current_item;
    }

    cout << total << endl; 
}