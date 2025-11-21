#pragma once
#include <memory>
#include <iostream>
enum Color
{
    RED,
    BLACK
};
template <class T>
class rbNode
{
public:
    T _val;
    Color _color;
    std::shared_ptr<rbNode<T>> _prev;
    std::shared_ptr<rbNode<T>> _left;
    std::shared_ptr<rbNode<T>> _right;
    rbNode(T val)
        : _val(val), _color(RED), _prev(nullptr), _left(nullptr), _right(nullptr)
    {
    }
};
template <class T>
class rbTree
{
    using node_t = std::shared_ptr<rbNode<T>>;

private:
    void rotateL(node_t parent)
    {
        node_t rotR = parent->_right;
        node_t rotRL = rotR->_left;
        node_t pparent = parent->_prev;

        rotR->_left = parent;
        parent->_right = rotRL;
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

        rotR->_prev = pparent;
        parent->_prev = rotR;
        if (rotRL)
            rotRL->_prev = parent;
    }
    void rotateR(node_t parent)
    {
        node_t rotL = parent->_left;
        node_t rotLR = rotL->_right;
        node_t pparent = parent->_prev;

        rotL->_right = parent;
        parent->_left = rotLR;
        if(pparent)
        {
            if(pparent->_left == parent)
                pparent->_left = rotL;
            else
                pparent->_right = rotL;
        }
        else
        {
            _root = rotL;
        }
        rotL->_prev = pparent;
        parent->_prev = rotL;
        if(rotLR)
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
    rbTree()
        : _root(nullptr)
    {
    }
    void insert(T data)
    {
        node_t newNode(std::make_shared<rbNode<T>>(data));
        if (_root == nullptr)
        {
            _root = newNode;
            _root->_color = BLACK;
            return;
        }
        node_t parent = nullptr;
        node_t cur = _root;
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
        //
        cur = newNode;
        while (parent && parent->_color == RED)
        {
            node_t grandfather = parent->_prev;
            if (grandfather->_left == parent)
            {
                node_t uncle = grandfather->_right;
                if (uncle && uncle->_color == RED)
                {
                    parent->_color = BLACK;
                    uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = grandfather->_prev;
                }
                else
                {
                    if (cur == parent->_left)
                    {
                        rotateR(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                        cur->_color = RED;
                    }
                    else
                    {
                        rotateLR(grandfather);
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                        parent->_color = RED;
                    }
                    break;
                }
            }
            else
            {
                node_t uncle = grandfather->_left;
                if (uncle && uncle->_color == RED)
                {
                    parent->_color = BLACK;
                    uncle->_color = BLACK;
                    grandfather->_color = RED;
                    cur = grandfather;
                    parent = grandfather->_prev;
                }
                else
                {
                    if (cur == parent->_right)
                    {
                        rotateL(grandfather);
                        parent->_color = BLACK;
                        grandfather->_color = RED;
                        cur->_color = RED;
                    }
                    else
                    {
                        rotateRL(grandfather);
                        cur->_color = BLACK;
                        grandfather->_color = RED;
                        parent->_color = RED;
                    }
                    break;
                }
            }
        }
        _root->_color = BLACK;
    }
    bool IsBalanceTree()
	{
		if (_root == nullptr) return true;
		if (_root->_color == RED) return false;
		int count = 0;
		node_t cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK) count++;
			cur = cur->_left;
		}
		return Check(_root, 0, count);
	}
	bool Check(node_t root,int path,const int refNum)
	{
		if (root == nullptr) return path == refNum;
		if (root->_color == RED && root->_prev->_color == RED) return false;
		if (root->_color == BLACK) path++;
		return Check(root->_left, path, refNum) && Check(root->_right, path, refNum);
	}
    void Print(node_t root)
    {
        if(!root) return;
        Print(root->_left);
        std::cout<<root->_val<<" ";
        Print(root->_right);
    }
    node_t get_root(){return _root;}
private:
    node_t _root;
};