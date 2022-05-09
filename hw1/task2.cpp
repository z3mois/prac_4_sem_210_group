#include<iostream>
using namespace std;
class score{
    public:
    //score(){}
    score(int n = 1111, const char* nam = " ", const char* time = " ", int money = 0){
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
        for (i; i< 20; i++){
            name[i] = ' ';
        }
        i = 0;
        for (i = 0; i < 20; i++){
            if (time[i] != '\0')
                time_create[i] = time[i];
            else 
                break;
        }
        for (i; i< 20; i++){
            time_create[i] = ' ';
        }
        //cout<<"create" << '\n';
    }
    score(const score& sc):card_number(sc.card_number), name(sc.name),
    time_create(sc.time_create), balance(sc.balance){
        //cout << "copy" << '\n';
    }
    ~score(){
        delete [] name;
        delete [] time_create;
        //cout << "~score" << '\n';
    }
    friend ostream& operator << (ostream& out, const score & sc);/// функция-член
    score& operator = (const score & sc){
        card_number = sc.card_number;
        balance = sc.balance;
        int i = 0;
        for (i = 0; i < 20; i++){
            if (sc.name[i] != '\0')
                name[i] = sc.name[i];
            else   
                break;
        }
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
        for (i; i< 20; i++){
            time_create[i] = ' ';
        }
        //cout << "Equal" << '\n';
        return *this;
    };
    private:
        int card_number;
        char* name;
        char* time_create;
        int balance;    
};
    ostream& operator << (ostream& out, const score & sc){
        out << sc.card_number << ' ' << sc.name << ' ' << sc.time_create << ' '<< sc.balance;
        return out;
    }
struct Node      
 {
     score item;     
     Node *next,*prev; 
 };

class List{
private:
    Node *first,*last; 
public:
    List():first(nullptr), last(nullptr){};
    ~List(){
        Node *curr;
        while (first != nullptr){
            curr = first;
            first = first->next;
            delete curr;
        }
    }    
    void print(){
        Node *temp = first; 
        if (temp == nullptr){
            cout << "empty" << '\n';
        }
        else {
            while (temp != nullptr){
                cout << temp->item << '\n'; 
                temp = temp->next; 
            }
        }
        cout << '\n';
    }
    void push_front(const score& x){
			Node *temp = new Node;
			temp->item = x;
			temp->prev = NULL;
			temp->next = first;
			if (first != nullptr){
				first->prev = temp;
			}
			first = temp;
			if(last == nullptr){
				last = temp;
			}        
    }
    void push_back(const score& x){
        Node *temp = new Node;
        temp->item = x;
        temp->next = nullptr;
        temp->prev = last;
        if (last != nullptr){
            last->next = temp;
        }
        last = temp;
        if (first == nullptr){
            first = temp;
        }
    }

    score& front(){
        return first->item;
    }
    score& back(){
        return last->item;
    }
    void pop_front(){
        if (first != nullptr){
            Node* temp = first;
            first = first->next;
            if (first != nullptr){
                first->prev = nullptr;
            }
            else {
                last = nullptr;
            }
            delete temp;
        }
    }
    void pop_back(){
        if (last != nullptr){
            Node* temp = first;
            while (temp->next != last){
                temp = temp->next; 
            }
            delete last;
            last = temp;
            last->next = nullptr;
        }
    }
    size_t size(){
        Node *temp = first;
        size_t size = 0;
        while (temp != nullptr){
            size++;
            temp = temp->next; 
        }
        return size;
    }
    bool empty(){
        return first == nullptr;
    }
    void insert(int p, const score& x){
        if (p > (int)size() || p < (int)size()){
            cout << "Error, pos is not true" << '\n' << '\n';
            return;
        }
        Node *when_insert = first;
        while (p > 0 && when_insert != nullptr){
            p--;
            when_insert = when_insert->next;
        }
        if (when_insert == first){
            push_front(x);
            return;
        }
        if (when_insert  == nullptr){
            push_back(x);
            return;
        }
        Node *temp = new Node;
        temp->item = x;
        temp->next = when_insert;
        temp->prev = when_insert->prev;
        temp->prev->next = temp;
        when_insert->prev = temp;
    }
    void erase(int p){
        if (p > (int)size() || p < (int)size()){
            cout << "Error, p is not true" << '\n' << '\n';
            return;
        }
        Node *what_delete = first;
        while (p > 0 && what_delete != nullptr){
            p--;
            what_delete = what_delete->next;
        }   
        if (what_delete != nullptr){
            if (what_delete == first){
                pop_front();
            }
            else if (what_delete == last){
                pop_back();
            }
            else{
                what_delete->prev->next = what_delete->next;
                what_delete->next->prev = what_delete->prev;
                delete what_delete;
            }
        }
    }
 };
int main(){
    cout << "Нумерация позиций идует с 0" << '\n' << '\n';
    score A(9275124, "Pavel Akcenov\0", "23:12 04.12.2020\0", 10000);
    score B = score(2423123, "Ilya Kozhanov\0", "21:12 03.10.2021\0", 11111);
    score C = score(2233131, "Dmitry Moiseev\0", "09:15 06.9.2022\0", 12221);
    score D = score(1499014, "Veronika Kerber\0", "19:58 07.10.2021\0", 14941);
    score E = score(7532523, "Airat Faizulov\0", "8:45 07.02.2025\0", 234941);
    List list;
    cout << "List is empty = " << list.empty() << '\n' << '\n';
    list.push_back(E);
    list.push_front(D);
    list.push_front(B);
    list.push_back(A);
    list.push_back(C); // B D E A C
    list.print();
    cout << "List size is "<< list.size() << '\n' << '\n';
    list.pop_front();
    list.pop_back();
    list.print(); // D E A
    cout << "List size is "<< list.size() << '\n'<< '\n';
    cout << "List is empty = " << list.empty() << '\n' << '\n';
    list.insert(2,B);
    list.insert(0,C);
    list.print(); // C D E B A
    cout << "List size is "<< list.size() << '\n'<< '\n';
    list.erase(3); // C D E A
    list.erase(1); // C E A
    list.print();
    list.insert(100, A);
    list.erase(100);
    return 0;
}