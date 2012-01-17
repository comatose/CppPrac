#ifndef TREE_H
#define TREE_H

#include <stack>

template<class T>
class TreeNode{
public:
	TreeNode(T v, TreeNode<T>* l, TreeNode<T>* r): value(v), left(l), right(r){}
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;

	void inOrder(){
		cout << value << ' ';
		if(left != NULL)
			left->inOrder();
		if(right != NULL)
			right->inOrder();
	}

	void inOrder2(){
		TreeNode<T>* n = this;
		stack< TreeNode<T>* > s;
		s.push(n);
		while(!s.empty()){
			n = s.top();
			s.pop();
			cout << n->value << ' ';
			if(n->right != NULL){
				s.push(n->right);
			}
			if(n->left != NULL){
				s.push(n->left);
			}
		}
	}

	static void test(){
		typedef TreeNode<T> Node;
		Node* root;
		root = new Node(100,
				new Node(50,
						new Node(25, NULL, NULL),
						new Node(75, NULL, NULL)),
				new Node(150,
						new Node(125,
								new Node(110, NULL, NULL),
								NULL),
						new Node(175, NULL, NULL)));

		root->inOrder2();
	}
};

#endif
