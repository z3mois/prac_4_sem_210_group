#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<cmath>
#include<iomanip>
#include<sstream>


using namespace std;

class Figure {
public:
	Figure(const string& name1) : name(name1){};
	virtual string Name() const {
		return name;
	};
	virtual double Perimeter() const = 0;
	virtual double Area () const = 0;
private:
	string name;
};

class Rect : public Figure {
public:
	Rect(const string& name, double width, double height) :
		Figure(name),
		Width(width),
		Height(height){
	};
	double Perimeter() const override{
		return 2 * (Width + Height);
	};
	double Area() const override{
		return Width * Height;
	};
private:
	double Width, Height;
};

class Triangle : public Figure {
public:
	Triangle(const string& name, double a1, double b1, double c1) : 
		Figure(name), a(a1), b(b1), c(c1){};
	double Perimeter() const override{
		return a + b + c;
	};
	double Area() const override{
		double p = (a + b + c) / 2.0;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	};
private:
	double a, b, c;
};

class Circle : public Figure {
public:
	Circle(const string& name, double r1) :
		Figure(name), 
		r(r1){
	};
	double Perimeter() const override{
		return 2.0 * r * 3.14;
	};
	double Area() const override{
		return r * r * 3.14;		
	};
private:
	double r;
};
shared_ptr<Figure> CreateFigure(istringstream& is) {
	string type_name;
	is >> type_name;
	if (type_name == "RECT") {
		double width, height;
		is >> width >> height;
		return make_shared<Rect>(type_name, width, height);
	}
	else {
		if (type_name == "TRIANGLE"){
			double a, b, c;
			is >> a >> b >> c;
			return make_shared<Triangle>(type_name, a, b, c);			
		}
		else {
			if (type_name == "CIRCLE") {
				double r;
				is >> r;
				return make_shared<Circle>(type_name, r);					
			}
		}
	}
}

int main() {
    cout << "EXAMPLE ADD CIRCLE 8 \nPRINT\n";
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}

