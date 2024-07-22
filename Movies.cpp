#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <utility>

using namespace std;

bool john (pair<string, int> & p1, pair<string, int> & p2) {
    if(p1.second == p2.second) {
        return p1.first < p2.first;
    }

    return p1.second > p2.second;
}

int main () {
    int N, requested;
    cin >> N >> requested;

    map<string, string> genres;
    map<string, set<int>> votes;
    vector<pair<string, int>> job;


    for(int i=0; i<N; i++) {
        string name, genre;
        cin >> name >> genre;

        genres[name] = genre;
    }

    istringstream iss;
    string line, movie;
    int rating;

    while(getline(cin, line)) {
        iss.clear();
        iss.str(line);
        while(iss.good()) {
            iss >> movie;
            iss.ignore(8);
            iss >> rating;

            auto term = genres.find(movie);

            if(term == genres.end()) {
                break;
            }

            if(rating < 0 || rating > 100) {
                break;
            }

            votes[genres[movie]].insert(rating);
        }
    }

    for(auto & x:votes) {
        pair<string, int> term;
        term.second = 0;
        int size;

        size = x.second.size();
        for(auto & y:x.second) {
            term.second += y;
        }

        term.second /= size;

        job.emplace_back(term);
    }

    for(int i=0; i<requested; i++) {
        cout << job[i].first << " " << job[i].second << endl;
    }
}
