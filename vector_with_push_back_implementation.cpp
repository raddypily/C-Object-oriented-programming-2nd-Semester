#include "iostream"
#include <stdexcept>

using namespace std;

class Vector {
    private:
    int *v;
    int size;
    int max_size;

    public:
    Vector(int sz, int val = 0) {
        size = sz;
        max_size = sz;

        v = new int[size];
        for(int i = 0; i < size; i++) {
            v[i] = val;
        }
    }

    Vector(const Vector &x) {
        size = x.size;
        v = new int[size];

        for(int i = 0; i < size; i++) {
            v[i] = x.v[i];
        }
    }

    ~Vector() {
        delete []v;
        v = nullptr;
    }

    Vector operator+(const Vector &x) {
        if(size != x.size) {
            throw logic_error("Not possible!");
        }
        else {
            Vector result(size);

            for(int i = 0; i < size; i++) {
                result.v[i] += x.v[i] + v[i];
            }

            return result;
        }
    }

    const Vector& operator =(const Vector &x) {
        delete []v;

        size = x.size;
        v = new int[size];

        for(int i = 0; i < size; i++) {
            v[i] = x.v[i];
        }

        return *this;
    }


    int operator [](int k) const {
        if(k >= size) {
            throw out_of_range("Not possible!");
        }
        else {
            return v[k];
        }
    }

    friend ostream& operator <<(ostream &out, const Vector &x) {
        for(int i = 0; i < x.size; i++) {
            out << x.v[i] << endl;
        }

        return out;
    }

    void Push_Back(int x) {
        if(max_size == size) {
            int *term = new int[size];

            for(int i = 0; i < size; i++) {
                term[i] = v[i];
            }

            max_size *= 2;

            delete []v;

            v = new int[max_size];

            for(int i = 0; i < size; i++) {
                v[i] = term[i];
            }

            v[size++] = x;
        }
        else {
            v[size++] = x;
        }
    }
};

int main () {
    Vector v(5, 5);

    v.Push_Back(6);
    v.Push_Back(7);

    cout << v ;
}