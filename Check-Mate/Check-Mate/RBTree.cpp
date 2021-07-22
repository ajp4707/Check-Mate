#include "RBTree.h"

RBNode::RBNode(std::string _gameStr, char _points) {
	gameStr = _gameStr;
	points = _points;
	left = right = parent = nullptr;
	color = red;
}

RBNode* createInsert(RBNode* root, std::string gameStr, char points) {
	RBNode* newNode = new RBNode(gameStr, points);
	return insert(root, newNode);
}

RBNode* insert(RBNode* root, RBNode* node) {
	root = BSTinsert(root, node);
	root = RBbalance(root, node);
	return root;
}

RBNode* BSTinsert(RBNode* root, RBNode* node) {
	if (root == nullptr) {
		return node;
	}

	if (node->gameStr < root->gameStr) {
		root->left = BSTinsert(root->left, node);
		root->left->parent = root;
	}
	else {
		root->right = BSTinsert(root->right, node);
		root->right->parent = root;
	}
	return root;
}

RBNode* getUncle(RBNode* node) {
	RBNode* parent = node->parent;
	RBNode* grandparent = parent->parent;
	if (grandparent == nullptr) return nullptr;
	if (parent == grandparent->left)
		return grandparent->right;
	return grandparent->left;
}

RBNode* RBbalance(RBNode* root, RBNode* node) {
	if (node->parent == nullptr) {
		node->color = black;
		return root;
	}
	if (node->parent->color == black)
		return root;
	RBNode* parent = node->parent;
	RBNode* grandparent = parent->parent;		// Guaranteed to exist because parent is guaranteed red.
	RBNode* uncle = getUncle(node);
	if (uncle != nullptr && uncle->color == red) {
		parent->color = uncle->color = black;
		grandparent->color = red;
		return RBbalance(root, grandparent);
	}
	if (node == parent->right && parent == grandparent->left) {
		root = rotateLeft(root, parent);
		node = parent;
		parent = node->parent;
	}
	else if (node == parent->left && parent == grandparent->right) {
		root = rotateRight(root, parent);
		node = parent;
		parent = node->parent;
	}
	parent->color = black;
	grandparent->color = red;
	if (node == parent->left)
		root = rotateRight(root, grandparent);
	else
		root = rotateLeft(root, grandparent);
	return root;
}


// https://www.programiz.com/dsa/red-black-tree
// https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/

RBNode* rotateRight(RBNode*root, RBNode* top) {
	RBNode* child = top->left;
	top->left = child->right;
	if (top->left != NULL)
		top->left->parent = top;
	child->parent = top->parent;
	if (top->parent == NULL)
		root = child;
	else if (top == top->parent->left)
		top->parent->left = child;
	else
		top->parent->right = child;
	child->right = top;
	top->parent = child;
	return root;
}

RBNode* rotateLeft(RBNode* root, RBNode* top) { //top = x
	RBNode* child = top->right;
	top->right = child->left;
	if (top->right != NULL)
		top->right->parent = top;
	child->parent = top->parent;
	if (top->parent == NULL)
		root = child;
	else if (top == top->parent->left)
		top->parent->left = child;
	else
		top->parent->right = child;
	child->left = top;
	top->parent = child;
	return root;
}


float rating(RBNode* root, std::string gameStr) {
	float sum = 0;
	int count = 0;
	std::string left = gameStr;
	std::string right = gameStr.substr(0, gameStr.size() - 1) + "!";
	traverseSum(root, left, right, sum, count);
	std::cout << "RB sum: " << sum << ". count: " << count << std::endl;
	if (count)
		return sum / count;
	else return 0;
}

void traverseSum(RBNode* root, std::string& left, std::string& right, float& sum, int& count) {
	if (!root) return;
	if (root->gameStr < left)
		traverseSum(root->right, left, right, sum, count);
	else if (root->gameStr > right)
		traverseSum(root->left, left, right, sum, count);
	else {
		sum += root->points;
		count++;
		//std::cout << root->gameStr.substr(0, 30) << std::endl;
		traverseSum(root->right, left, right, sum, count);
		traverseSum(root->left, left, right, sum, count);
	}
}

int count(RBNode* root) {
	if (root == nullptr) return 0;
	return 1 + count(root->right) + count(root->left);
}