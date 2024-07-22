#include "iostream"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Purchase {
    public:
    Purchase() {
        front = rear = nullptr;
        tot = 0;
    }

    ~Purchase () {
        purge();
    }

    void Add_Node(string i, int p) {
        tot += p;

        if(front == nullptr) {
            vector<int> term;
            term.emplace_back(p);

            node *pt = new node(term, i, nullptr, p);

            front = rear = pt;
        }
        else {
            node *pt = front;

            while(pt != nullptr && pt->item_name != i) {
                pt = pt->next;
            }

            if(pt == nullptr) {
                vector<int> term;
                term.emplace_back(p);

                node *pt = new node(term, i, nullptr, p);

                rear->next = pt;

                rear = pt;
            }
            else {
                pt->prices.emplace_back(p);
                pt->t += p;
            }
        }
    }

    int Total() {
        return tot;
    }

    friend ostream& operator << (ostream &out, const Purchase &p) {
        node *q = p.front;

        while(q != nullptr) {
            out << q->item_name << " " << q->prices.size() << " " << q->prices.front() << " " << q->t << endl;
            q = q->next;
        }

        return out;
    }

    private:
    struct node {
        vector<int> prices;
        int t;
        string item_name;
        node *next;
        node(vector<int> p, string i, node *n, int y) {
            prices = p;
            item_name = i;
            next = n;
            t = y;
        }
    };

    int tot;

    node *front, *rear;

    void purge() {
        node *p = front;

        while(p != nullptr) {
            node *term = p;

            p = p->next;

            delete term;
        }

        front = rear = nullptr;
    }
};

int main () {
    Purchase p;
    istringstream iss;
    string line;

    while(getline(cin, line)) {
        iss.clear();
        iss.str(line);
        while(iss.good()) {
            string item;
            int pr;
            iss >> item >> pr;
            p.Add_Node(item, pr);
        }
    }

    cout << p;
    cout << p.Total() << endl;
}

