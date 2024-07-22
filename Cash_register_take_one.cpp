#include "iostream"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Purchase {
    private:
    struct node {
        string item;
        vector<int> prices;
        node *next;
        node(string i, vector<int> p, node *t) {
            item = i;
            prices = p;
            next = t;
        }
    };
    node *head, *rear;

    void purge() {
        node *p = head;
        while(p != nullptr) {
            node *q = p;
            p = p->next;

            delete q;
        }

        head = rear = nullptr;
    }
    public:
    Purchase(): head(nullptr), rear(nullptr) {}

    ~Purchase () {purge();}

    void Add(string i, int p) {
        if(head == nullptr) {
            vector<int> term;
            term.emplace_back(p);
            node *p = new node(i, term, nullptr);

            head = rear = p;
        }
        else {
            node *q = head;

            while(q != nullptr && q->item != i) {
                q = q->next;
            }
            if(q == nullptr) {
                vector<int> term;
                term.emplace_back(p);
                node *p = new node(i, term, nullptr);
                
                rear->next = p;

                rear = p;
            }
            else {
                q->prices.emplace_back(p);
            }
        }
    }

    int Total() {
        int result = 0;
        node *q = head;

        if(head == nullptr)  {
            return result;
        }
        else {
            while(q != nullptr) {
                cout << q->item << " " << q->prices.size() << " " << q->prices.front() << endl;

                for(int i = 0; i < q->prices.size(); i++) {
                    result += q->prices[i];
                }

                q = q->next;
            }

            return result;
        }
    }
};

int main () {
    Purchase P;

    string line;
    istringstream iss;

    while(getline(cin, line)) {
        iss.clear();
        iss.str(line);

        while(iss.good()) {
            string word;
            int pr;
            iss >> word >> pr;

            P.Add(word, pr);
        }
    }

    cout << P.Total() << endl;
}