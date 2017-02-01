#include "a1_polynomial.hpp"
#include <iostream>
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

using namespace std;

Polynomial::Polynomial(int* A, int size)
{
	this->list = new DoublyLinkedList();
	for (int i = 0; i < size; i++)
	{
		this->list->insert_back(*(A + i));
	}
}

Polynomial::Polynomial() 
{
	this->list = new DoublyLinkedList();
}

Polynomial::~Polynomial()
{
	delete list;
	
}

void Polynomial::print() const
{
	this->list->print();
}

int Polynomial::degree() const
{
	return this->list->size();
}

Polynomial* Polynomial::add(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	if (this->degree() > rhs->degree())
	{
		// THis is of higher degree than RHS
		for (int i = 0; i < rhs->degree(); i++)
		{
			output->list->insert_back(this->list->select(i) + rhs->list->select(i));
		}
		for (int i = rhs->degree(); i < this->degree(); i++)
		{
			output->list->insert_back(this->list->select(i));
		}
	} 
	else
	{
		// RHS has a bigger degree than LHS
		for (int i = 0; i < this->degree(); i++)
		{
			output->list->insert_back(this->list->select(i) + rhs->list->select(i));
		}
		for (int i = this->degree(); i < rhs->degree(); i++)
		{
			output->list->insert_back(rhs->list->select(i));
		}
	}

	return output;
}

Polynomial* Polynomial::sub(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	if (this->degree() > rhs->degree())
	{
		// THis is of higher degree than RHS
		for (int i = 0; i < rhs->degree(); i++)
		{
			output->list->insert_back(this->list->select(i) - rhs->list->select(i));
		}
		for (int i = rhs->degree(); i < this->degree(); i++)
		{
			output->list->insert_back(this->list->select(i));
		}
	} 
	else
	{
		// RHS has a bigger degree than LHS
		for (int i = 0; i < this->degree(); i++)
		{
			output->list->insert_back(this->list->select(i) - rhs->list->select(i));
		}
		for (int i = this->degree(); i < rhs->degree(); i++)
		{
			output->list->insert_back(-1 * rhs->list->select(i));
		}
	}

	return output;
}


Polynomial* Polynomial::mul(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	Polynomial* temp = new Polynomial();
	for (int i = 0; i < this->degree(); i++)
	{
		for (int k = 0; k < i; k++)
		{
			temp->list->insert_back(0);
		}
		for (int j = 0; j < this->degree(); j++)
		{
			temp->list->insert_back(this->list->select(j) * rhs->list->select(i));
		}
		output = output->add(temp);
		while (!temp->list->empty())
		{
			temp->list->remove_back();
		}
	}
	return output;
}


// Test cases

// Check constrctors
bool test1()
{
	
}
int main()
{
	int foo[5] = {0, 1, 2, 3, 4};
	int bar[4] = {0, 1, 2, 3};
	
	Polynomial* A = new Polynomial(foo, 5);
	Polynomial* B = new Polynomial(bar, 4);
	Polynomial* C = new Polynomial();
	Polynomial* D = C->mul(A);
	
	
	A->print();
	B->print();
	D->print();
	
	
	return 0;
}
