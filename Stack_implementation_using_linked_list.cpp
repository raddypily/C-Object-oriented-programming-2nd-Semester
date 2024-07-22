#include "iostream"

using namespace std;

template<typename T>

class stack {
    public:  
		stack (): head(nullptr), siz(0) {}

		stack (stack &s) {
            copy(s);
        }  

		~stack () {
            purge_all();
        }  

        const stack& operator = (const stack &s) {
            purge_all();

            copy(s);

            return *this;
        }  

		bool empty () {
            return siz == 0;
        }  

		void push (const T &x) {
            if(head == nullptr) {
                node *p = new node(x, nullptr);
                head = p;
            }
            else {
                node *p = new node(x, head);

                head = p;
            }
            siz--;
        }



		T pop () {
                int result;
                node *p = head;
                result = p->info;
                head = head->next;
                
                siz--;
                return result;
        }

		int size () {
            return siz;
        }

		friend ostream & operator << (ostream &out, const stack &s) {
            node *q = s.head;

            while(q != nullptr) {
                cout << q->info << endl;
                q = q->next;
            }

            return out;
        } 

    private:
    int siz;
    struct node {
        T info;
        node *next;
        node(T i, node * t) {
            info = i;
            next = t;
        }
    };

    void purge_all() {
        node *p = head;
        while(p != nullptr) {
            node * q = p;
            p = p->next;
            delete q;
        }

        siz = 0;
    }

    void copy(const stack &s) {
        head = nullptr;
        siz = 0;

        node *p = s.head;
        while(p != nullptr) {
            push(p->info);
            p = p->next;
        }
    }

    node *head;
};

int main () {
    stack<int> S;

    for(int i = 0; i < 5; i++) {
        S.push(i);
    }

    cout << S;

    stack<int> SP;

    for(int i = 0; i < 5; i++) {
        SP.push(i+1);
    }

    SP = S;

    cout << SP;
}