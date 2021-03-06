//Dustin Hu and Jimmy Xu

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
	return size_;
}

unsigned int SequentialList::capacity() const
{
	return capacity_;
}

bool SequentialList::empty() const
{
	return size_ == 0;
}

bool SequentialList::full() const
{
	return size_ == capacity_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	DataType output = *(data_ + size_ - 1);
	if (index < size_ && index >= 0)
	{
		output = *(data_ + index);
	}
	return output;

}

unsigned int SequentialList::search(DataType val) const
{
	for (int i = 0; i < size_; i++)
	{
		if (data_[i] == val)
		{
			return i;
		}
		
	}
	return size_;
}

void SequentialList::print() const
{
	for (int i = 0; i < size_; i++)
	{
		cout <<data_[i] << " ";
	}
	cout<<endl;
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	
	if (size_+1 <= capacity_ && index <= size_){
		for (int i=size_;i>index;i--){
			*(data_+i)=*(data_+(i-1));
		}
		*(data_+index)=val;
		size_++;
		return true;
	}
	return false;
}

bool SequentialList::insert_front(DataType val)
{
	return insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
	return insert(val, size_);
}

bool SequentialList::remove(unsigned int index)
{
	if (index < size_){
		for (int i = index; i < size_; i++) {
			data_[i]=data_[i+1];
		}
		data_[size_-1] = NULL;
		size_--;
		return true;
	}
	return false;
}

bool SequentialList::remove_front()
{
	return remove(0);
}

bool SequentialList::remove_back()
{
	return remove(size_ - 1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if (size_ > index)
	{
		data_[index] = val;
		return true;
	}
	return false;
}


bool SequentialList::insert_sorted_asc(DataType val)
{
	if (size_==0){
		insert(val,0);
		return true;
	}
	else if (is_sorted_asc()){
		int index = 0;
		if (size_!=capacity_)
		{
			while (data_[index] < val && index<size_)
			{
				index++;
			}
			insert(val, index);
			return true;
		}
	}
	return false;
}

bool SequentialList::insert_sorted_desc(DataType val)
{
	if (size_==0){
		insert(val,0);
		return true;
	}
	else if (is_sorted_desc()){
		int index = 0;
		if (size_!=capacity_)
		{
			while (data_[index] > val && index<size_)
			{
				index++;
			}
			insert(val, index);
			return true;
		}
	}
	return false;	
}


bool SequentialList::is_sorted_asc() const
{
	if (size_>1){
		int prev = data_[0];
		for (int i= 0; i < size_ ; i++)
		{
			if (prev>data_[i])
				return false;
			else
				prev = data_[i];
		}
	}
	return true;
}

bool SequentialList::is_sorted_desc() const
{
	if (size_>1){
		int prev = data_[0];
		for (int i= 0; i < size_ ; i++)
		{
			if (prev<data_[i])
				return false;
			else
				prev = data_[i];
		}
	}
	return true;
}

void SequentialList::sort_asc()
{
	if (size_>1){
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (data_[i]>data_[j]){
					DataType temp=data_[j];
					data_[j]=data_[i];
					data_[i]=temp;
				}
			}
			
		}
	}
}

void SequentialList::sort_desc()
{
	if (size_!=0){
		for(int i=0;i<size_;i++){
			for(int j=i;j<size_;j++){
				if (data_[i]<data_[j]){
					DataType temp=data_[j];
					data_[j]=data_[i];
					data_[i]=temp;
				}
			}
		}
	}
}

