#pragma once
#include <iostream>
#include <vector>
#define RED_NODE -1
#define BLACK_NODE 1
template<typename KeyType, typename ValueType, typename Compare = std::less<KeyType>>
class map
{
private:
	struct m_node
	{
		std::pair<KeyType, ValueType> data = std::pair<KeyType, ValueType>(KeyType(), ValueType());
		m_node* left = nullptr;
		m_node* right = nullptr;
		m_node* parent = nullptr;
		int color = RED_NODE;
	};
	m_node* NIL = nullptr;
	m_node* m_root = nullptr;
	size_t m_totalSize = 0;

	//const std::string redNodeText = "\033[30;41m";
	//const std::string blackNodeText = "\033[1;37m";
	const std::string redNodeText = "\033[37;41m";
	const std::string blackNodeText = "\033[30;47m";
	const std::string resetText = "\033[0m";

	void printKeys(const std::string& prefix, const m_node* node, bool isRight)
	{
		if (node != nullptr  && node != NIL)
		{
			std::cout << prefix;
			std::cout << (isRight ? "|--" : "'--");
			if (node->color == RED_NODE) std::cout << redNodeText;
			if (node->color == BLACK_NODE) std::cout << blackNodeText;
			std::cout << node->data.first << resetText << '\n';
			printKeys(prefix + (isRight ? "|   " : "    "), node->right, true);
			printKeys(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}
	void printValues(const std::string& prefix, const m_node* node, bool isRight)
	{
		if (node != nullptr && node != NIL)
		{
			std::cout << prefix;
			std::cout << (isRight ? "|--" : "'--");
			if (node->color == RED_NODE) std::cout << redNodeText;
			if (node->color == BLACK_NODE) std::cout << blackNodeText;
			std::cout << node->data.second << resetText << '\n';
			printValues(prefix + (isRight ? "|   " : "    "), node->right, true);
			printValues(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}

	void rightRotation(m_node* y)
	{
		m_node* x = y->left;
		y->left = x->right;
		if (x->right != NIL) x->right->parent = y->parent;
		x->parent = y->parent;
		if (y->parent == NIL) m_root = x;
		else
		{
			if (y == y->parent->right) y->parent->right = x;
			else
				y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	}

	
	void leftRotation(m_node* y)
	{
		if (y == NIL) std::cout << "xxxx";
		m_node* x = y->right;
		y->right = x->left;
		if (x->left != NIL) x->left->parent = y->parent;
		x->parent = y->parent;
		if (y->parent == NIL) m_root = x;
		else
		{
			if (y == y->parent->left) y->parent->left = x;
			else
				y->parent->right = x;
		}
		x->left = y;
		y->parent = x;
	}


	void insertionCaseSolver(m_node* child)
	{
		if (child == NIL) return;
		if (child->parent == m_root) 
		{
			m_root->color = BLACK_NODE;
			return;
		}
		if (child->color != RED_NODE || child->parent->color != RED_NODE) return;
		m_node* parent = child->parent;
		bool childIsLeft = false;
		if (child == parent->left) childIsLeft = true;
		m_node* grandParent = parent->parent;
		bool parentIsLeft = false;
		m_node* uncle = NIL;
		if (grandParent->left == parent) 
		{
			parentIsLeft = true;
			uncle = grandParent->right;
		}
		if (grandParent->right == parent) 
		{
			uncle = grandParent->left;
		}
		//Case 1:
		if (uncle->color == RED_NODE)
		{
			if(grandParent!=m_root) grandParent->color = RED_NODE;
			parent->color = BLACK_NODE;
			uncle->color = BLACK_NODE;
			insertionCaseSolver(grandParent);
			return;
		}
		if (uncle->color == BLACK_NODE)
		{
			//Case 2:
			//a
			if (childIsLeft == false && parentIsLeft == true)
			{
				leftRotation(parent);
				insertionCaseSolver(parent);
				return;
			}
			//b
			if (childIsLeft == true && parentIsLeft == false)
			{
				rightRotation(parent);
				insertionCaseSolver(parent);
				return;
			}
			//Case 3:
			//a
			if (childIsLeft == true && parentIsLeft == true)
			{
				grandParent->color = RED_NODE;
				parent->color = BLACK_NODE;
				rightRotation(grandParent);
				return;
			}
			//b
			if (childIsLeft == false && parentIsLeft == false)
			{
				grandParent->color = RED_NODE;
				parent->color = BLACK_NODE;
				leftRotation(grandParent);
				return;
			}
		}

	}

	void deletionTransplant(m_node* node, m_node* replace)
	{
		if (node->parent == NIL) 
			m_root = replace;
		else
		{
			if (node == node->parent->left)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		replace->parent = node->parent;
	}

	void deletionCaseSolver(m_node* node)
	{
		while (node != m_root && node->color == BLACK_NODE)
		{
			if (node == node->parent->left)
			{
				m_node* brother = node->parent->right;
				//Case 1:
				if (brother->color == RED_NODE)
				{
					brother->color = BLACK_NODE;
					node->parent->color = RED_NODE;
					leftRotation(node->parent);
					brother = node->parent->right;
				}
				//Case 2:
					if (brother->left->color == BLACK_NODE && brother->right->color == BLACK_NODE)
					{
						brother->color = RED_NODE;
						node = node->parent;
					}
					//Case 3:
					else
					{
						if (brother->right->color == BLACK_NODE)
						{
							brother->left->color = BLACK_NODE;
							brother->color = RED_NODE;
							rightRotation(brother);
							brother = node->parent->right;
						}
						//Case 4:
						brother->color = node->parent->color;
						node->parent->color = BLACK_NODE;
						brother->right->color = BLACK_NODE;
						leftRotation(node->parent);
						node = m_root;

					}
			}
			else if (node == node->parent->right)
			{
				m_node* brother = node->parent->left;
				//Case 1:
				if (brother->color == RED_NODE)
				{
					brother->color = BLACK_NODE;
					node->parent->color = RED_NODE;
					rightRotation(node->parent);
					brother = node->parent->left;
				}
				//Case 2:
					if (brother->right->color == BLACK_NODE && brother->left->color == BLACK_NODE)
					{
					brother->color = RED_NODE;
					node = node->parent;
					}
					//Case 3:
					else
					{
						if (brother->left->color == BLACK_NODE)
						{
							brother->right->color = BLACK_NODE;
							brother->color = RED_NODE;
							leftRotation(brother);
							brother = node->parent->left;
						}
						//Case 4:
						brother->color = node->parent->color;
						node->parent->color = BLACK_NODE;
						brother->left->color = BLACK_NODE;
						rightRotation(node->parent);
						node = m_root;
					}
				
			}
		}
		//Case 0:
		node->color = BLACK_NODE; 
	}

	m_node* successor(m_node* node) {
		if (node->right != NIL) {
			node = node->right;
			while (node->left != NIL) {
				node = node->left;
			}
			return node;
		}
		else {
			m_node* parent = node->parent;
			while (parent != NIL && node == parent->right) {
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
	}

	void copyConstructorHelper(const map<KeyType,ValueType,Compare>& otherMap, m_node* currentNode1, m_node* currentNode2)
	{
		if (currentNode2->left == otherMap.NIL)
		{
			currentNode1->left = this->NIL;
		}
		else
		{
			currentNode1->left = new m_node;
			currentNode1->left->data = currentNode2->left->data;
			currentNode1->left->color = currentNode2->left->color;
			currentNode1->left->parent = currentNode1;
			copyConstructorHelper(otherMap, currentNode1->left, currentNode2->left);
		}
		if (currentNode2->right == otherMap.NIL)
		{
			currentNode1->right = this->NIL;
		}
		else
		{
			currentNode1->right = new m_node;
			currentNode1->right->data = currentNode2->right->data;
			currentNode1->right->color = currentNode2->right->color;
			currentNode1->right->parent = currentNode1;
			copyConstructorHelper(otherMap, currentNode1->right, currentNode2->right);
		}
	}

	void clearHelper(m_node* node)
	{
		if (node->left != NIL) clearHelper(node->left);
		if (node->right != NIL) clearHelper(node->right);
		delete node;
	}


public:

	void printKeys()
	{
		printKeys("", m_root, false);
	}
	void printValues()
	{
		printValues("", m_root, false);
	}

	class iterator {
	private:
		m_node* currentNode = nullptr;
		map<KeyType, ValueType, Compare>* mapInstance = nullptr;

	public:
		iterator() {
			currentNode = nullptr;
			mapInstance = nullptr;
		}
		iterator(m_node* node, map<KeyType,ValueType,Compare>* mapInstance) : currentNode(node), mapInstance(mapInstance) {}
		iterator(const iterator& copy)
		{
			this->currentNode = copy.currentNode;
			this->mapInstance = copy.mapInstance;
		}
		iterator& operator=(iterator& copy)
		{
			this->currentNode = copy.currentNode;
			this->mapInstance = copy.mapInstance;
			return *this;
		}
		iterator& operator=(iterator copy)
		{
			this->currentNode = copy.currentNode;
			this->mapInstance = copy.mapInstance;
			return *this;
		}
		iterator& operator++()
		{
			if (currentNode == nullptr) {
				return *this;
			}

			if (currentNode->right != mapInstance->NIL) {
				currentNode = currentNode->right;
				while (currentNode->left != mapInstance->NIL) {
					currentNode = currentNode->left;
				}
			}
			else {
				m_node* parent = currentNode->parent;
				while (parent != nullptr && currentNode == parent->right) {
					currentNode = parent;
					parent = parent->parent;
				}
				currentNode = parent;
			}
			return *this;
		}

		iterator operator++(int)
		{
			iterator toReturn = *this;
			++(*this);
			return toReturn;
		}

		std::pair<KeyType, ValueType>& operator*() {
			return currentNode->data;
		}
		std::pair<KeyType, ValueType>* operator->() {
			return &(currentNode->data);
		}

		bool operator!=(const iterator& otherIterator)
		{
			return (this->currentNode != otherIterator.currentNode || this->mapInstance != otherIterator.mapInstance);
		}
		bool operator==(const iterator& otherIterator)
		{
			return (this->currentNode == otherIterator.currentNode && this->mapInstance == otherIterator.mapInstance);
		}

	};
private:
	iterator beginIT;
	iterator endIT;

public:


	iterator& begin()
	{
		m_node* curr = m_root;
		while (curr->left != NIL)
		{
			curr = curr->left;
		}
		beginIT = iterator(curr, this);
		return beginIT;
	}

	iterator& end()
	{
		endIT = iterator(NIL, this);
		return endIT;
	}
	iterator find(const KeyType& key)
	{
		if (empty())
		{
			return end();
		}
		m_node* curr = m_root;
		while (curr != NIL && curr->data.first!=key)
		{
			if (Compare{}(key, curr->data.first))
				curr = curr->left;
			else
				curr = curr->right;
		}
		if (curr == NIL) return end();
		else
			return iterator(curr, this);
	}

	iterator insert(const std::pair<KeyType,ValueType>& val)
	{
		if (empty())
		{
			m_root = new m_node;
			if (!m_root)
			{
				std::cout << "Memory allocation failed.\n";
				return iterator();
			}
			m_root->color = BLACK_NODE;
			m_root->data = val;
			m_root->left = NIL;
			m_root->right = NIL;
			m_root->parent = NIL;
			m_totalSize = 1;
			
			return iterator(m_root,this);
		}
		else
		{
			bool yetToFind = true;
			m_node* curr = m_root;
			if (curr->data.first == val.first) return iterator(curr, this);
			bool leftToCurr = false;
			while (yetToFind)
			{

				if (curr->left->data.first == val.first) return iterator(curr->left, this);
				if (curr->right->data.first == val.first) return iterator(curr->right, this);
				if (Compare{}(val.first, curr->data.first))
				{
					if (curr->left == NIL)
					{
						leftToCurr = true;
						yetToFind = false;
					}
					else
					{
						curr = curr->left;
					}
				}
				else
				{
					if (curr->right == NIL)
					{
						leftToCurr = false;
						yetToFind = false;
					}
					else
					{
						curr = curr->right;
					}
				}
			}
			m_node* newNode = new m_node;
			if (!newNode) 
			{
				std::cout << "Memory allocation failed.\n";
				return iterator();
			}
			newNode->data = val;
			newNode->left = NIL;
			newNode->right = NIL;
			newNode->parent = curr;
			if (leftToCurr)
				curr->left = newNode;
			else
				curr->right = newNode;
			if (curr->color == RED_NODE) insertionCaseSolver(newNode);
			m_totalSize++;
		return iterator(newNode, this);
		}
	}

	ValueType& operator[](const KeyType& key)
	{
		iterator findIt = find(key);
		if (findIt != end()) return findIt->second;
		return insert(std::pair<KeyType, ValueType>(key, ValueType()))->second;
	}

	void erase(KeyType deleteKey)
	{
		if (empty())
		{
			return;
		}
		m_node* toDelete = m_root;
		while (toDelete != NIL && toDelete->data.first != deleteKey)
		{
			if (Compare{}(deleteKey, toDelete->data.first))
				toDelete = toDelete->left;
			else
				toDelete = toDelete->right;
		}
		if (toDelete == NIL) return;
		m_totalSize--;
		int color = toDelete->color;
		m_node* replace;
		if (toDelete->left == NIL)
		{
			replace = toDelete->right;
			deletionTransplant(toDelete, replace);
		}
		else
		{
			if (toDelete->right==NIL)
			{
				replace = toDelete->left;
				deletionTransplant(toDelete, replace);
			}
			else
			{
				m_node* succ = successor(toDelete);
				color = succ->color;
				replace = succ->right;
				if (succ->parent == toDelete) replace->parent = succ;
				else
				{
					deletionTransplant(succ, replace);
					succ->right = toDelete->right;
					toDelete->right->parent = succ;
				}
				deletionTransplant(toDelete, succ);
				succ->left = toDelete->left;
				toDelete->left->parent = succ;
				succ->color = toDelete->color;
			}
		}
		if (color == BLACK_NODE) deletionCaseSolver(replace);
		delete toDelete;
	}

	KeyType maxKey()
	{
		if (empty()) return ValueType();
		m_node* curr = m_root;
		while (curr->right != NIL) curr = curr->right;
		return curr->data.first;
	}

	KeyType minKey()
	{
		if (empty()) return ValueType();
		m_node* curr = m_root;
		while (curr->left != NIL) curr = curr->left;
		return curr->data.first;
	}


	bool empty()
	{
		if (this->m_root == this->NIL) return true;
		return this->m_root == nullptr;
	}

	size_t size()
	{
		return m_totalSize;
	}

	void clear()
	{
		if (!empty()) clearHelper(m_root);
		m_totalSize = 0;
		m_root = NIL;
	}

	map<KeyType, ValueType, Compare>& operator=(const map<KeyType, ValueType, Compare>& otherMap)
	{
		clear();
		if (otherMap.m_root != otherMap.NIL && otherMap.m_root != nullptr)
		{
			this->insert(otherMap.m_root->data);
		this->m_totalSize = otherMap.m_totalSize;
		copyConstructorHelper(otherMap, this->m_root, otherMap.m_root);
		}
		return *this;
	}

	map()
	{
		m_totalSize = 0;
		NIL = new m_node;
		if (!NIL) 
		{
			std::cout << "Couldn't initialize NIL.\n";
			return;
		}
		NIL->color = BLACK_NODE;
	}
	map(const map<KeyType,ValueType,Compare>& otherMap)
	{
		m_totalSize = 0;
		NIL = new m_node;
		if (!NIL)
		{
			std::cout << "Couldn't initialize NIL.\n";
			return;
		}
		NIL->color = BLACK_NODE;
		if (otherMap.m_root!=otherMap.NIL&&otherMap.m_root!=nullptr)
		{
			this->insert(otherMap.m_root->data);
		this->m_totalSize = otherMap.m_totalSize;
		copyConstructorHelper(otherMap, this->m_root, otherMap.m_root);
		}
	}

	map(const std::vector<std::pair<KeyType, ValueType>>& vect)
	{
		m_totalSize = 0;
		NIL = new m_node;
		if (!NIL)
		{
			std::cout << "Couldn't initialize NIL.\n";
			return;
		}
		NIL->color = BLACK_NODE;
		for (const std::pair<KeyType, ValueType>& val : vect)
		{
			insert(val);
		}
	}

	~map()
	{
		clear();
		delete NIL;
	}

};

#undef NODE_RED
#undef NODE_BLACK

