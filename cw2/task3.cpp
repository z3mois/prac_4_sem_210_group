#include<iostream>
using namespace std;

class B{
int a;
B &b;

public:
    B(int q, B& s):a(q), b(s){};
    int f2(){return b--->a<---b;}
    B* operator --(int){cout <<"1\n";};
    B operator -(){cout << "2\n";};
    int operator --(){cout << "3\n";};
};

int main(){
    B b1(5, b1);
    cout<< b1.f2() << endl;
    return 0;
}