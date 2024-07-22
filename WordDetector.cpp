#include "iostream"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int main () {
    map<string, int> unique_words;
    istringstream iss;
    ifstream inFile;

    inFile.open("words.txt");
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

                    unique_words[word] = 0;
                }
            }
        }
    }

    inFile.close();
    set<string> unknown;

    inFile.open("input.txt");
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
                    
                    auto it = unique_words.find(word);

                    if(it != unique_words.end()) {
                        it->second++;
                    }
                    else {
                        unknown.insert(word);
                    }
                }
            }
        }
    }

    inFile.close();

    for(auto &x:unique_words) {
        if(x.second != 0) {
            cout << x.first << " " << x.second << endl;
        }
    }

    cout << unknown.size() << endl;
}