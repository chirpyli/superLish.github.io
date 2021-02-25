// #include"bstree.h"
// #include"dswtree.h"
// #include"avltree.h"
// #include"redblack.h"
// #include "selftree.h"
#include"heap.h"

int main() {
	// int data[] = {8, 3, 13, 1, 4, 6, 7, 11, 12, 18, 24, 29};
	int data[5] = {13, 10, 15, 5, 1};
	// STree<int> *t = new STree<int>();
	// for (auto i : data) {
	// 	t->insert(i);
	// }

	// t->breadthFirst();
	// t->search(13);
	// t->breadthFirst();
	// t->search(18);
	// t->breadthFirst();
	
	// t->inorder();
	// t->morrisInorder();
	// std::cout << endl;
	// t->preorder();
	// std::cout << endl;
	// t->morrisPreorder();
	// DswBST<int> *bt = new DswBST<int>(data, 6);
	// bt->dswBalance();
	// bt->breadthFirst();

	// mytree::RBTree* t = new mytree::RBTree();
	// for (auto i : data) {
	// 	t->insert(i);
	// 	t->print_tree();
	// }

	// t->remove(24);
	// t->print_tree();

	// SplayTree<int> *st = new SplayTree<int>();
	// st->insert(10);
	// st->insert(20);
	// st->insert(1);
	// st->insert(5);
	// st->insert(30);
	// st->breadthFirst();

	MaxHeap<int> *mh = new MaxHeap<int>(data, 5);
	// mh->push(1);
	// mh->print();
	// mh->push(10);
	// mh->push(100);
	// mh->push(30);
	// mh->print();
	// mh->pop();
	mh->print();


	return 0;
}

// void avl_test() {
// 	AVLTree<int>* at = new AVLTree<int>(data, sizeof(data)/sizeof(int));
// 	AVLTree<int>* at = new AVLTree<int>();
// 	at->insert(10);
// 	at->insert(20);
// 	at->insert(30);
// 	at->insert(40);
// 	at->insert(50);
// 	at->insert(25);
// 	at->insert(1);
// 	at->preOrder(at->getRoot());
// 	at->remove(20);
// 	std::cout << std::endl;
// 	at->preOrder(at->getRoot());
// }