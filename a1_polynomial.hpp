#ifndef A1_POLYNOMIAL_HPP
#define A1_POLYNOMIAL_HPP

#include "a1_doubly_linked_list.hpp"


class Polynomial
{
	public:
		Polynomial(int* A, int size);
		Polynomial();
		~Polynomial();
		void print() const;
		int degree() const;
		Polynomial* add(Polynomial* rhs);
		Polynomial* sub(Polynomial* rhs);
		Polynomial* mul(Polynomial* rhs);
	private:
		DoublyLinkedList* list;
};


#endif
