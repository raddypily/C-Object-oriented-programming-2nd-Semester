#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool john(const pair<string, int> & x1, const pair<string, int> & x2) {
    return x1.second > x2.second;
}

int main () {
    int requested;
    cin >> requested;

    map<string, set<int>> people;
    vector<pair<string, int>> job;

    string line;
    string movie;
    string viewer;
    int rating;
    istringstream iss;

    while(getline(cin, line)) {
         iss.clear();
         iss.str(line);

         while(iss.good()) {
            iss >> movie >> viewer >> rating;

            if(rating < 0 || rating > 100) {
                break;
            }

            people[viewer].insert(rating);
         }
    }

    for(auto & x:people) {
        job.emplace_back(make_pair(x.first, x.second.size()));
    }

    sort(job.begin(), job.end(), john);

    for(auto & x:job) {
        cout << x.first << " " << x.second << endl;
    }
}