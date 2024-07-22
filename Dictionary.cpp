#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>

using namespace std;


int main () {
    int N, D;
    cin >> N >> D;
    vector<set<string>> all_the_books(D+1);
    map<string, set<int>> common_words;

    for(int i=0; i<N; i++) {
        int d;
        string w;
        cin >> d >> w;
        all_the_books[d].insert(w);
        common_words[w].insert(d);
    }

    int largest = all_the_books[1].size();
    int index = 1;
    for(int i=2; i<=D; i++) {
        int y = all_the_books[i].size();
        if(largest < y) {
            largest = y;
            index = i;
        }
    }

    cout << index << " " << largest << endl;

    int count = 0;
    for(auto & x:common_words) {
        if(x.second.size() == D) {
            cout << x.first << endl;
            count ++;
        }
    }

    cout << count << endl;
}
