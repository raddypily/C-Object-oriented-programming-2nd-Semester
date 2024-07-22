#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Undirected_Graph {
public:
    Undirected_Graph(int & N): adj(N), identity(N), vertices(N) {}

    void Add_Edge(int U, int V) {
        adj[U].insert(V);
    }

    void Add_Letters(string & c, int & index) {
        identity[index] = c;
    }

    int Paths_Of_Two() {
        int counting = 0;

        for(int i = 0; i < vertices; i++) {
            for(auto & y:adj[i]) {
                if(identity[i] != identity[y]) {
                    continue;
                }
                for(auto &z:adj[y]) {
                    if(identity[i] != identity[z]) {
                        continue;
                    }
                    counting++;
                }
            }
        }

        return counting;
    }


private:
    vector<set<int>> adj;
    vector<string> identity;
    int vertices;
};

int main () {
    int N, M;
    cin >> N >> M;
    Undirected_Graph G(N);

    cin.ignore();
    string line;
    getline(cin, line);

    istringstream iss;
    iss.clear();

    iss.str(line);

    for(int i = 0; i < N; i++) {
        string c;
        iss >> c;
        G.Add_Letters(c, i);
    }

    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        G.Add_Edge(u, v);
    }

    cout << G.Paths_Of_Two() << endl;
}
