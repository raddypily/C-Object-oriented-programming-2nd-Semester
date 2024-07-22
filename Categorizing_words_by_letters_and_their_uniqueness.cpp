#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool nickie1(const string & w1, const string & w2) {
    if(w1.length() == w2.length()) {
        return w1 > w2;
    }
    else {
        return w1.length() < w2.length();
    }
}

int main () {
    string line;
    map<char, int> all_the_words;
    map<char, set<string>> unique_words;
    char first_letter;

    while(getline(cin, line)) {
        istringstream iss;
        iss.clear();

        iss.str(line);
        string words;

        while(iss.good()) {

            iss >> words;
            first_letter = *words.begin();
            if (all_the_words[first_letter]) {

                all_the_words[first_letter]++;

                auto term = unique_words[first_letter].find(words);

                if (term == unique_words[first_letter].end()) {
                    unique_words[first_letter].insert(words);
                }
            } else {
                unique_words[first_letter].insert(words);
                all_the_words[first_letter]++;
            }
        }
    }

    for(auto & x:all_the_words) {
        cout << x.first << " " << x.second << " " ;

        vector<string> term;
        for(auto & y: unique_words[x.first]) {
            term.emplace_back(y);
        }

        sort(term.begin(), term.end(), nickie1);

        cout << term[term.size()-1] << " " ;

        int size = term[0].length();

        int i=1;
        for(i; i<term.size(); i++) {
            if(size != term[i].length()) {
                break;
            }
        }

        cout << term[--i] << endl;
    }
}
