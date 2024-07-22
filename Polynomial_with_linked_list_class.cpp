#include "iostream"
#include <cmath>

using namespace std;

class Polynomial {
    private:
    struct node {
        int coefficient;
        int exponent;
        node *next;
        node *previous;
        node(int c, int e, node *p, node *q) {
            coefficient = c;
            exponent = e;
            next = p;
            previous = q;
        }
    };

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

    void copy(const Polynomial& P) {
        front = rear = nullptr;

        node *q = P.front;

        node *term = new node(q->coefficient, q->exponent, nullptr, q->previous);

        front = rear = term;

        q = q->next;

        while(q != nullptr) {
            node *t = new node(q->coefficient, q->exponent, nullptr, q->previous);

            rear->next = t;

            rear = t;

            q = q->next;
        }
    }

    public:
    Polynomial() {
        front = rear = nullptr;
    }

    ~Polynomial() {
        purge();
    }

    Polynomial(const Polynomial &p) {
        copy(p);
    }

    const Polynomial & operator =(const Polynomial &p) {
        purge();
        copy(p);

        return *this;
    }

    void AddTerm(int coeff, int expon) {
        if(front == nullptr) {
            node *p = new node(coeff, expon, nullptr, nullptr);

            front = rear = p;
        }
        else {
            node *p = front;

            while(p != nullptr && p->exponent > expon) {
                p = p->next;
            }

            if(p == nullptr) {
                node *t = new node(coeff, expon, nullptr, rear);

                rear->next = t;

                rear = t;
            }
            else {
                if(p->exponent == expon) {
                    p->coefficient += coeff;
                    if(p->coefficient == 0) {
                        node *z = p->previous;

                        z->next = p->next;

                        p->next->previous = z;

                        delete p;
                    }
                }
                else {
                    if(p != front) {
                        node *t = new node(coeff, expon, p, p->previous);

                        p->previous->next = t;
                    }
                    else {
                        node *t = new node(coeff, expon, front, nullptr);

                        front->previous = t;

                        front = t;
                    }
                }
            }
        }
    }

    friend ostream& operator <<(ostream &out, const Polynomial &p) {
        node *q = p.front;

        out << q->coefficient << "x" << "^" << q->exponent << " ";
        q = q->next;

        while(q != nullptr) {
            if(abs(q->coefficient) == 1) {
                if(q->coefficient < 0) {
                    out << "-" << " " << "x" << "^" << q->exponent << " ";
                }
                else {
                    out << "+" << " " << "x" << "^" << q->exponent << " ";
                }
            }
            else {
                if(q->coefficient < 0) {
                    out << "-" << " " << abs(q->coefficient) << "x" << "^" << q->exponent << " ";
                }
                else {
                    out << "+" << " " << abs(q->coefficient) << "x" << "^" << q->exponent << " ";
                }
            }

            q = q->next;
        }

        out << endl;
        return out;
    }

    double evaluate(double x) {
        double result = 0;

        node *q = front;

        while(q != nullptr) {
            result += q->coefficient*pow(x, q->exponent);

            q = q->next;
        }

        return result;
    }

    Polynomial operator +(const Polynomial &p) {
        Polynomial result;

        node *t1 = front;
        node *t2 = p.front;

        while (t1 != nullptr && t2 != nullptr) {
            if (t1->exponent == t2->exponent) {
                if (t1->coefficient + t2->coefficient != 0) {
                    result.AddTerm(t1->coefficient + t2->coefficient, t1->exponent);
                }

                t1 = t1->next;
                t2 = t2->next;
            } else if (t1->exponent < t2->exponent) {
                result.AddTerm(t2->coefficient, t2->exponent);
                t2 = t2->next;
            } else {
                result.AddTerm(t1->coefficient, t1->exponent);
                t1 = t1->next;
            }
        }

        if (t1 == nullptr && t2 == nullptr) {
            return result;
        } else {
            if (t1 == nullptr) {
                while (t2 != nullptr) {
                    result.AddTerm(t2->coefficient, t2->exponent);
                    t2 = t2->next;
                }
            } else {
                while (t1 != nullptr) {
                    result.AddTerm(t1->coefficient, t1->exponent);
                    t1 = t1->next;
                }
            }
        }
        return result;
    }

    Polynomial operator*(const Polynomial &p) {
        Polynomial result;

        node *p1 = front;

        while(p1 != nullptr) {
            node *p2 = p.front;
            while(p2 != nullptr) {
                result.AddTerm(p1->coefficient*p2->coefficient, p1->exponent+p2->exponent);

                p2 = p2->next;
            }

            p1 = p1->next;
        }

        return result;
    }
};

int main () {
    Polynomial p;
    p.AddTerm(3,5);

    p.AddTerm(3,6);

    p.AddTerm(3, 4);

    Polynomial q(p);


    Polynomial z;

    z.AddTerm(-3, 6);

    cout << z;

    cout << p*z;
}