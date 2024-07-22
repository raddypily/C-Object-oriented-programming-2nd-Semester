#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <set>
#include <list>


using namespace std;

bool john(pair<int,int> p1, pair<int,int> p2) {
    return p1.second > p2.second;
}

class Graph {
public:
    Graph(int v) : adj({}), nodes({}), vertices(v) {}

    ~Graph() {}

    void addEdge(int u, int v) {
        set<int>::iterator r;
        r = nodes.find(u);

        if (r == nodes.end()) {
            nodes.insert(u);
        }

        r = nodes.find(v);

        if (r == nodes.end()) {
            nodes.insert(v);
        }
        map<int, set<int>>::iterator p;
        p = adj.find(u);

        if (p == adj.end()) {
            p = adj.find(v);
            if (p == adj.end()) {
                adj[u].insert(v);
            } else {
                set<int> term = p->second;
                set<int>::iterator help;

                help = find(term.begin(), term.end(), u);

                if (help == term.end()) {
                    adj[u].insert(v);
                }
            }
        } else {
            p = adj.find(v);
            if (p == adj.end()) {
                adj[u].insert(v);
            } else {
                set<int> term = p->second;
                set<int>::iterator help;

                help = find(term.begin(), term.end(), u);

                if (help == term.end()) {
                    adj[u].insert(v);
                }
            }
        }
    }


    bool cycle(vector<int> &path) {
        Graph Reverse = Alternate();
        Reverse.DFS_Special();

        vector<pair<int,int>> term;

        for(auto & x:Reverse.timings) {
            term.push_back(make_pair(x.first, x.second));
        }

        sort(term.begin(), term.end(), john);

        vector<int> help;

        for(auto & x : term) {
            help.push_back(x.first);
        }


        DFS(path, help);

        if (path.empty()) {
            return false;
        }

        vector<int> n_path = path;

        list<int> helpful;


        helpful.push_front(n_path.back());

        n_path.pop_back();

        helpful.push_front(n_path.back());

        n_path.pop_back();

        while(helpful.front() != path.back()) {
            helpful.push_front(n_path.back());
            n_path.pop_back();
        }

        helpful.pop_front();


        vector<int> for_the_lat_time;

        for(auto & x:helpful) {
            for_the_lat_time.push_back(x);
        }

        path = for_the_lat_time;

        return true;
    }

    Graph Alternate() {
        Graph g(vertices);

        for (auto &x: adj) {
            for (auto &y: x.second) {
                g.addEdge(y, x.first);
            }
        }
        return g;
    }

private:
    int vertices;

    set<int> nodes;

    map<int,set<int>> adj;

    map<int, int> timings;

    map<int, int> status;

    void DFS(vector<int> &path, vector<int> & help) {
        bool found_back_edge = false;
        for (auto &x: nodes) {
            status[x] = 0;
        }
        int y = help[0];
        vector<int>::iterator p = --help.end();
        while(true) {
            int time = 0;
            vector<int> path_term;
            map<int, int> times_term;
            DFS_Help(y, path_term, found_back_edge);


            if(found_back_edge) {
                path = path_term;


                return;
            }
            else {
                vector<int>::iterator q = --path_term.end();
                if(*q == *p) {
                    return;
                }
                else {
                    vector<int>::iterator e = find(help.begin(), help.end(), *q);
                    e++;
                    y = *e;
                }
            }
        }
    }

    void DFS_Help(int x, vector<int> & path, bool & found_back_edge) {
        if(status[x] == -1) {
            found_back_edge = true;
            path.push_back(x);
            return;
        }

        status[x] = -1; // SEEN
        if(!found_back_edge) {
            path.push_back(x);
        }

        set<int> term = adj[x];

        for(auto & y:  term) {
            if(status[y] != 1) {
                DFS_Help(y, path, found_back_edge);
            }
            if(found_back_edge) {
                return ;
            }
        }
        status[x] = 1;
    }

    void DFS_Special() {
        for (auto &x: nodes) {
            status[x] = 0;
        }
        int time = 0;
        for (const auto &x: nodes) {
            if (status[x] == 0) {
                DFS_Help_Special(x, time);
            }
        }
    }

    void DFS_Help_Special(int v, int &time) {
        ++time;
        status[v] = 1;

        set<int> term = adj[v];

        for (auto &x: term) {
            if (status[x] == 0) {
                DFS_Help_Special(x, time);
            }
        }

        timings[v] = ++time;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for (int i = 0; i<E; ++i) {
        int u, v; cin >> u >> v; g.addEdge(u, v);
    }
    vector<int> path;
    bool c = g.cycle(path);
    if (c) {
        cout << "CYCLE: ";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] << (i == path.size()-1 ? "\n" : " ");
    } else {
        cout << "NO CYCLE" << endl;
    }
    return 0;
}

