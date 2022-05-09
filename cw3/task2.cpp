#include<list>
#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
template<class T, class L>
void preobraz(vector<T> & vec, list<L>& lis){
    int idx = 1;
    while (true){
        if((idx <= vec.size()) && lis.size() > 1){
            vec.insert(vec.begin() + idx + 1, lis.front());
            lis.pop_front();
            lis.pop_front();
            idx += 3;
        }
        else{
            break;
        }
    }
}
int main() {
    vector<int>  vec = {1,2,3,4,5};
    list<int> lis = {8,9,10,11};
    preobraz(vec, lis);
    for (auto i: vec){
        cout<< i << " ";
    }
    // 1 2 8 3 4 10 5
    return 0;
}