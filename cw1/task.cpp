#include<iostream>

using namespace std;
class Arr{
private:
	int * arr;
	int size;
public:
	Arr(int s, int date = 0) : size(s){
		arr = new int[s];
		for(int i = 0; i < size; arr[i++] = date);
	}
	
	Arr(const Arr &array){
		arr = new int[array.size];
		size = array.size;
		for(int i = 0; i < size; i++){
			arr[i] = array.arr[i];
		}
	}
	
	Arr& operator= (const Arr &array){
		if (this != &array){
			for(int i = 0; i < size; i++){
				arr[i] = array.arr[i];
			}
			size = array.size;
		}
		return *this;
	}
	
	~Arr(){
		delete[] arr;
	}
	
	
	int& operator[] (int idx){
		return arr[idx];
	}
    Arr(Arr&& tmp):size(tmp.size),arr(tmp.arr){
    }

    Arr& operator=(Arr&& tmp){
        delete [] arr;
        size = tmp.size;
        arr = tmp.arr;
        tmp.arr = nullptr;
        tmp.size = 0;
        return *this;
    }
	friend ostream& operator<< (ostream &out, const Arr &array);
	friend Arr operator | (Arr array, int num);
	friend Arr operator | (Arr array1, Arr array2);
	friend Arr operator - (Arr array);
};

ostream& operator<< (ostream &out, const Arr &array){
    cout << "size = " << array.size  << " ";
	for(int i = 0; i < array.size; i++){
		cout << array.arr[i];
		if (i != array.size - 1){
			cout << " ";
		}
	}
	cout << endl;
	return out;
}

Arr operator |(Arr array, int num){
	Arr answer(array.size);
	for(int i = 0; i < array.size; i++){
		answer[i] = array.arr[i] | num;
	}
	return answer;
}

Arr operator | (Arr array1, Arr array2){
	int size = min(array1.size, array2.size);
	Arr answer(size);
	for(int i = 0; i < size; i++){
        answer[i] = array1.arr[i] | array2.arr[i];
	}
	return answer;
}

Arr operator - (Arr array){
	Arr answer(array.size);
	for(int i = 0; i < array.size; i++){
        answer.arr[i] = - array.arr[i];
	}
	return answer;
}


int main(){
    Arr a1(15);
    Arr a2(20, 5);
    Arr a3(30, 3);
    const Arr a4(5);
    cout << "1\n" << a1 << a2 << a3 << a4;
    a2 = a2 | 2;
    a3 = (-a2)| a3;
    
    a3[5] = 10;
    //a1 = a4|a3;
    cout << "2\n" << a1 << a2 << a3 << a4;
     a1 = a2;
    cout << "3\n" <<a1 << a2 << a3 << a4;
    return 0;
}