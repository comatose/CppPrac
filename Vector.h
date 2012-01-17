#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstddef>

class OutOfBound{};

template<class T>
class Vector{
public:
	Vector(): size_(0), objects_(NULL) {}

	~Vector(){
		delete[] objects_;
	}

	explicit Vector(int size): size_(size){
		objects_ = new T[size];
	}

	Vector(const Vector& rhs): objects_(NULL){
		*this = rhs;
	}

	Vector& operator=(const Vector& rhs){
		if(this != &rhs){
			delete[] objects_;
			size_ = rhs.size();
			objects_ = new T[size_];
			for(int i = 0; i < size_; ++i){
				objects_[i] = rhs[i];
			}
		}
		return *this;
	}

	void Resize(int size){
		T* new_objects = new T[size];
		int count = (size > size_)?size_:size;
		for(int i = 0; i < count; ++i){
			objects_[i] = new_objects[i];
		}
		delete[] objects_;
		objects_ = new_objects;
		size_ = size;
	}

	T& operator[](int index){
		if(index < 0 || index >= size_){
			throw OutOfBound();
		}
		return objects_[index];
	}

	const T& operator[](int index) const {
		if(index < 0 || index >= size_){
			throw OutOfBound();
		}
		return objects_[index];
	}

	int size() const {
		return size_;
	}

private:
	int size_;
	T* objects_;
};

#endif
