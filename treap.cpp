#include <memory>
#include <iostream>
#include <cstdlib>

using namespace std;

struct _Node;

using Node = unique_ptr<_Node>;

struct _Node {
    _Node(int v, int p)
        : _value(v)
        , _priority(p) {
    }

    int _value;
    int _priority;
    Node _left, _right;
};

pair<Node, Node> split(Node&& node, int value) {
    if(!node)
        return {};

    if(node->_value < value) {
        auto p = split(move(node->_right), value);
        node->_right = move(p.first);
        return {move(node), move(p.second)};
    }
    else {
        auto p = split(move(node->_left), value);
        node->_left = move(p.second);
        return {move(p.first), move(node)};
    }
}

void insert(Node& node, int value, int priority = rand()) {
    if(!node) {
        node = make_unique<_Node>(value, priority);
        return;
    }

    if(node->_priority > priority) {
        if(node->_value > value)
            insert(node->_left, value, priority);
        else
            insert(node->_right, value, priority);
    }
    else {
        auto p = split(move(node), value);
        node = make_unique<_Node>(value, priority);
        node->_left = move(p.first);
        node->_right = move(p.second);
    }
}

Node merge(Node&& left, Node&& right) {
    if(!left)
        return move(right);

    if(!right)
        return move(left);

    if(left->_priority > right->_priority) {
        left->_right = merge(move(left->_right), move(right));
        return move(left);
    }
    else {
        right->_left = merge(move(left), move(right->_left));
        return move(right);
    }
}

void remove(Node& node, int value) {
    if(!node)
        return;
    if(node->_value > value)
        remove(node->_left, value);
    else if(node->_value < value)
        remove(node->_right, value);
    else {
        node = merge(move(node->_left), move(node->_right));
    }
}

void print(Node& node) {
    if(!node)
        return;
    print(node->_left);
    cout << node->_value << "\t" << node->_priority << endl;
    print(node->_right);
}

int main(int argc, char *argv[])
{
    Node tree;
    insert(tree, 1);
    insert(tree, 2);
    insert(tree, 3);
    insert(tree, 4);
    insert(tree, 5);
    insert(tree, 6);
    insert(tree, 7);
    insert(tree, 8);
    insert(tree, 9);
    insert(tree, 10);
    print(tree);
    cout << endl;

    remove(tree, 2);
    remove(tree, 1);
    remove(tree, 5);
    print(tree);
    return 0;
}
