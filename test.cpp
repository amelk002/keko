#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <cmath>

using namespace std;
class Sort;
class Container;
class SelectionSort;
class BubbleSort;
class VectorContainer;
class ListContainer;
class Base
{
	public:
		Base() {};
		virtual double evaluate() = 0;
};
class Operand : public Base
{
	protected:
		double number;
	public:
		Operand(): number(0) {}
		Operand(double x): number(x) {}
		double evaluate()
		{
			return number;
		}
};
class Add : public Base
{
	protected:
		Base* leftChild; 
		Base* rightChild;
	public:
		Add(): leftChild(NULL), rightChild(NULL) {}		
		Add(Base* left, Base* right): leftChild(left), rightChild(right) {}		
		double evaluate()
		{
			return this->leftChild->evaluate() + this->rightChild->evaluate();
		}
};
class Subtract : public Base
{
	protected:
		Base* leftChild;
		Base* rightChild;
	public:
		Subtract(): leftChild(NULL), rightChild(NULL) {}		
		Subtract(Base* left, Base* right): leftChild(left), rightChild(right) {}		
		double evaluate()
		{
			return this->leftChild->evaluate() - this->rightChild->evaluate();
		}
};
class Multiply : public Base
{
	protected:
		Base* leftChild;
		Base* rightChild;
	public:
		Multiply(): leftChild(NULL), rightChild(NULL) {}		
		Multiply(Base* left, Base* right): leftChild(left), rightChild(right) {}
		double evaluate()
		{
			return this->leftChild->evaluate() * this->rightChild->evaluate();
		}
};
class Division : public Base
{
	protected:
		Base* leftChild;
		Base* rightChild;
	public:
		Division(): leftChild(NULL), rightChild(NULL) {}		
		Division(Base* left, Base* right): leftChild(left), rightChild(right) {}		
		double evaluate()
		{
			return this->leftChild->evaluate() / this->rightChild->evaluate();
		}
};
class Squared : public Base
{
	protected:
		Base* child;
	public:
		Squared(): child(NULL) {}		
		Squared(Base* one): child(one) {}
		double evaluate()
		{
			return this->child->evaluate() * this->child->evaluate();
		}
};
class Ceiling: public Base
{
	protected:
		Base* child;
	public:
		Ceiling(): child(NULL) {}
		Ceiling(Base* number): child(number) {}
		double evaluate()
		{
			return ceil(child->evaluate());
		}
};
class Floor: public Base
{
	protected:
		Base* child;
	public:
		Floor(): child(NULL) {}
		Floor(Base* number): child(number) {} 
		double evaluate()
		{
			return floor(child->evaluate());
		}
};
class Absolute: public Base
{
	protected:
		Base* child;
	public:
		Absolute(): child(NULL) {}
		Absolute(Base* number): child(number) {}
		double evaluate()
		{
			return fabs(child->evaluate());
		}
};
class Container
{
	protected:
		Sort* sort_function;
	public:
		/*Constructors*/
		Container():sort_function(NULL){};
		Container(Sort*function):sort_function(function){};
		/*Non Virtual Functions*/
		void set_sort_function(Sort* sort_function)
		{//set the type of sorting algorithm
			this->sort_function = sort_function;
		}
		/*Pure Virtual Functions*/
		//push the top pointer of the tree into container
		virtual void add_element(Base*element)=0;
		//iterate through trees and output values	
		virtual void print()=0;
		//calls on the previously set sorting algorithm. Checks if sort_function is not null,
		//throw exception if otherwise	
		virtual void sort() =0;
		/*Essentially the only functions needed to sort*/
		//switch tree locations		
		virtual void swap(int i,int j)=0;
		//get top ptr of tree at index i		
		virtual Base* at(int i)=0;
		//return container size
		virtual int size()=0;
};
class Sort
{
	public:
	    Sort() {};
		virtual void sort(Container* container) = 0;
};
class VectorContainer : public Container
{
	protected:
		vector<Base*> baseVector;
		Base* child;
	public:
		VectorContainer(): child(NULL) {}	
		VectorContainer(Sort* temp): child(NULL)
		{
			sort_function = temp;
		}
		void sort()
		{
		      sort_function->sort(this);
		}
		void add_element(Base* element)
		{
			baseVector.push_back(element);
		}
		void print()
		{
			for(unsigned int i = 0; i < baseVector.size(); ++i)
			{
				cout << baseVector.at(i)->evaluate() << endl;
			}
		}
		void swap(int i,int j)
		{
			Base* temp2 = baseVector.at(i);
			baseVector.at(i) = baseVector.at(j);
			baseVector.at(j) = temp2;
		}
		Base* at(int i)
		{
			return baseVector.at(i);
		}
		int size()
		{
			return baseVector.size();
		}
};
class ListContainer : public Container
{
	protected:
		list<Base*> baseList;
		Base* child;
	public:
		ListContainer(): child(NULL) {}
		ListContainer(Sort* temp): child(NULL)
		{
			sort_function = temp;
		} 
		void sort()
		{
			 sort_function->sort(this);
		}
		void add_element(Base* element)
		{
			baseList.push_back(element);
		}
		void print()
		{
			list<Base*>::iterator it;
			for(it = baseList.begin(); it != baseList.end(); it++) 
			{
				Base* a = *it;
				cout << a->evaluate() << endl;
			}
		}
		void swap(int i,int j)
		{
			list<Base*>::iterator it;
			int counter = 0;
			Base* temp1;
			Base* temp2;
			int counter2 = 0;
			for(it = baseList.begin(); it != baseList.end(); it++) 
			{
				if(counter == i)
				{
					temp1 = *it;
				}
				if(counter == j)
				{
					temp2 = *it;
				}
				counter++;
				counter2++;
			}
			counter = 0;
			counter2 = 0;
			for(it = baseList.begin(); it != baseList.end(); it++) 
			{
				if(counter == i)
				{
					*it = temp2;
				}
				if(counter == j)
				{
					*it = temp1;
				}
				counter++;
				counter2++;
			}
		}
		Base* at(int i)
		{
			list<Base*>::iterator it;
			int counter = 0;
			for(it = baseList.begin(); it != baseList.end(); it++) 
			{
				if(counter == i)
				{
					return *it;
				}
				counter++;
			}
			return *it;
		}
		int size()
		{
			return baseList.size();
		}
};
class SelectionSort : public Sort
{
	protected:
		Container* Child;
	public:
		SelectionSort(): Child(NULL) {}
		SelectionSort(Container* va): Child(va) {}
		void sort(Container* va)
		{
			Child = va;
			unsigned int outer, inner, first;
			for(outer = 0; outer < va->size(); ++outer)
			{
				first = 0;
				for(inner = 1; inner <= outer; inner++)
				{
					if(va->at(inner)->evaluate() > va->at(first)->evaluate())
					{
						first = inner;
					}
				}
				va->swap(first, outer);	
			}
		}
};
class BubbleSort : public Sort
{
	protected:
		Container* Child;
	public:
		BubbleSort(): Child(NULL) {}
		BubbleSort(Container* bubble): Child(bubble) {}
		void sort(Container* va)
		{
			Child = va;
			for(unsigned int i = 0; i < va->size(); i++)
			{
				for(unsigned int j = 0; j < va->size(); j++)
				{
					if(j != va->size() - 1)
					{
						if(va->at(j)->evaluate() > va->at(j + 1)->evaluate())
						{
               va->swap(j, j+1);
						}
					}
				}
			}
		}
};
int main(){
	Operand* op7 = new Operand(7);
    Operand* op6 = new Operand(7.4);
    Operand* op5 = new Operand(6.3);
	Operand* op4 = new Operand(4);
	Operand* op3 = new Operand(3);
	Operand* op2 = new Operand(2);
    Operand* op1 = new Operand(-3.4);
    Operand* op0 = new Operand(3.3);
	Multiply* A = new Multiply(op7,op4);
	Add* B = new Add(op3,A);
	Subtract* C = new Subtract(B,op2);
	Squared* D = new Squared(C);
	VectorContainer* container = new VectorContainer();
	container->add_element(A);
	container->add_element(B);
	container->add_element(C);
	container->add_element(D);


	cout << "Container Before Sort: " << endl;
	container->print();

	cout << "Container After Sort: " << endl;
	container->set_sort_function(new SelectionSort());
	container->sort();
	container->print();
	
    cout << "Before Ceiling: " << endl;
    cout << op6->evaluate() << endl;
    cout << "After Ceiling: " << endl;
    Ceiling* op9 = new Ceiling(op6);
    cout << op9->evaluate() << endl;
  
    cout << "Before Floor: " << endl;
    cout << op5->evaluate() << endl;
    cout << "After Floor: " << endl;
    Floor* op10 = new Floor(op5);
    cout << op10->evaluate() << endl;

    cout << "Before Absolute Value: " << endl;
    cout << op1->evaluate() << endl;
    cout << "After Absolute Value: " << endl;
    Absolute* op11 = new Absolute(op1);
    cout << op11->evaluate() << endl;
	return 0;
};
