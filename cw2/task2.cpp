#include <iostream>
#include <new>
using namespace std;
#define N 5

class A
{
    int a;
    ~A(){cout << "destr\n"; }
public:
    A(int b = 5);
    static A *arr(int n = N);
    static A arStat[N];
    void print() const;
};

A A::arStat[N];

A::A(int b){
    a = b;
}

A* A::arr(int n){
    A *ar = new(&arStat) A[n];
    return ar;
}

void A::print() const{
    cout << a << endl;
}


int main()
{
    A *ar = A::arr();
    for(int i = 0; i < N; i++)
        ar[i].print();

    return 0;
}