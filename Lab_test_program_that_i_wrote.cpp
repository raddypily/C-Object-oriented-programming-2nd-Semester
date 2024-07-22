//
// Created by radpi on 5/20/2024.
//
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main () {
    istringstream iss;
    string line;

    vector<vector<string>> my_text;   //all the text

    vector<string> my_words;   // first words

    while (getline(cin, line)) {
        vector<string> my_line;
        string word;
        iss.clear();

        iss.str(line);

        while (iss.good()) {
            iss >> word;

            my_line.emplace_back(word);   //put each word in line, in my_line vector
        }

        my_words.emplace_back(my_line[0]); //first word


        my_text.emplace_back(my_line);
    }

    set<string> unique;

    if (my_text.size() > 2) {
        for (int i = 0; i < my_words.size() - 2; i++) {
                if(my_words[i].empty()) {
                    continue;
                }
            vector<string>::iterator p = find(my_text[i+2].begin(), my_text[i+2].end(), my_words[i]);

            if(p != my_text[i+2].end()) {
                unique.insert(*p);
            }
        }
    }

    if(unique.empty()) {
        cout << "NONE FOUND" << endl;
    }
    else {
        for(auto &x:unique) {
            cout << x << endl;
        }
    }
}