#include<iostream>

using namespace std;

class A{
private:
    int a;
    A(int i = 0): a(i){}
    A(const A& b){
        this->a = b.a;
    }
public:
    static A* ptr;
    static int counter;
    static A* f(int b = 0){
        if (counter == 0){
            ptr = new A(b);
            counter++;
        }
        return ptr;
    }
    // A(const A& b){
    //     this->a = b.a;
    // }
    void print() const{
        cout <<"a is = " << a << '\n';
    }
};

A* A::ptr;
int A::counter = 0;

int main(){
    A* a = A::f(5);
    (*a).print();
    A* b = A::f(10);
    (*b).print(); 
    A* c = A::f(15);
    (*c).print();  
    return 0;
}