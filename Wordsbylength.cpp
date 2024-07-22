#include "iostream"
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main () {
    ifstream inFile;
    istringstream iss;

    map<int, set<string>> my_words;

    inFile.open("input1.txt");

    if(inFile.good()) {
        while(!inFile.eof()) {
            string line;
            getline(inFile, line);

            if(inFile.good()) {
                iss.clear();
                iss.str(line);

                while(iss.good()) {
                    string word;
                    iss >> word;

                    my_words[word.length()].insert(word);
                }
            }
        }

        for(auto &x:my_words) {
            cout << x.first << " ";
            for(auto &y:x.second) {
                cout << y << " ";
            }

            cout << endl;
        }
    }
}