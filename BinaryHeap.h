/*
 * BinaryHeap.h
 *
 *  Created on: Jun 16, 2010
 *      Author: comatose
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

template<class T>
class BinaryHeap{
public:
	void insert(const T& value){
		elems_.push_back(value);
		siftup(elems_.size() - 1);
	}

	T extract(){
		T result = elems_.front();
		elems_[0] = elems_.back();
		elems_.pop_back();
		siftdown(0);
		return result;
	}

	bool isEmpty(){
		return elems_.empty();
	}

	int size(){
		return elems_.size();
	}

	static void test(){
		BinaryHeap<int> heap;
		heap.insert(1);
		heap.insert(20);
		heap.insert(12);
		heap.insert(32);
		heap.insert(2);
		heap.insert(13);
		heap.insert(24);
		heap.insert(6);

		BinaryHeap<int> heap2 = heap;
		while(!heap2.isEmpty()){
			std::cout << heap2.extract() << " ";
		}
	}

private:
	std::vector<T> elems_;

	int parent(int index){
		return (index - 1) / 2;
	}

	int leftchild(int index){
		return index * 2 + 1;
	}

	int rightchild(int index){
		return leftchild(index) + 1;
	}

	void siftup(int index){
		int pi;
		while(index > 0){
			pi = parent(index);
			if(elems_[index] < elems_[pi]){
				break;
			}
			std::swap(elems_[index], elems_[pi]);
			index = pi;
		}
	}

	void siftdown(int index){
		int li, ri, ni;
		while(1){
			li = leftchild(index);
			if(li >= elems_.size()){
				break;
			}
			ri = rightchild(index);
			if(ri >= elems_.size() || elems_[li] > elems_[ri]){
				ni = li;
			}
			else{
				ni = ri;
			}
			if(elems_[index] > elems_[ni])
				break;
			std::swap(elems_[index], elems_[ni]);
			index = ni;
		}
	}
};

#endif /* BINARYHEAP_H_ */
