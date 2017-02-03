#include "a1_polynomial.hpp"
#include <iostream>
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;


//Dustin Hu and Jimmy Xu
using namespace std;

Polynomial::Polynomial(int* A, int size)
{
	this->list = new DoublyLinkedList();
	for (int i = 0; i < size; i++)
	{
		this->list->insert_back(*(A + i));
	}
	this->reduceList();
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
	if (this->list->size() > 1)
		return this->list->size() - 1;
	else
		return 0;
}

Polynomial* Polynomial::add(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	if (this->list->size() > rhs->list->size())
	{
		// THis is of higher degree than RHS
		for (int i = 0; i < rhs->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i) + rhs->list->select(i));
		}
		for (int i = rhs->list->size(); i < this->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i));
		}
	} 
	else
	{
		// RHS has a bigger degree than LHS
		for (int i = 0; i < this->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i) + rhs->list->select(i));
		}
		for (int i = this->list->size(); i < rhs->list->size(); i++)
		{
			output->list->insert_back(rhs->list->select(i));
		}
	}
	this->reduceList();
	return output;
}

Polynomial* Polynomial::sub(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	if (this->list->size() > rhs->list->size())
	{
		// THis is of higher degree than RHS
		for (int i = 0; i < rhs->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i) - rhs->list->select(i));
		}
		for (int i = rhs->list->size(); i < this->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i));
		}
	} 
	else
	{
		// RHS has a bigger degree than LHS
		for (int i = 0; i < this->list->size(); i++)
		{
			output->list->insert_back(this->list->select(i) - rhs->list->select(i));
		}
		for (int i = this->list->size(); i < rhs->list->size(); i++)
		{
			output->list->insert_back(-1 * rhs->list->select(i));
		}
	}
	output->reduceList();
	return output;
}


Polynomial* Polynomial::mul(Polynomial* rhs)
{
	Polynomial* output = new Polynomial();
	Polynomial* temp = new Polynomial();
	// Min and max is becaues otherwise it might try to multiply by a null value
	for (int i = 0; i < min(this->list->size(), rhs->list->size()); i++)
	{
		for (int k = 0; k < i; k++)
		{
			temp->list->insert_back(0);
		}
		for (int j = 0; j < max(this->list->size(), rhs->list->size()); j++)
		{
			temp->list->insert_back(this->list->select(j) * rhs->list->select(i));
		}
		output = output->add(temp);
		while (!temp->list->empty())
		{
			temp->list->remove_back();
		}
	}
	output->reduceList();
	return output;
}


void Polynomial::reduceList()
{
	if (this->list->tail_)
	{
		while (this->list->tail_ && this->list->tail_->value == 0)
		{
			this->list->remove_back();
		}
	}
}


// Test cases

// Check constrctors
bool test1()
{
	int a[5] = {0};
	int b[5] = {1, 2, 3, 4, 5};
	Polynomial list1 = Polynomial();
	Polynomial list2 = Polynomial(a, 5);
	Polynomial list3 = Polynomial(b, 4);

	ASSERT_TRUE(list1.degree() == 0);
	ASSERT_TRUE(list2.degree() == 0);
	ASSERT_TRUE(list3.degree() == 3);

	return true;
}

// Check addition
bool test2()
{
	int a[5] = {1, 3, 6, 8, 10};
	int b[4] = {1, 2, 3, 4};
	Polynomial list1 = Polynomial();
	Polynomial list2 = Polynomial(a, 5);
	Polynomial list3 = Polynomial(b, 4);
	
	ASSERT_TRUE((list1.add(&list1))->degree() == 0);
	ASSERT_TRUE((list2.add(&list2))->degree() == 4);
	ASSERT_TRUE((list1.add(&list2))->degree() == 4);
	ASSERT_TRUE((list2.add(&list1))->degree() == 4);
	
	ASSERT_TRUE((list3.add(&list1))->degree() == 3);
	ASSERT_TRUE((list3.add(&list2))->degree() == 4);
	ASSERT_TRUE(((list2.add(&list1))->add(&list3))->degree() == 4);
	ASSERT_TRUE(((list2.add(&list1))->add(&list2))->degree() == 4);

	return true;
}

// Check subtraciton
bool test3()
{
	int a[8];
	for (int i = 0; i < 8; i++)
	{
		a[i] = i + 3;
	}
	
	Polynomial list1 = Polynomial();
	Polynomial list2 = Polynomial(a, 3);
	Polynomial list3 = Polynomial(a, 5);
	
	ASSERT_TRUE((list1.sub(&list1))->degree() == 0);
	ASSERT_TRUE((list2.sub(&list2))->degree() == 0);
	ASSERT_TRUE((list1.sub(&list2))->degree() == 2);
	ASSERT_TRUE((list1.sub(&list3))->degree() == 4);
	ASSERT_TRUE((list2.sub(&list3))->degree() == 4);
	ASSERT_TRUE(((list3.sub(&list2))->sub(&list1))->degree() == 4);
	ASSERT_TRUE(((list3.sub(&list1))->sub(&list2))->degree() == 4);
	return true;
}


// Check multiplication
bool test4()
{
	int a[8];
	for (int i = 0; i < 8; i++)
	{
		a[i] = i;
	}
	Polynomial list1 = Polynomial();
	Polynomial list2 = Polynomial(a, 8);
	Polynomial list3 = Polynomial(a, 4);
	
	ASSERT_TRUE((list1.mul(&list1))->degree() == 0); 
	ASSERT_TRUE((list1.mul(&list2))->degree() == 0);
	ASSERT_TRUE((list2.mul(&list1))->degree() == 0);
	ASSERT_TRUE((list2.mul(&list2))->degree() == 14);
	ASSERT_TRUE((list3.mul(&list3))->degree() == 6);
		
	ASSERT_TRUE((list2.mul(&list3))->degree() == 10);
	ASSERT_TRUE(((list2.mul(&list3))->mul(&list1))->degree() == 0);
	return true;
}


int main()
{
	int a[4] = {1, 1, 0, 0};
	Polynomial list1 = Polynomial(a, 2);

	bool testResults[4];
	testResults[0] = test1();
	testResults[1] = test2();
	testResults[2] = test3();
	testResults[3] = test4();
	
	
	for (int i = 0; i < 4; i++)
	{
		cout << testResults[i];
	}
	return 0;
}
