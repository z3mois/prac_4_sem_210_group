#include<iostream>
using namespace std;
class score{
    public:
    score(){};
    score(int n = 1111, const char* nam = "\0", const char* time = "\0", int money = 0){
        card_number = n;
        name = new char[20];
        time_create = new char[20];
        balance = money;
        int i = 0;
        for (i = 0; i < 20; i++){
            if (nam[i] != '\0')
                name[i] = nam[i];
            else   
                break;
        }
        name[i] = '\0';
        i++;
        for (i; i < 20; i++){
            name[i] = ' ';
        }
        i = 0;
        for (i = 0; i < 20; i++){
            if (time[i] != '\0')
                time_create[i] = time[i];
            else 
                break;
        }
        time_create[i] = '\0';
        i++;
        for (i; i< 20; i++){
            time_create[i] = ' ';
        }
        cout<<"create" << '\n';
    }
    score(const score& sc){
        card_number = sc.card_number;
        int i = 0;
        name = new char[20];
        time_create = new char[20];
        for (i = 0; i < 20; i++){
            if (sc.name[i] != '\0')
                name[i] = sc.name[i];
            else   
                break;
        }
        name[i] = '\0';
        i++;
        for (i; i< 20; i++){
            name[i] = ' ';
        }
        i = 0;
        for (i = 0; i < 20; i++){
            if (sc.time_create[i] != '\0')
                time_create[i] = sc.time_create[i];
            else 
                break;
        }
        time_create[i] = '\0';
        i++;
        for (i; i< 20; i++){
            time_create[i] = ' ';
        }
        balance = sc.balance;
        cout << "copy" << '\n';
        //sc.use_in_copy+=1;
    }
    score(score& sc){
        card_number = sc.card_number;
        int i = 0;
        name = new char[20];
        time_create = new char[20];
        for (i = 0; i < 20; i++){
            if (sc.name[i] != '\0')
                name[i] = sc.name[i];
            else   
                break;
        }
        name[i] = '\0';
        i++;
        for (i; i< 20; i++){
            name[i] = ' ';
        }
        i = 0;
        for (i = 0; i < 20; i++){
            if (sc.time_create[i] != '\0')
                time_create[i] = sc.time_create[i];
            else 
                break;
        }
        time_create[i] = '\0';
        i++;
        for (i; i< 20; i++){
            time_create[i] = ' ';
        }
        balance = sc.balance;
        cout << "copy" << '\n';
        sc.use_in_copy+=1;
    }
    ~score(){
        cout <<"~score" << '\n';
        if (use_in_copy == 0){
            delete [] name;
            delete [] time_create; 
        }
        else
            use_in_copy--;        
    }
    friend ostream& operator << (ostream& out, const score & sc);/// функция-член
    score& operator = (const score & sc){
        card_number = sc.card_number;
        balance = sc.balance;
        name = sc.name;
        time_create = sc.time_create;
        cout << "Equal" << '\n';
        return *this;
    };
    private:
        int card_number;
        char* name;
        char* time_create;
        int balance;
        size_t use_in_copy = 0;    
};
    ostream& operator << (ostream& out, const score & sc){
        out << sc.card_number << ' ' << sc.name << ' ' << sc.time_create << ' '<< sc.balance;
        return out;
    }
int main(){
    score A(9275124, "Vasya Volkov\0", "23:12 04.12.2020\0", 10000);
    score B(A);
    score C = score(9275124, "Vasya Kozhanov\0", "21:12 03.10.2021\0", 11111);
    score D(A);
    cout << A << '\n' << B <<  '\n' <<C << '\n';
    A = C;
    cout <<  C << endl;
    return 0;
}