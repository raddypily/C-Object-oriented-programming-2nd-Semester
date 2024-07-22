#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

class Gas {
public:
    Gas(int v, int i): vertices(v), edges(i), adj(vertices+1) {}

    ~Gas() {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    void Answer(int A, int B, int C) {
        int refills = 1;
        vector<int> small_path = Shortest_Path(A, B, C, refills);

        if (small_path.empty()) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE: " << refills << " fill(s), ";
            for (size_t i = 0; i < small_path.size(); ++i)
                cout << small_path[i] << (i == small_path.size() - 1 ? "\n" : " ");
        }
    }

private:
    int vertices;
    int edges;
    vector<vector<pair<int,int>>> adj;

    //Dijkstra
    vector<int> Shortest_Path(int Source, int Target, int C, int & refills) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(vertices+1, 1e9), parent(vertices+1);

        for(int i=0; i<vertices; i++) parent[i] = i;

        dist[Source] = 0;

        pq.push({0, Source});

        int remaining_fuel = C;

        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int dis = it.first;

            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int edW = it.second;

                if (dis + edW < dist[adjNode])
                {
                    if(remaining_fuel - edW > 0) {
                        dist[adjNode] = dis + edW;
                        pq.push({dis + edW, adjNode});

                        parent[adjNode] = node;

                        remaining_fuel -= edW;
                    }
                    else {
                        if(C -edW > 0) {
                           remaining_fuel = C - edW;
                           refills++;

                            dist[adjNode] = dis + edW;
                            pq.push({dis + edW, adjNode});

                            parent[adjNode] = node;
                        }
                    }
                }
            }
        }
        if (dist[Target] == 1e9)
            return {-1};

        vector<int> path;
        int node = Target;

        while (parent[node] != node)
        {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(Source);

        reverse(path.begin(), path.end());
        return path;
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
