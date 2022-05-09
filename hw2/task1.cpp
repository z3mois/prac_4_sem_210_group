#include<iostream>
using namespace std;
class score {
	public:
		score(int number = 1,const char n[]= "\0", const char s[] = "\0", int money = 0){
            balance = money;
            card_number = number;
			name = new char [20];
			time_create = new char [20];
			for(int i = 0; i < 21; i++){
				if((n[i] == 0) || (i == 20)){
					name[i] = 0;
					break;
				}
				name[i] = n[i];
			}
			for(int i = 0; i < 21; i++){
				if((s[i] == 0) || (i == 20)){
					time_create[i] = 0;
					break;
				}
				time_create[i] = s[i];
			}
		}
		score(const score &sc){
			name = new char [20];
			time_create = new char [20];
			for(int i = 0; i < 21; i++){
				if((sc.name[i] == 0) || (i == 20)){
					name[i] = 0;
					break;
				}
				name[i] = sc.name[i];
			}
			for(int i = 0; i < 21; i++){
				if((sc.time_create[i] == 0) || (i == 20)){
					time_create[i] = 0;
					break;
				}
				time_create[i] = sc.time_create[i];
			}
		}
		~score(){
			delete[] name;
			delete[] time_create;
		}
		
		
		score& operator= (const score &sc){
			if (this != &sc) {
	 			for(int i = 0; i < 21; i++){
					if((sc.name[i] == 0) || (i == 20)){
						name[i] = 0;
						break;
					}
					name[i] = sc.name[i];
				}
				for(int i = 0; i < 21; i++){
					if((sc.time_create[i] == 0) || (i == 20)){
						time_create[i] = 0;
						break;
					}
					time_create[i] = sc.time_create[i];
				}
	        }
            return *this;
        }
		
		friend ostream& operator<< (ostream &out, const score &sc);
    private:
        int card_number;
        char* name;
        char* time_create;
        int balance;  
        size_t how_much_copy = 0;
        size_t how_much_equal = 0; //   ловли количество раз , чтобы уадлить единожды, но не вышло
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
protected:
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
    virtual void print() const{
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
			temp->prev = nullptr;
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

    virtual score& front() const{
        return first->item;
    }
    score& back() const{
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
			if(last != NULL){
				Node *temp = last;
				last = last->prev;
				if(last != NULL){
					last->next = NULL;
				}
				else{
					first = NULL;
				}
				delete temp;
			}
    }
    virtual size_t size() const {
        Node *temp = first;
        size_t size = 0;
        while (temp != nullptr){
            size++;
            temp = temp->next; 
        }
        return size;
    }
    virtual bool empty() const {
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
class queue : private List{
private:
    size_t len = 0;
    size_t MAX_SIZE;
public:
    queue(): MAX_SIZE(20){};

    queue(size_t sizes) : MAX_SIZE(sizes){};

    ~queue(){}

    void back(const score & a){
        if (!full()){
            List::push_back(a);
            len++;
        }
    }

    score& front(){
        if (!empty()){
            return List::front();
        }
        else {
            throw "Queue is empty";
        }
    }
    void pop(){
        if (!empty()){
            List::pop_front();
            len--;
        }
        else {
            throw "Queue is empty";
        }   
    }

    bool empty(){
        return size() == 0;
    }

    void print(){
        List::print();
    }

    bool full(){
        return size() == MAX_SIZE;
    }

    size_t size(){
        return len;
    }
};
int main(){
    score A(9275124, "Pavel Akcenov\0", "23:12 04.12.2020\0", 10000);
    score B = score(2423123, "Ilya Kozhanov\0", "21:12 03.10.2021\0", 11111);
    score C = score(2233131, "Dmitry Moiseev\0", "09:15 06.9.2022\0", 12221);
    score D = score(1499014, "Veronika Kerber\0", "19:58 07.10.2021\0", 14941);
    score E = score(7532523, "Airat Faizulov\0", "8:45 07.02.2025\0", 234941);
    queue q(5);
    cout << "q is empty = " << q.empty() << "\n\n";
    q.back(A);
    q.back(C);
    q.back(D);
    cout << "q size is = " << q.size() << "\n\n";
    //error (what we need) q.push_back(E);
    q.back(B);
    q.back(E);
    q.print();
    cout << "q is full = " << q.full() << "\n\n";
    cout << "first in q = " << q.front() << "\n\n"; 
    q.pop();
    q.print();
    q.pop();
    q.pop();
    cout << "q size is = " << q.size() << "\n\n";
    q.pop();
    q.pop();
    q.print();
    cout << "q is empty = " << q.empty() << "\n\n";
    return 0;
}