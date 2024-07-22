#include "iostream"
#include <stdexcept>

using namespace std;

class my_vector {
public:
    my_vector(int val = 0, int sz = 0): size(sz) {
        vector = new int[size];
        for(int i = 0; i < size; i++) {
            vector[i] = val;
        }
    }

    ~my_vector() {
        delete []vector;
        vector = nullptr;
    }

    my_vector(const my_vector & x) {
        size = x.size;

        vector = new int[size];
        for(int i = 0; i < size; i++) {
            vector[i] = x.vector[i];
        }
    }

    const my_vector & operator = (const my_vector & x) {
        delete []vector;

        size = x.size;
        vector = new int[size];
        for(int i = 0; i < size; i++) {
            vector[i] = x.vector[i];
        }

        return *this;
    }

    my_vector operator + (my_vector & x) {
        my_vector Term(0, size);

        if(size != x.size) {
            throw "not good";
        }

        for(int i = 0; i < size; i++) {
            Term.vector[i] = vector[i] + x.vector[i];
        }

        return Term;
    }

    int & operator [] (int k) {
        if(k >= size) {
            throw "not good";
        }

        return vector[k];
    }

    const int & operator [] (int k) const {
        if(k >= size) {
            throw "not good";
        }

        return vector[k];
    }

    friend ostream & operator << (ostream & out, const my_vector & x) {
        for(int i = 0; i < x.size; i++) {
            if(i == x.size - 1) {
                out << x[i] << endl;
            }
            else {
                out << x[i] << " ";
            }
        }

        return out;
    }

    int & operator *(my_vector & x) {
        int sum = 0;
        if(x.size != size) {
            throw logic_error("my bad");
        }


    }

private:
    int size;
    int * vector;
};

