#include "iostream"
#include <stdexcept>

using namespace std;

template <typename T>
class List {
    public:

    List(): sum(0), head(nullptr), rear(nullptr) {}

    void Add_A_Node(T i) {
        sum++;

        if(head == nullptr) {
            node *p = new node(i, nullptr, nullptr);

            head = p;
            rear = p;
        }
        else {
            node *q = head;
            while (i > q->info) {
                q = q->next;
                if (q == nullptr) {
                    break;
                }
            }
            node *p;

            if (q == nullptr) {
                p = new node(i, nullptr, rear);
                rear->next = p;

                rear = p;
            } else if (q->previous == nullptr) {
                p = new node(i, head, nullptr);
                head->previous = p;

                head = p;
                return;
            }
            else {
                p = new node(i, q, q->previous);

                q->previous->next = p;
            }
        }
    }

    int summed() {
        return sum;
    }

    friend ostream & operator <<(ostream &out, const List &l) {
        node *p = l.head;
        while(p != nullptr) {
            out << p->info << endl;
            p = p->next;
        }

        return out;
    }

    T operator[] (int i) {
        node *p = head;
        int count = 0;

        while(count != i) {
            count++;
            p = p->next;
        }

        return p->info;
    }

    List operator +(const List &l) {
        if(sum == l.sum) {
            List result;

            node *p = head;
            node *q = l.head;
            while(p != nullptr) {
                result.Add_A_Node(p->info+q->info);

                p = p->next;
                q = q->next;
            }

            return result;
        }
        else {
            throw out_of_range("Not possible!");
        }
    }

    private:
    int sum;
    struct node {
        T info;
        node *next;
        node *previous;
        node(T i, node *p, node *q) {
            info = i;
            next = p;
            previous = q;
        }
    };

    node *head;
    node *rear;
};

int main () {
    List<int> l;
    List<int> s;

    for(int i = 0; i < 5; i ++) {
        l.Add_A_Node(5-i);

        int num;
        cin >> num;
        s.Add_A_Node(num);
    }

    cout << s;

     try {
         cout << l+s;
     }
     catch(out_of_range &e) {
         cout << e.what() << endl;
     }
}