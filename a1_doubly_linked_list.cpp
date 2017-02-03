#include "a1_doubly_linked_list.hpp"
#include "a1_tests.hpp"
#include <iostream>

//Dustin Hu and Jimmy Xu
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* cur = head_;
	if (cur!=NULL){
	
		while (cur->next != NULL)
		{
			cur = cur->next;
			delete cur->prev;
			cur->prev=NULL;
		}
		
		if (cur != NULL)
		{
			delete cur;
			cur=NULL;
		}
	}
}


unsigned int DoublyLinkedList::size() const
{
	return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
	return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
	return (size_ == 0);
}

bool DoublyLinkedList::full() const
{
	return (size_ == CAPACITY);
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	Node* cur = head_;
	if (index >= 0 && index < size_)
	{
		for (int i = 0; i < index; i++)
		{
			cur = cur->next;
		}
	}else {
		return tail_->value;
	}
	return cur->value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	Node* cur=head_;
	for(int i=0;i<size_;i++){
		if (cur->value==value){
			return i;
		}
		cur=cur->next;
	}
	return size_;
}

void DoublyLinkedList::print() const
{
	Node* cur = head_;
	cout << "NULL <- ";
	for (int i = 0; i < size_; i++)
	{
		cout  << cur->value << " <--> ";
		cur = cur->next;
	}
	cout<<" NULL"<<endl;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{	
	Node* cur = head_;
	if (index<size_){
		for(int i=0;i<index;i++){
			cur=cur->next;
		}
		return cur;
	}
	return NULL;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	bool output = false;
	if (index >= 0 && index <= size_ && size_+1 < CAPACITY)
	{
		Node* newNode = new Node(value);

		if (size_==0){
			//empty list
			head_= newNode;
			tail_ = newNode;
			newNode->prev=NULL;
			newNode->next=NULL;
		}
		else if (index==0){
			// no prev
			head_->prev = newNode;
			newNode->next = head_;
			newNode->prev = NULL;
			head_ = newNode;
		}
		else if (index==size_){
			// no next
			tail_->next = newNode;
			newNode->next = NULL;
			newNode->prev = tail_;
			tail_ = newNode;
		}else{
			Node* cur = head_;
			for(int i=0;i<index;i++){
				cur=cur->next;
			}
			cur->prev->next = newNode;
			newNode->prev = cur->prev;
			newNode->next = cur;
			cur->prev = newNode;
		}
		output = true;
		size_++;
	}
	return output;
}

bool DoublyLinkedList::insert_front(DataType value)
{
	return insert(value, 0);
}

bool DoublyLinkedList::insert_back(DataType value)
{
	return insert(value, size_);
}

bool DoublyLinkedList::remove(unsigned int index)
{
	bool output = false;
	if (index >= 0 && index < size_ && size_ > 0)
	{
		Node* old;
		if (size_==1){
			//empty list
			old = head_;
			head_=NULL;
			tail_=NULL;
		}
		else if (index==0){
			// no prev
			old=head_;
			head_=head_->next;
			head_->prev=NULL;
		}
		else if (index==size_-1){
			// no next
			old=tail_;
			tail_=tail_->prev;
			tail_->next=NULL;
		}else{
			old=head_;
			for(int i=0;i<index;i++){
				old=old->next;
			}
			old->prev->next=old->next;
			old->next->prev=old->prev;
		}
		delete old;
		old = NULL;
		output = true;
		size_--;
		
	}
	return output;
}

bool DoublyLinkedList::remove_front()
{
	return remove(0);
}

bool DoublyLinkedList::remove_back()
{
	return remove(size_ - 1);
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	Node* cur = head_;
	if (index<size_){
		for(int i=0;i<index;i++){
			cur=cur->next;
		}
		cur->value=value;
		return true;
	}
	return false;
}

bool DoublyLinkedList::is_sorted_asc()const{
	Node* cur = head_;
	if (cur==NULL){
		return true;
	}
	while (cur->next!=NULL){
		if (cur->value>cur->next->value){
			return false;
		}
		cur=cur->next;
	}
	return true;
}

bool DoublyLinkedList::is_sorted_desc()const{
	Node* cur = head_;
	if (cur==NULL){
		return true;
	}
	while (cur->next!=NULL){
		if (cur->value<cur->next->value){
			return false;
		}
		cur=cur->next;
	}
	return true;
}

bool DoublyLinkedList::insert_sorted_asc(DataType val){
	if (size_==0){
		return insert(val, 0);
	}
	else if (is_sorted_asc()){
		Node* cur = head_;
		int index=0;
		while (cur->value<val && index<size_){
			index++;
			if (cur->next)
				cur=cur->next;
		}
		return nsert (val, index);
	}
	return false;
}


bool DoublyLinkedList::insert_sorted_desc(DataType val)
{
	if (size_==0){
		insert(val, 0);
		return true;
	}
	else if (is_sorted_desc()){
		Node* cur = head_;
		int index=0;
		while (cur->value>val&&index<size_){
			index++;
			if (cur->next)
				cur=cur->next;
		}
		return insert (val, index);
	}
	return false;
}


void DoublyLinkedList::sort_asc()
{
	if (size_>1){
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (select(i)>select(j)){
					DataType temp=select(j);
					replace(j, select(i));
					replace(i, temp);
				}
			}
		}
	}
}

void DoublyLinkedList::sort_desc()
{
	if (size_>1){
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (select(i)<select(j)){
					DataType temp=select(j);
					replace(j, select(i));
					replace(i, temp);
				}
			}
		}
	}
}



