
#pragma once
#include <memory>
#include <cassert>
#include<iostream>
using namespace std;
template <class T>
class treeNode
{
public:
	T _val;
	int _bf;
	std::shared_ptr<treeNode<T>> _prev;
	std::shared_ptr<treeNode<T>> _left;
	std::shared_ptr<treeNode<T>> _right;
	treeNode(T val)
		: _val(val), _bf(0), _prev(nullptr), _left(nullptr), _right(nullptr) {}
};

template <class T>
class AVLTree
{
	using node_t = std::shared_ptr<treeNode<T>>;

private:
	void rotateL(node_t parent)
	{
		node_t rotR = parent->_right;
		node_t rotRL = rotR->_left;
		node_t pparent = parent->_prev;

		parent->_right = rotRL;
		rotR->_left = parent;

		rotR->_prev = pparent;
		if (pparent)
		{
			if (pparent->_left == parent)
				pparent->_left = rotR;
			else
				pparent->_right = rotR;
		}
		else
		{
			_root = rotR;
		}
		if (rotRL)
			rotRL->_prev = parent;
		parent->_prev = rotR;
	};
	void rotateR(node_t parent)
	{
		node_t rotL = parent->_left;
		node_t rotLR = rotL->_right;
		node_t pparent = parent->_prev;

		parent->_left = rotLR;
		rotL->_right = parent;

		rotL->_prev = pparent;
		if (pparent)
		{
			if (pparent->_left == parent)
				pparent->_left = rotL;
			else
				pparent->_right = rotL;
		}
		else
		{
			_root = rotL;
		}
		parent->_prev = rotL;
		if (rotLR)
			rotLR->_prev = parent;
	}
	void rotateLR(node_t parent)
	{
		rotateL(parent->_left);
		rotateR(parent);
	}
	void rotateRL(node_t parent)
	{
		rotateR(parent->_right);
		rotateL(parent);
	}

public:
	AVLTree()
		: _root(nullptr) {}
	void insert(T data)
	{
		node_t newNode = std::make_shared<treeNode<T>>(data);
		if (_root == nullptr)
		{
			_root = newNode;
			return;
		}
		node_t cur = _root;
		node_t parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (data <= cur->_val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		if (data <= parent->_val)
			parent->_left = newNode;
		else
			parent->_right = newNode;
		newNode->_prev = parent;
		cur = newNode;
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
				return;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_prev;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					parent->_bf = cur->_bf = 0;
					rotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					parent->_bf = cur->_bf = 0;
					rotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					if (cur->_left->_bf == -1)
					{
						cur->_bf = 1;
						parent->_bf = 0;
					}
					else if (cur->_left->_bf == 1)
					{
						parent->_bf = -1;
						cur->_bf = 0;
					}
					else
					{
						parent->_bf = cur->_bf = 0;
					}
					cur->_left->_bf = 0;
					rotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					if (cur->_right->_bf == -1)
					{
						parent->_bf = 1;
						cur->_bf = 0;
					}
					else if (cur->_right->_bf == 1)
					{
						cur->_bf = -1;
						parent->_bf = 0;
					}
					else
					{
						cur->_bf = parent->_bf = 0;
					}
					cur->_right->_bf = 0;
					rotateLR(parent);
				}
				else
				{
					std::cout << cur->_bf << " " << parent->_bf << std::endl;
					assert(0);
				}
				return;
			}
			else
			{
				// std::cout<<cur->_bf<<" "<<parent->_bf<<std::endl;
				assert(0);
			}
		}
	}
void _InOrder(node_t root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_val << " ";
		_InOrder(root->_right);
	}

	int _Height(node_t root)
	{
		if (root == nullptr)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	int _Size(node_t root)
	{
		if (root == nullptr)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	bool _IsBalanceTree(node_t root)
	{
		// 空树也是AVL树
		if (nullptr == root)
			return true;
		// 计算pRoot结点的平衡因子：即pRoot左右子树的高度差
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		int diff = rightHeight - leftHeight;

		// 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
		// pRoot平衡因子的绝对值超过1，则一定不是AVL树
		if (abs(diff) >= 2)
		{
			cout << root->_val << "高度差异常" << endl;
			return false;
		}

		if (root->_bf != diff)
		{
			cout << root->_val << "平衡因子异常" << endl;
			return false;
		}

		// pRoot的左和右如果都是AVL树，则该树一定是AVL树
		return _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
	}
	node_t get_root(){return _root;}
private:
	node_t _root;
};