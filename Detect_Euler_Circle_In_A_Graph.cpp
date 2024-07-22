#include <iostream>
#include <vector>
#include <map>

using namespace std;

class nonDirected {
public:
    nonDirected(): adj({}) {}

    void addEdge(int f, int t) {
        adj[f].push_back(t);
        adj[t].push_back(f);
    }

    bool Euler_Circuit() {
        bool found = true;
        for(auto const & term : this->adj) {
            if(term.second.size() % 2 != 0) {
                found = false;
                break;
            }
        }
        if(!found) {
           return found;
        }
        return found;
    }

    vector<int> Euler_Path() {
        vector<int> passenger;
        vector<int> empty_vector;

        int count = 0;
        int N;
        bool found1 = false;

        int M;
        bool found2 = false;

        for (auto const &term: this->adj) {
            if (term.second.size() % 2 != 0) {
                count++;
                if(!found1) {
                    N = term.first;
                    found1 = true;
                    continue;
                }
                if(!found2) {
                    M = term.first;
                    found2 = true;
                }
            }
        }

        if(count == 2) {
            if(N < M) {
                passenger.emplace_back(N);
                passenger.emplace_back(M);
            }
            else {
                passenger.emplace_back(M);
                passenger.emplace_back(N);
            }
            return passenger;
        }
        return empty_vector;
    }

private:
    map<int,vector<int>> adj;
};

int main () {
    nonDirected graph_euler;

    int N;
    int M;
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int u;
        int v;
        cin >> u >> v;
        graph_euler.addEdge(u, v);
    }

    if(!graph_euler.Euler_Circuit()) {
        vector<int> term;
        term = graph_euler.Euler_Path();

        if(term.empty()) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << "PATH " << term[0] << " " << term[1] << endl;
        }
    }
    else {
        cout << "CYCLE" << endl;
    }
}