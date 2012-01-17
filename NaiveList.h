#ifndef _NAIVELIST_H_
#define _NAIVELIST_H_

#include <cstddef>
#include <iostream>

template<class T>
class ListNode{
public:
	ListNode(ListNode<T>* n, const T& v): next_(n), value_(v){}
	ListNode<T>* next_;
	T value_;
};

template<class T>
bool insertHead(ListNode<T>* &head, const T& value){
	head  = new ListNode<T>(head, value);
	return head != NULL;
}

template<class T>
ListNode<T>* find(ListNode<T>* head, const T& value){
	while(head != NULL){
		if(head->value_ == value)
			return head;
		head = head->next_;
	}
	return NULL;
}

template<class T>
ListNode<T>* findPrev(ListNode<T>* head, ListNode<T>* node){
	ListNode<T>* prev = NULL;
	while(head != NULL){
		if(head == node)
			return prev;
		prev = head;
		head = head->next_;
	}
	return NULL;
}

template<class T>
bool deleteNode(ListNode<T>* &head, ListNode<T>* node){
	if(head == NULL)
		return false;
	ListNode<T>* prev = findPrev(head, node);
	if(prev == NULL){
		head = node->next_;
	}
	else{
		prev->next_ = node->next_;
	}
	delete node;
	return true;
}

template<class T>
void deleteList(ListNode<T>* &head){
	ListNode<T>* next;
	while(head != NULL){
		next = head->next_;
		delete head;
		head = next;
	}
}

template<class T>
ListNode<T>* findMToLast(ListNode<T>* head, int m){
	ListNode<T>* ahead = head;
	for(int i = 0; i <= m; ++i){
		if(ahead == NULL)
			return NULL;
		ahead = ahead->next_;
	}
	while(ahead != NULL){
		head = head->next_;
		ahead = ahead->next_;
	}
	return head;
}

inline void test(){
	ListNode<int>* head = NULL;
	insertHead(head, 23);
	insertHead(head, 2);
	insertHead(head, 3);
	insertHead(head, 1);
	insertHead(head, 13);
	insertHead(head, 34);

	std::cout << find(head, 23)->value_ << std::endl;
	std::cout << find(head, 2)->value_ << std::endl;
	std::cout << find(head, 3)->value_ << std::endl;
	std::cout << find(head, 1)->value_ << std::endl;
	std::cout << find(head, 13)->value_ << std::endl;
	std::cout << find(head, 34)->value_ << std::endl;

	deleteNode(head, find(head, 3));
	std::cout << (find(head, 3) == NULL?"PASS":"FAILED") << std::endl;

	std::cout << findMToLast(head, 0)->value_ << std::endl;
	std::cout << findMToLast(head, 1)->value_ << std::endl;
	std::cout << findMToLast(head, 2)->value_ << std::endl;
	std::cout << findMToLast(head, 3)->value_ << std::endl;
	std::cout << findMToLast(head, 4)->value_ << std::endl;
	std::cout << (findMToLast(head, 5) == NULL?"PASS":"FAILED") << std::endl;

	deleteList(head);
	std::cout << (find(head, 23) == NULL?"PASS":"FAILED") << std::endl;
}

#endif
