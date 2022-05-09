#include<iostream>
#include<vector>
#include<list>
#include<iterator>
using namespace std;
template<class It>
void Print(It range_begin, It range_end){
    It i = range_begin;
    for (i; i != range_end; i++){
        cout << *i << " ";
    }
    cout << "\n";
}
template<class T>
void Print1(const T& t1){
    typename T::const_iterator it1 = t1.begin();
    for (it1; it1 != t1.end(); it1++){
        cout << *it1 << " ";
    }
    cout<< "\n";
    typename T::const_reverse_iterator it2 = t1.rbegin();
    for (it2; it2 != t1.rend(); it2++){
        cout << *it2 << " ";
    }
    cout<< "\n";
}
int main(){
    vector<int> vec1 = {1,2,3,4,5,6,7,8};
    const vector<int> vec2 = {2,3, 4,5,6};
    list<int> lis1 = {1,2,3,4};
    // Print(begin(vec1), end(vec1));
    // Print(rbegin(vec2), rend(vec2));
    // Print(lis1.begin(), lis1.end());
    Print1(vec1);
    Print1(vec2);
    Print1(lis1);
    return 0;
}