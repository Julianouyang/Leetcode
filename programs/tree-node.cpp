#include<iostream>
#include<vector>
#include<memory>
#include<stdlib.h>

using namespace std;

class Node
{
public:
    Node() : _v(0), _parent(nullptr) {};
    Node(int val) : _v(val), _parent(nullptr) {};
    Node(int val, Node* parent) : _v(val), _parent(parent) {
        _parent->setChild(this);
    };

    ~Node() {
        cout << "Deleting node " + to_string(_v) << endl;
        delete _parent;
        for (auto it = _children.begin(); it != _children.end(); it++) {
            (*it)->_parent = nullptr;
            delete *it;
        }
        _children.clear();
        cout << "Node " + to_string(_v) + " deleted" << endl;
    }
    /**
     * @brief Set a node as the parent of current node
     * 1. Input node is already the parent of current node (O)
     * 2. Input node is a child of current node (X)
     * 3. Input node is a subling of current node (X)
     * @param parent
     * @return true
     * @return false
     */
    bool setParent(Node* parent) {
        if (checkParent(this, parent)) {
            _parent = parent;
            _parent->_children.push_back(this);
            return true;
        }
        return false;
    }

    bool setChild(Node* child) {
        if (checkChild(this, child)) {
            _children.push_back(child);
            child->_parent = this;
            return true;
        }
        return false;
    }

    void print() {
        cout << to_string(_v) + "->";
        for (int i = 0; i < _children.size(); i++) {
            _children[i]->print();
        }
        cout << endl;
    }

    string getValue() {
        return to_string(_v);
    }

protected:
    int _v;
    Node* _parent;
    vector<Node*> _children;

private:
    // check if input node is a child of this node
    bool checkParent(Node* root, Node* node) {
        if (!node) return true;
        if (node == root) return false;
        for (int i = 0; i < _children.size(); i++) {
            bool res = checkParent(_children[i], node);
            if (!res) return false;
        }
        return true;
    }

    // check if input node is a parent of this node
    bool checkChild(Node* root, Node* node) {
        while (root) {
            if (root == node) return false;
            root = root->_parent;
        }
        return true;
    }
};

class SmartNode
{
public:
    SmartNode(int val) : _v(val) {};
    SmartNode(int val, shared_ptr<SmartNode> parent) : _v(val), _parent(parent) {};

    void setParent(shared_ptr<SmartNode> parent) {
        _parent = parent;
        parent->_children.push_back(make_shared<SmartNode>(*this));
    }

    void setChildren(shared_ptr<SmartNode> child) {
        _children.push_back(child);
        child->_parent = make_shared<SmartNode>(*this);
    }

    void print() {
        cout << to_string(_v) + "->";
        for (int i = 0; i < _children.size(); i++) {
            _children[i]->print();
        }
        cout << endl;
    }

protected:
    int _v;
    shared_ptr<SmartNode> _parent;
    vector<shared_ptr<SmartNode>> _children;
};

int main() {
    // generate manually
    Node *root = new Node(3);
    Node *n1 = new Node(5, root);
    Node *n2 = new Node(6);
    n1->setChild(n2);
    Node *n3 = new Node(8, n1);
    if (n3->setChild(root)) {
        cout << "set child " + root->getValue() + " to " + n3->getValue() << endl;
    }
    root->print();
    delete root;

    // smart pointer
    auto r = make_shared<SmartNode>(1);
    auto s1 = make_shared<SmartNode>(2);
    auto s2 = make_shared<SmartNode>(9);
    r->setChildren(s1);
    r->setChildren(s2);
    auto s3 = make_shared<SmartNode>(7);
    s2->setChildren(s3);
    r->print();

    return 0;
}
