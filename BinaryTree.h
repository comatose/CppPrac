/*
 * BinaryTree.h
 *
 *  Created on: May 6, 2010
 *      Author: comatose
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <iostream>
#include "Queue.h"
#include "Stack.h"

template<class T>
class BinaryTree{
private:
	class Node{
		friend class BinaryTree<T>;
		Node(const T& value, Node* const left, Node* const right): value_(value), left_(left), right_(right){}
		T value_;
		Node* left_;
		Node* right_;
	};

public:
	struct NotFound{};

	BinaryTree(): root_(NULL){}

	BinaryTree& operator=(const BinaryTree& rhs){
		if(this != &rhs){
			removeAll();
			copy(rhs.root_, root_);
		}
		return *this;
	}

	BinaryTree(const BinaryTree& rhs): root_(NULL){
		*this = rhs;
	}

	T& findMin() const {
		for(Node* node = root_; node != NULL; node = node->left_){
			if(node->left_ == NULL)
				return node->value_;
		}
		throw NotFound();
	}

	T& findMax() const {
		for(Node* node = root_; node != NULL; node = node->right_){
			if(node->right_ == NULL)
				return node->value_;
		}
		throw NotFound();
	}

	bool find(const T& value) const{
		return find(value, root_);
	}

	void insert(const T& value){
		insert(value, root_);
	}

	void remove(const T& value){
		remove(value, root_);
	}

	void removeAll(){
		removeAll(root_);
		root_ = NULL;
	}

	void print(std::ostream& os) const {
		print(os, root_, 0);
	}

	void BFS(std::ostream& os) const {
		Queue<Node*> queue(100);
		queue.enqueue(root_);
		while(!queue.isEmpty()){
			Node* node = queue.dequeue();
			if(node == NULL)
				continue;
			queue.enqueue(node->left_);
			queue.enqueue(node->right_);
			os << node->value_ << " ";
		}
	}

	void preorder(std::ostream& os) const {
		Stack<Node*> stack(100);
		stack.push(root_);
		while(!stack.isEmpty()){
			Node* node = stack.top();
			stack.pop();
			if(node == NULL)
				continue;
			os << node->value_ << " ";
			stack.push(node->right_);
			stack.push(node->left_);
		}
	}

	void inorder(std::ostream& os) const {
		Stack<Node*> cs(100);
		Stack<bool> vs(100);
		cs.push(root_);
		vs.push(false);
		while(!cs.isEmpty()){
			Node* node = cs.top();
			cs.pop();
			bool visited = vs.top();
			vs.pop();
			if(node == NULL)
				continue;

			if(visited){
				os << node->value_ << " ";
				continue;
			}
			cs.push(node->right_);
			vs.push(false);

			cs.push(node);
			vs.push(true);

			cs.push(node->left_);
			vs.push(false);
		}
	}

	void postorder(std::ostream& os) const {
		Stack<Node*> cs(100);
		Stack<bool> vs(100);
		cs.push(root_);
		vs.push(false);
		while(!cs.isEmpty()){
			Node* node = cs.top();
			cs.pop();
			bool visited = vs.top();
			vs.pop();
			if(node == NULL)
				continue;

			if(visited){
				os << node->value_ << " ";
				continue;
			}

			cs.push(node);
			vs.push(true);

			cs.push(node->right_);
			vs.push(false);

			cs.push(node->left_);
			vs.push(false);
		}
	}

	void postorder2(std::ostream& os) const {
		postorderR(os, root_);
	}

	void postorderR(std::ostream& os, Node* root) const {
		if(root == NULL)
			return;
		postorderR(os, root->left_);
		postorderR(os, root->right_);
		os << root->value_ << ' ';
	}

	static void test(){
		BinaryTree<int> tree1;
		tree1.insert(6);
		tree1.insert(2);
		tree1.insert(8);
		tree1.insert(1);
		tree1.insert(5);
		tree1.insert(3);
		tree1.insert(4);
		tree1.BFS(std::cout);
		std::cout << std::endl;

		tree1.inorder(std::cout);
		std::cout << std::endl;

		tree1.preorder(std::cout);
		std::cout << std::endl;

		tree1.postorder(std::cout);
		std::cout << std::endl;
}

private:
	T& findMin(const Node* const subroot) const {
		for(const Node* node = subroot; node != NULL; node = node->left_){
			if(node->left_ == NULL)
				return node->value_;
		}
		throw NotFound();
	}

	bool find(const T& value, const Node* const node) const{
		if(node == NULL)
			return false;

		if(node->value_ == value)
			return true;
		else if(node->value_ > value)
			return find(value, node->left_);
		else
			return find(value, node->right_);
	}

	void insert(const T& value, Node* &node){
		if(node == NULL)
			node = new Node(value, NULL, NULL);
		else if(node->value_ > value)
			insert(value, node->left_);
		else if(node->value_ < value)
			insert(value, node->right_);
	}

	void remove(const T& value, Node* &node){
		if(node == NULL)
			return;

		if(node->value_ > value){
			remove(value, node->left_);
			return;
		}
		else if(node->value_ < value){
			remove(value, node->right_);
			return;
		}

		if(node->left_ == NULL && node->right_ == NULL){
			delete node;
			node = NULL;
		}
		else if(node->right_ == NULL){
			Node* tbg = node;
			node = node->left_;
			delete tbg;
		}
		else{
			node->value_ = findMin(node->right_);
			remove(node->value_, node->right_);
		}
	}

	void print(std::ostream& os, const Node* const node, int level) const {
		if(node == NULL)
			return;

		print(os, node->left_, level + 1);
		for(int i = 0; i < level; ++i){
			os << " ";
		}
		os << node->value_ << std::endl;
		print(os, node->right_, level + 1);
	}

	void removeAll(Node* &node){
		if(node == NULL)
			return;
		removeAll(node->left_);
		removeAll(node->right_);
		delete node;
	}

	void copy(const Node* const src, Node* &dst){
		if(src == NULL)
			return;

		dst = new Node(src->value_, NULL, NULL);
		copy(src->left_, dst->left_);
		copy(src->right_, dst->right_);
	}

	Node* root_;
};

#endif /* BINARYTREE_H_ */
