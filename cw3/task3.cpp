#include<iostream>
#include<vector>
#include<list>
//#include<iterator>
#include<algorithm>
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
void delete1(vector<T>& t1){
    int counter = 1;
    t1.erase(remove_if(t1.begin(), t1.end(), [&counter](const T i){
        return (counter++)%3==0;
    }), t1.end());
}

template<class T>
void delete1(list<T>& t1){
    int counter = 1;
    auto it1 = remove_if(t1.begin(), t1.end(), [&counter](const T i){
        return (counter++)%3==0;
    });
    t1.erase(it1, t1.end());
};
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
    vector<int> vec1 = {1,2,3,4,5,6,7,8, 9,10};
    const vector<int> vec2 = {2,3, 4,5,6};
    list<int> lis1 = {1,2,3,4};
    delete1(vec1);
    delete1(lis1);
    Print1(vec1);
    Print1(lis1);
    return 0;
}
