#ifndef BSTNode_h
#define BSTNode_h

#include "Node.h"

template <typename T>
class BSTNode : public Node<T>
{
private:
	int key;

public:
	BSTNode<T> *left;
	BSTNode<T> *right;

	BSTNode<T>(T);
	BSTNode<T>(T, BSTNode*, BSTNode*);
	void setKey(int);
	void setLeft(BSTNode*);
	void setRight(BSTNode*);

	BSTNode<T>* getLeft();
	BSTNode<T>* getRight();
	int getKey();

	bool isLeaf();
};

template <typename T>
BSTNode<T>::BSTNode(T data) : Node<T>(data)
{
	this->left = nullptr;
	this->right = nullptr;
}

template<typename T>
BSTNode<T>::BSTNode(T data, BSTNode* left, BSTNode* right) : Node<T>(data)
{
	this->left = left;
	this->right = right;
}

template<typename T>
void BSTNode<T>::setKey(int key)
{
	this->key = key;
}

template <typename T>
void BSTNode<T>::setLeft(BSTNode<T> *left) {
	this->left = left;
}

template <typename T>
void BSTNode<T>::setRight(BSTNode<T> *right) {
	this->right = right;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getLeft() {
	return this->left;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getRight() {
	return this->right;
}

template<typename T>
int BSTNode<T>::getKey()
{
	return this->key;
}

template <typename T>
bool BSTNode<T>::isLeaf() {
//	if (this->left == this->right) // will this ever fail?
	if (this->left == nullptr && this->right == nullptr)
		return true;
	return false;
}

#endif
