#pragma once
#include<string>
#include<iostream>
#define black 0
#define red 1

// Inspiration: Ms. Resch's lecture on Red-Black Trees
struct RBNode
{
	std::string gameStr;
	char points;
	bool color = black;
	RBNode * left;
	RBNode * right;
	RBNode * parent;

	RBNode(std::string _gameStr, char _points);
};

RBNode* createInsert(RBNode* root, std::string gameStr, char points);
RBNode * insert(RBNode* root, RBNode* node);
RBNode * BSTinsert(RBNode* root, RBNode* node);
RBNode * RBbalance(RBNode* root, RBNode* node);
RBNode * getUncle(RBNode* node);
RBNode* rotateRight(RBNode*root, RBNode* top);
RBNode* rotateLeft(RBNode* root, RBNode* top);

float rating(RBNode* root, std::string gameStr);
void traverseSum(RBNode* root, std::string& left, std::string& right, float& sum, int& count);
int count(RBNode* root);