#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

using namespace std;

class ChessBoardArray {
protected:
    class Row {
    public:
        Row(ChessBoardArray &a, int i): chessy(a), row(i) {}

        int & operator [] (int i) {
            return chessy.select(row,i);
        }

    private:
        ChessBoardArray & chessy;
        int row;
    };
    class ConstRow {
    public:
        ConstRow(const ChessBoardArray &a, int i) : chesser(a), rower(i) {}

        int operator [] (int i) const {
            return chesser.select(rower,i);
        }

    private:
        const ChessBoardArray & chesser;
        int rower;
    };
public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) {
        num=size;
        cbase=base;
        int a;
        if(num%2==0) {
            a=num*num/2;
        }
        else {
            a=num*num/2+1;
        }
        data=new int[a];
        for(int i=0; i<a; i++) {
            data[i]=0;
        }
    }

    ChessBoardArray(const ChessBoardArray &a) {
         num=a.num;
         cbase=a.cbase;
         int sk;
        if(num%2==0) {
            sk=num*num/2;
        }
        else {
            sk=num*num/2+1;
        }
        data = new int[sk];
         for(int i=0; i<sk; i++) {
             data[i]=a.data[i];
         }
    }

    ~ChessBoardArray() {
        delete [] data;
        data=nullptr;
    }

    ChessBoardArray & operator = (const ChessBoardArray &a) {
        delete [] data;
        data=nullptr;
        num=a.num;
        cbase=a.cbase;
        int sk;
        if(num%2==0) {
            sk=num*num/2;
        }
        else {
            sk=num*num/2+1;
        }
        data = new int[sk];
        for(int i=0; i<sk; i++) {
            data[i]=a.data[i];
        }

        return *this;
    }

    int & select(int i, int j) {
        return data[loc(i,j)];
    }

    int select(int i, int j) const {
        return data[loc(i,j)];
    }

    Row operator [] (int i) {
        return Row(*this,i);
    }
    const ConstRow operator [] (int i) const {
        return  ConstRow(*this,i);
    }

    friend ostream & operator << (ostream &out, const ChessBoardArray &a){
        for(int i=a.cbase; i<a.cbase+a.num; i++){
            for(int j=a.cbase; j<a.cbase+a.num; j++) {
                try {
                    out << setw(4) << a[i][j] ;
                }
                catch(out_of_range & e) {
                   out << setw(4) << 0;
               }
            }
            out << endl;
        }
        return out;
    }

private:
    unsigned int loc (int i, int j) const {
          int di=i-cbase;
          int dj=j-cbase;
          if(di<0 || dj>=num || dj<0 || di>=num) {
              throw out_of_range("invalid index");
          }
          int calc=pow(-1,di+dj);
          if(calc<0) {
              throw out_of_range("invalid index");
          }
          return (di*num+dj)/2;

    }

    int * data;

    unsigned  cbase;

    unsigned num;

};




























































































































































































