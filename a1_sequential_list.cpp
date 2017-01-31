#include "a1_sequential_list.hpp"
#include "a1_tests.hpp"
#include <iostream>

using namespace std;
SequentialList::SequentialList(unsigned int cap)
{
	capacity_ = cap;
	data_ = new DataType[cap];
	size_ = 0;
}

SequentialList::~SequentialList()
{
	delete [] data_;

}

unsigned int SequentialList::size() const
{
	return this->size_;
}

unsigned int SequentialList::capacity() const
{
	return this->capacity_;
}

bool SequentialList::empty() const
{
	return this->size_ == 0;
}

bool SequentialList::full() const
{
	return this->size_ == this->capacity_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	DataType output = *(this->data_ + this->size_ - 1);
	if (index < this->size_ && index >= 0)
	{
		output = *(this->data_ + index);
	}
	return output;

}

unsigned int SequentialList::search(DataType val) const
{
	for (int i = 0; i < this->size_; i++)
	{
		if (*(this->data_ + i) == val)
		{
			return i;
		}
		
	}
	return this->size_;
}

void SequentialList::print() const
{
	for (int i = 0; i < this->size_; i++)
	{
		cout << *(this->data_ + i) << " ";
	}
	cout << "NULL" << endl;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	
	if (this->size_+1 <= this->capacity_ && index <= this->size_){
		for (int i=this->size_;i>index;i--){
			*(this->data_+i)=*(this->data_+(i-1));
		}
		*(this->data_+index)=val;
		this->size_++;
		return true;
	}
	return false;
}

bool SequentialList::insert_front(DataType val)
{
	return this->insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
	return this->insert(val, this->size_);
}

bool SequentialList::remove(unsigned int index)
{
	if (index < this->size_){
		for (int i = index; i < this->size_; i++) {
			*(this->data_+i)=*(this->data_+(i+1));
		}
		*(this->data_+ this->size_ - 1) = NULL;
		this->size_--;
		return true;
	}
	return false;
}

bool SequentialList::remove_front()
{
	return this->remove(0);
}

bool SequentialList::remove_back()
{
	return this->remove(this->size_ - 1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if (this->size_ > index)
	{
		*(this->data_ + index) = val;
		return true;
	}
	return false;
}


bool SequentialList::insert_sorted_asc(DataType val)
{
	int index = 0;
	if (size_!=capacity_)
	{
		while (*(this->data_ + index) < val)
		{
			index++;
		}
		this->insert(val, index);
		return true;
	}
	return false;
}

bool SequentialList::insert_sorted_desc(DataType val)
{
	int index = 0;
	if (size_!=capacity_)
	{
		while (*(this->data_ + index) > val)
		{
			index++;
		}
		this->insert(val, index);
		return true;
	}
	return false;	
}


bool SequentialList::is_sorted_asc() const
{
	if (size_!=0){
		int prev = *this->data_;
		for (int i= 0; i < this->size_ ; i++)
		{
			if (prev>*(data_+i))
				return false;
			else
				prev = *(data_+i);
		}
	}
	return true;
}

bool SequentialList::is_sorted_desc() const
{
	if (size_!=0){
		int prev = *this->data_;
		for (int i= 0; i < this->size_ ; i++)
		{
			if (prev<*(data_+i))
				return false;
			else
				prev = *(data_+i);
		}
	}
	return true;
}

void SequentialList::sort_asc()
{
	if (size_!=0){
		int cur = *data_;
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (cur>*(data_+1)){
					int temp=cur;
					cur=*(data_+1);
					*(data_+1)=temp;
				}
				cur= *(data_+1);
			}
			
		}
	}
}

void SequentialList::sort_desc()
{
	if (size_!=0){
		int cur = *data_;
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (cur<*(data_+1)){
					int temp=cur;
					cur=*(data_+1);
					*(data_+1)=temp;
				}
				cur= *(data_+1);
			}
			
		}
	}
}


int main ()
{
	SequentialList* a = new SequentialList(5);
	for (int i= 5; i > 0; i--)
	{
		a->insert_back(i);
	}
	a->print();
	cout << a->is_sorted_desc();
	a->sort_asc();
	a->print();
}

