#include <iostream>
#include <vector>
#include <set>

using namespace std;
class UnDirected {
public:
    UnDirected(int &N): vertices(N), adj(N), values({}) {}

    void Add_Edge(int &U, int &V) {
         adj[U].insert(V);
         adj[V].insert(U);
    }

    void Add_Value(int  & v) {
        values.emplace_back(v);
    }

    int Find_Triangles(int & L, int & U) {
        int counting = 0;

        for(int i = 0; i < vertices; i++) {
            if(values[i] >= U) {
                continue;
            }
                for (auto &x: adj[i]) {
                    if(i < x) {
                        continue;
                    }
                    if(values[i] + values[x]>= U) {
                        continue;
                    }
                        for(auto & y:adj[x]) {
                            if(x < y) {
                                continue;
                            }
                            for(auto & z:adj[y]) {
                                if(z == i) {
                                    if(values[i] + values[x] + values[y] >= L && values[i] + values[x] + values[y]<= U) {
                                        counting++;
                                    }
                                    break;
                                }
                            }
                        }
                    }
        }

        return counting;
    }

private:
    vector<set<int>> adj;
    vector<int> values;
    int vertices;
};

int main () {
    int N, M, L, U;
    cin >> N >> M >> L >> U;

    UnDirected g(N);

    for(int i = 0; i < N; i++) {
        int v;
        cin >> v;

        g.Add_Value(v);
    }

    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g.Add_Edge(u, v);
    }

    cout << g.Find_Triangles(L, U) << endl;
}