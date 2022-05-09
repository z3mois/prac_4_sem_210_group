#include<iostream>
#include<vector>
#include<string>
#include<list>
#include <type_traits>
#include <algorithm>

using namespace std;
class func{
public:
    func(bool str = false, bool vec_list = false): is_str(str), is_vector_or_list(vec_list){}
    template<class U>
    void operator()(vector<U>& u){
        reverse(u.begin(), u.end());
    }
    template<class U>
    void operator()(list<U>& u){
        reverse(u.begin(), u.end());
    }
    void operator()(string & u){
        reverse(u.begin(), u.end());
    }
    void operator()(int & u){
        u = 1000;
    }
    void operator()(char & u){
        u = 'm';
    }
private:
    bool is_str;
    bool is_vector_or_list;
    bool is_int = false;
};


int main(){
    func f;
    list<int> l = {1,2,3,4,5};
    f(l);
    vector<int> v = {1,2,3};
    f(v[1]);
    for (auto &i:l){
        cout << i << " ";
    };
    cout << "\n";    
    for (auto &i:v){
        cout << i << " ";
    };
    cout << "\n";
    string s1 = "adadsdaff";
    f(s1[0]);
    cout << s1 << endl;
    f(s1);
    cout << s1 << endl;
    vector<string> s2 = {"dad", "mams", "paps", "rars"};
    f(s2);
    for (auto &i:s2){
        cout << i << " ";
    };
    cout << endl;
    f(s2[2]);
    for (auto &i:s2){
        cout << i << " ";
    };
    cout << endl;
    return 0;
}