#ifndef BST_h
#define BST_h

#include "BSTNode.h"
#include "Queue.h"
#include <ostream>

template <typename T>
class BST
{
private:
	BSTNode<T>* root = nullptr;
	int nodes;
	
	void insert(BSTNode<T>*, T);

	void extract(BSTNode<T>*, BSTNode<T>*);
	BSTNode<T>* deleteNode(BSTNode<T>*);
	BSTNode<T>* moveChildren(BSTNode<T>*, T);

	BSTNode<T>* find(BSTNode<T>*, T);
	int findDepth(BSTNode<T>*);

public:
	~BST();
	void destroyTree(BSTNode<T>*);

	void add(T data); // set root if root, else call insert
	int nodesCount();

	bool remove(T data);
	int depth();

	BSTNode<T>* getRootptr();

	void preOrder(BSTNode<T>*, std::ofstream &);
	void postOrder(BSTNode<T>*, std::ofstream &);
	void inOrder(BSTNode<T>*, std::ofstream &);
	void breadthFirst(BSTNode<T>*, std::ofstream &);
};

template<typename T>
void BST<T>::insert(BSTNode<T> *root, T data)
{
	if (root->getData() > data) {
		if (!root->left) {
			root->left = new BSTNode<T>(data);
			nodes++;
		}
		else {
			insert(root->left, data);
		}
	}
	else {
		if (!root->right) {
			root->right = new BSTNode<T>(data);
			nodes++;
		}
		else {
			insert(root->right, data);
		}
	}
}

template<typename T>
void BST<T>::extract(BSTNode<T>* root, BSTNode<T>* nodeToDelete)
{
	if (root == nullptr) {
		return root;
	}
	if (nodeToDelete->getData() < root->getData()) {
		root->setLeft(extract(root->getLeft(), nodeToDelete));
	}
	else if (root->getData() < nodeToRemove->getData()) {
		root->setRight(extract(root->getRight(), nodeToDelete));
	}
	else {
		root = deleteNode(root);
	}
	return root;
}

template<typename T>
BSTNode<T>* BST<T>::deleteNode(BSTNode<T>* nodeToDelete)
{
	if (nodeToDelete->isLeaf()) {
		delete nodeToDelete;
		nodes--;
		return nullptr;
	}
	else if (nodeToDelete->getLeft() == nullptr) {
		BSTNode<T> temp = nodeToDelete->getRight();
		delete nodeToDelete;
		nodes--;
		return temp;
	}
	else if (nodeToDelete->getRight() == nullptr) {
		BSTNode<T> temp = nodeToDelete->getLeft();
		delete nodeToDelete;
		nodes--;
		return temp;
	}
	else {
		T temp;
		nodeToDelete->setLeft(moveChildren(nodeToDelete->getRight(), temp));
		nodeToDelete->setData(temp);
		return nodeToDelete;
	}
}

template<typename T>
BSTNode<T>* BST<T>::moveChildren(BSTNode<T>* root, T newData)
{
	if (root->getRight() == nullptr) {
		newData = root->getData;
		return deleteNode(root);
	}
	else {
		root->setRight(moveChildren(root->getRight(), newData));
		return root;
	}
	return NULL;
}

template<typename T>
BSTNode<T>* BST<T>::find(BSTNode<T>* root, T nodeToFind)
{
	if (this->root) {
		if (root->getData() == nodeToFind) {
			return root;
		}
		else if (!root(isLeaf)) {
			if (root->getData() < nodeToFind)
				return (find(root->getRight(), nodeToFind));
			else
				return (find(root->getLeft(), nodeToFind));
		}
		else return nullptr;
	}
	else {
		return this->root;
	}
}

template<typename T>
int BST<T>::findDepth(BSTNode<T>* root)
{
	if (!root)
		return 0;
	else return (1 + max(findDepth(root->left), findDepth, root->right));
}

template<typename T>
BST<T>::~BST()
{
	destroyTree(root);
}

template<typename T>
void BST<T>::destroyTree(BSTNode<T>* root)
{
	if (root) {
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
		root = nullptr;
		nodes = 0;
	}
}

template<typename T>
void BST<T>::add(T data)
{
	if (root) {
		this->insert(this->root, data);
	}
	else {
		root = new BSTNode<T>(data);
		nodes = 1;
	}
}

template<typename T>
int BST<T>::nodesCount()
{
	return this->nodes;
}

template<typename T>
bool BST<T>::remove(T data)
{
	BSTNode<T> temp = findNode(this->root, data);
	if (temp) {
		extract(this->root, temp);
		return true;
	}
	return false;
}

template<typename T>
int BST<T>::depth()
{
	return findDepth(this->root);
}

template<typename T>
BSTNode<T>* BST<T>::getRootptr()
{
	return this->root;
}

template<typename T>
void BST<T>::preOrder(BSTNode<T>* root, std::ofstream &output)
{
	if (root) {
		output << root->getData() << '\t';
		preOrder(root->getLeft(), output);
		preOrder(root->getRight(), output);
	}
}

template<typename T>
void BST<T>::postOrder(BSTNode<T>* root, std::ofstream &output)
{
	if (root) {
		postOrder(root->getLeft(), output);
		postOrder(root->getRight(), output);
		output << root->getData() << '\t';
	}
}

template<typename T>
void BST<T>::inOrder(BSTNode<T>* root, std::ofstream &output)
{
	if (root) {
		inOrder(root->getLeft(), output);
		output << root->getData() << '\t';
		inOrder(root->getRight(), output);
	}
}

template<typename T>
void BST<T>::breadthFirst(BSTNode<T>* root, std::ofstream &output)
{
	Queue<BSTNode<T>*> *queue = new Queue<BSTNode<T>*>();

	if (root == nullptr) return;
	queue->enqueue(root);
	while (!queue->queueEmpty())
	{
		BSTNode<T>* temp = queue->dequeue();
		output << temp->getData() << '\t';
		if (temp->left != nullptr)
			queue->enqueue(temp->left);
		if (temp->right != nullptr)
			queue->enqueue(temp->right);
	}
	delete queue;

	//int numnodes = this->nodesCount();
	//BSTNode<T> *temp[numnodes];
	//temp[0] = root;
	//int count = 1;

	//for (int i = 0; i < nodes; i++) {
	//	count--;
	//	output << temp[count]->getData() << '\t';
	//	if (temp->left != nullptr) {
	//		temp[count] = temp->left;
	//		count++;
	//	}
	//	if (temp->right != nullptr) {
	//		temp[count] = temp->right;
	//		count++;
	//	}
	//}


	//BSTNode<T>* temp = root;
	//for (int i = 0; i < nodes; i++) {
	//	output << temp->getData() << '\t';
	//	if (temp->left != nullptr)
	//		temp=temp->left;
	//	if (temp->right != nullptr)
	//		temp=temp->right;
	//}
}

#endif
