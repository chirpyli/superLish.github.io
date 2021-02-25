#include"treap.h"
// #include"common.h"

int main() {
    Treap<int>* t = new Treap<int>();
    t->insert(10);
    t->insert(20);
    t->insert(11);
    t->insert(30);
    t->breadthFirst();


    t->remove(20);
    cout << endl;
    t->breadthFirst();

    // BST<int, Node<int>>* t = new BST<int, Node<int>>();
    // t->insert(1);
    // t->breadthFirst();


    return 0;
}