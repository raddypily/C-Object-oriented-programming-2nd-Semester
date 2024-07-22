#include <iostream>
#include <map>
#include <vector>
#include <utility>


using namespace std;

class Gas {
public:
    Gas(int n, int v) : nodes(n), vertices(v), adj({}) {}

    ~Gas() {}

    void addEdge(int u, int v, int L) {
        adj[u].insert(make_pair(v, L));
        adj[v].insert(make_pair(u,L));
    }

    void Answer(int A, int B, int C) {
        int gas = C;
        int refills = 1;
        int real_refills;

        map<int,int> status;

        for(map<int, map<int,int>>::iterator p = adj.begin(); p != adj.end(); p++) {
            status[p->first] = 0;
        }

        vector<int> path;
        vector<int> right_path;

        path.push_back(A);
        bool found = false;
        DFS(right_path, A, B, path, status, gas, refills, C, found, real_refills);

        if(!found) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << "POSSIBLE: " << real_refills << " fill(s), ";
            for (size_t i = 0; i < right_path.size(); ++i)
                cout << right_path[i] << (i == right_path.size()-1 ? "\n" : " ");
        }
    }
private:
    int nodes;
    int vertices;
    map<int, map<int, int>> adj;

    void DFS(vector<int> & right_path, int u, int B, vector<int> path, map<int, int> & status, int gas, int refills, int C, bool & found, int & real_refills) {
        if (found) {
            return;
        }

        status[u] = 1;

        if (u == B) {
            right_path = path;

            real_refills = refills;

            found = true;
            return;
        } else {
            for (map<int, int>::iterator w = adj[u].begin(); w != adj[u].end(); w++) {
                if (status[w->first] == 0) {
                    int term_gas = gas;
                    int term_ref = refills;

                    if (gas - w->second < 0) {
                        if (gas == C) {
                            continue;
                        } else {
                            if (C - w->second < 0) {
                                continue;
                            }
                            term_gas = C - w->second;
                            term_ref++;
                        }
                    } else {
                        term_gas -= w->second;
                    }

                    status[w->first] = 1;

                    path.push_back(w->first);

                    DFS(right_path, w->first, B, path, status, term_gas, term_ref, C, found, real_refills);

                    if (found) {
                        return;
                    }

                    path.pop_back();

                }
            }
        }
        status[u] = 0;
    }
};

int main () {
    int N, M, U, V, L, Q, A, B, C;
    cin >> N >> M;
    Gas nickie(N, M);

    for(int i=0; i <M; i++) {
        cin >> U >> V >> L;
        nickie.addEdge(U, V, L);
    }

    cin >> Q;

    for(int i=0; i<Q; i++) {
        cin >> A >> B >> C;
        nickie.Answer(A,B,C);
    }
}