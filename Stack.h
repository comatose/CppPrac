#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstddef>
#include <iostream>

template<class T>
class Stack{
private:
	int head_;
	int size_;
	T* objects_;

public:
	explicit Stack(int size): head_(0), size_(size), objects_(NULL){
		objects_ = new T[size];
	}

	Stack(const Stack& rhs): size_(0), objects_(NULL){
		*this = rhs;
	}

	~Stack(){
		delete[] objects_;
	}

	Stack& operator=(const Stack& rhs){
		if(this != &rhs){
			if(size_ != rhs.size_){
				delete objects_;
				size_ = rhs.size_;
				objects_ = new T[size_];
			}
			head_ = rhs.head_;
			for(int i = 0; i < rhs.head_; ++i){
				objects_[i] = rhs.objects_[i];
			}
		}
		return *this;
	}

	bool isEmpty() const {
		return head_ == 0;
	}

	bool isFull() const {
		return head_ == size_;
	}

	const T& top() const{
		return objects_[head_ - 1];
	}

	void pop(){
		head_--;
	}

	void push(const T& value){
		objects_[head_++] = value;
	}

	static void test(){
		Stack<int> stack(5);
		std::cout << (stack.isEmpty()?"Pass":"Failed") << std::endl;
		stack.push(1);
		stack.push(2);
		stack.push(3);
		stack.push(4);
		stack.push(5);
		std::cout << (stack.isFull()?"Pass":"Failed") << std::endl;

		Stack<int> stack2 = stack;
		while(!stack2.isEmpty()){
			std::cout << stack2.top() << ' ';
			stack2.pop();
		}
		std::cout << std::endl;
	}
};

#endif
