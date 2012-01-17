#ifndef QUEUE_H_
#define QUEUE_H_

#include <cstddef>
#include <iostream>

template<class T>
class Queue{
public:
	struct Overflow{};
	struct Underflow{};

	explicit Queue(int size): size_(size + 1), front_(0), back_(0){
		objects_ = new T[size_];
	}

	Queue(const Queue& rhs): objects_(NULL){
		*this = rhs;
	}

	~Queue(){
		delete[] objects_;
	}

	Queue& operator=(const Queue& rhs){
		if(this != &rhs){
			delete[] objects_;
			size_ = rhs.size_;
			front_ = rhs.front_;
			back_ = rhs.back_;
			objects_ = new T[size_];
			for(int i = 0; i < size_; ++i){
				objects_[i] = rhs.objects_[i];
			}
		}
		return *this;
	}

	void enqueue(const T& value){
		if(isFull()){
			throw Overflow();
		}
		objects_[back_] = value;
		if(++back_ == size_)
			back_ = 0;
	}

	T& dequeue(){
		if(isEmpty()){
			throw Underflow();
		}
		T& obj = objects_[front_];
		if(++front_ == size_)
			front_ = 0;
		return obj;
	}

	bool isEmpty(){
		return front_ == back_;
	}

	bool isFull(){
		return (front_ == (back_ + 1)) || (front_ == 0 && back_ == (size_ - 1));
	}

	static void test(){
		Queue queue(5);
		for(int i = 0; !queue.isFull(); ++i){
			queue.enqueue(i);
		}
		std::cout << queue.dequeue() << ' ';
		for(int i = 0; i < 20; ++i){
			queue.enqueue(i);
			std::cout << queue.dequeue() << ' ';
		}
		std::cout << std::endl;
		Queue queue2 = queue;
		while(!queue2.isEmpty()){
			std::cout << queue2.dequeue() << ' ';
		}
		std::cout << std::endl;
	}

private:
	int size_;
	int front_;
	int back_;
	T* objects_;
};

#endif /* QUEUE_H_ */
