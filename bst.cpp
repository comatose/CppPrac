#include <memory>
#include <iostream>

using namespace std;

struct _Node;

using Node = unique_ptr<_Node>;

struct _Node {
    _Node(int v) : _value(v) {}
    Node _left, _right;
    int _value;
};

void insert(Node& node, int value) {
    if(!node) {
        node = make_unique<_Node>(value);
        return;
    }

    if(node->_value > value) {
        insert(node->_left, value);
    }
    else {
        insert(node->_right, value);
    }
}

Node& findMin(Node& node) {
    return (node->_left) ? findMin(node->_left) : node;
}

void remove(Node& node, int value) {
    if(!node)
        return;
    if(node->_value > value) {
        remove(node->_left, value);
    }
    else if(node->_value < value) {
        remove(node->_right, value);
    }
    else {
        if(node->_left && node->_right) {
            auto& alt = findMin(node->_right);
            node->_value = alt->_value;
            remove(node->_right, node->_value);
        }
        else if(node->_left){
            node = move(node->_left);
        }
        else {
            node = move(node->_right);
        }
    }
}

void print(Node& node) {
    if(!node)
        return;
    print(node->_left);
    cout << node->_value << endl;
    print(node->_right);
}

int main(int argc, char *argv[])
{
    Node tree;
    insert(tree, 5);
    insert(tree, 2);
    insert(tree, 12);
    insert(tree, -4);
    insert(tree, 3);
    insert(tree, 9);
    insert(tree, 21);
    insert(tree, 19);
    insert(tree, 25);

    remove(tree, 12);
    remove(tree, 21);
    remove(tree, 25);
    print(tree);
    return 0;
}
