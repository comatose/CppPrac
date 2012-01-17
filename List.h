#ifndef _LIST_H_
#define _LIST_H_

#include <cstddef>
#include <iostream>

template<class T>
class List{
private:
	class Node{
	public:
		Node(const T& value, Node* next ): value_(value), next_(next){}
		T value_;
		Node* next_;
	};

	Node* head_;

	Node* findPrevious(const Node* node) const{
		Node* prev = NULL;
		for(Node* cur = head_; cur != NULL; cur = cur->next_){
			if(cur == node)
				return prev;
			prev = cur;
		}
		return prev;
	}

	void rcopy(Node* &dst, Node* src){
		if(src == NULL)
			return;
		dst = new Node(src->value_, NULL);
		rcopy(dst->next_, src->next_);
	}

public:
	List(): head_(NULL){}
	List(const List& rhs): head_(NULL){
		*this = rhs;
	}
	List& operator=(const List& rhs){
		if(this != &rhs){
			eraseAll();
			rcopy(head_, rhs.head_);
		}
		return *this;
	}
	~List(){
		eraseAll();
	}

//	class Iterator : public std::iterator<std::forward_iterator_tag, T>{
	class Iterator{
		friend class List<T>;
	public:
		Iterator(Node* n): node_(n){}
		T& operator*(){
			return node_->value_;
		}
		Iterator& operator++(){
			if(node_ != NULL)
				node_ = node_->next_;
			return *this;
		}
		bool operator== (const Iterator& rhs) const{
			return node_ == rhs.node_;
		}
		bool operator!= (const Iterator& rhs) const{
			return !(*this == rhs);
		}

	private:
		Node* node_;
	};
//	typedef Iterator iterator;

	void print(std::ostream& os){
		for(Iterator it = begin(); it != end(); ++it){
			os << *it << ' ';
		}
		os << std::endl;
	}

	Iterator insert(const Iterator& pos, T v){
		Node* prev = findPrevious(pos.node_);
		if(prev == NULL){
			head_ = new Node(v, head_);
			return head_;
		}
		else{
			prev->next_ = new Node(v, prev->next_);
			return prev->next_;
		}
	}

	Iterator begin() const{
		return head_;
	}

	Iterator end() const{
		return NULL;
	}

	Iterator find(const T& v) const{
		for(Node* node = head_; node != NULL; node = node->next_){
			if(node->value_ == v)
				return node;
		}
		return NULL;
	}

	Iterator erase(const Iterator& pos){
		Node* prev = findPrevious(pos.node_);
		Node* next = pos.node_->next_;
		if(prev == NULL){
			head_ = next;
			delete pos.node_;
		}
		else{
			prev->next_ = next;
			delete pos.node_;
		}
		return next;
	}

	void eraseAll(){
		Node* next;
		while(head_ != NULL){
			next = head_->next_;
			delete head_;
			head_ = next;
		}
	}

	bool isEmpty() const{
		return head_ == NULL;
	}

	int size() const{
		int i = 0;
		for(Node* node = head_; node != NULL; node = node->next_, ++i);
		return i;
	}

	static void test(){
		List<int> list;
		for(int i = 0; i < 10; ++i)
			list.insert(list.begin(), i);
		list.print(std::cout);

		List<int> list2 = list;
		list2.erase(list2.find(3));
		list2.insert(list2.end(), 100);

		list.eraseAll();
		list.print(std::cout);
		list2.print(std::cout);
	}
};

#endif
