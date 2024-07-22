#include <iostream>
#include <list>
#include <string>
#include <stack>
#include <stdexcept>

using namespace std;

int main () {
    int N, number;
    cin >> N;
    list<int> q;
    stack<int> s;

    for(int i = 0; i < N; i++) {
        cin >> number;
        q.push_back(number);
    }

    string actions;
    cin >> actions;

    try {
        for (auto &c: actions) {
            if (c == 'Q') {
                if (q.empty()) {
                    throw "e";
                }
                int result = q.front();
                q.pop_front();

                s.push(result);
            } else if (c == 'S') {
                if (s.empty()) {
                    throw "e";
                }
                int result = s.top();
                s.pop();

                q.push_back(result);
            } else {
                for (list<int>::iterator p = q.begin(); p != q.end(); p++) {
                    if (p == --q.end()) {
                        cout << *p << endl;
                    } else {
                        cout << *p << " ";
                    }
                }
            }
        }
    }
    catch(const char * e) {
        cout << "error" << endl;
    }
}
