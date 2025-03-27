#pragma once
#include <iostream>
template <typename type>
class Deque
{
private:
	type** Blocks = nullptr;
	size_t firstBlock = 0;
	size_t firstPos = 0;
	size_t lastBlock = 0;
	size_t lastPos = 0;
	size_t totalBlocksSize = 0;
	size_t DequeSize = 0;
	bool expand(int dirr);
	bool shrink(int dirr);

	template<typename Arg, typename... Rest>
	void push_back_all(Arg&& arg, Rest&&... rest) 
	{
		push_back(std::forward<Arg>(arg));
		push_back_all(std::forward<Rest>(rest)...);
	}
	template<typename Arg>
	void push_back_all(Arg&& arg) 
	{
		push_back(std::forward<Arg>(arg));
	}

public:
	Deque();
	Deque(Deque& copy);
	template<typename ... Args>
	Deque(Args&& ... values) : Deque<type>()
	{
		push_back_all(std::forward<Args>(values)...);
	}
	~Deque();

	Deque& operator=(Deque & copy);

	bool empty();
	type& operator[](int i);
	void push_back(type value);
	void push_front(type value);
	void insert(type value, int pos);
	void remove(int pos);
	void pop_back();
	void pop_front();
	type& front();
	type& back();
	void clear();
	size_t size();
};

template<typename type>
bool Deque<type>::expand(int dirr)
{
	type** newBlocks = new type * [totalBlocksSize + 1];
	if (!newBlocks)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return false;
	}
	if (dirr < 0)
	{
		//Left expand
		for (int i = 1; i < totalBlocksSize + 1; i++)
		{
			newBlocks[i] = Blocks[i - 1];
		}
		newBlocks[0] = new type[8];
		if (!newBlocks[0])
		{
			std::cout << "Memory allocation unsuccessful.\n";
			return false;
		}
		firstBlock++;
		lastBlock++;
	}
	else if (dirr > 0)
	{
		//Right expand
		for (int i = 0; i < totalBlocksSize; i++)
		{
			newBlocks[i] = Blocks[i];
		}
		newBlocks[totalBlocksSize] = new type[8];
		if (!newBlocks[totalBlocksSize])
		{
			std::cout << "Memory allocation unsuccessful.\n";
			return false;
		}
	}
	delete[] Blocks;
	Blocks = newBlocks;
	totalBlocksSize++;
	return true;
}

template<typename type>
bool Deque<type>::shrink(int dirr)
{
	type** newBlocks = new type * [totalBlocksSize - 1];
	if (!newBlocks)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return false;
	}
	if (dirr < 0)
	{
		//Left shrink
		for (int i = 0; i < totalBlocksSize - 1; i++)
		{
			newBlocks[i] = Blocks[i + 1];
		}
		delete[] Blocks[0];
		firstBlock--;
		lastBlock--;
	}
	else if (dirr > 0)
	{
		//Right shrink
		for (int i = 0; i < totalBlocksSize - 1; i++)
		{
			newBlocks[i] = Blocks[i];
		}
		delete[] Blocks[totalBlocksSize - 1];
	}
	delete[] Blocks;
	Blocks = newBlocks;
	totalBlocksSize--;
	return true;
}

template <typename type>
Deque<type>::Deque()
{
	Blocks = new type * [2];
	if (Blocks == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	Blocks[0] = new type[8];
	if (Blocks[0] == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	Blocks[1] = new type[8];
	if (Blocks[1] == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	firstBlock = 1;
	lastBlock = 1;
	firstPos = 0;
	lastPos = 0;
	totalBlocksSize = 2;
	DequeSize = 0;
}

template<typename type>
bool Deque<type>::empty()
{
	if (DequeSize == 0) return true;
	return false;
}

template<typename type>
type& Deque<type>::operator[](int search)
{
	if (DequeSize <= search || search < 0 || empty())
	{
		std::cout << "Invalid position ";
		static type x = type();
		return x;
	}
	else
	{
		if (search <= 7 - firstPos)
		{
			return Blocks[firstBlock][firstPos + search];
		}
		search -= 8 - (int)firstPos ;
		return Blocks[firstBlock + 1 + search / 8][search % 8];
	}

}

template<typename type>
void Deque<type>::push_back(type value)
{
	if (empty())
	{
		Blocks[1][0] = value;
		DequeSize++;
	}
	else
	{
		if (lastPos != 7)
		{
			Blocks[lastBlock][lastPos + 1] = value;
			lastPos++;
			DequeSize++;
		}
		else
		{
			if (totalBlocksSize - 1 == lastBlock)
			{
				if (!expand(1))
				{
					return;
				}
				lastBlock++;
				lastPos = 0;
				Blocks[lastBlock][lastPos] = value;
				DequeSize++;
			}
			else
			{
				lastBlock++;
				lastPos = 0;
				Blocks[lastBlock][lastPos] = value;
				DequeSize++;
			}
		}
	}
}

template<typename type>
void Deque<type>::push_front(type value)
{
	if (empty())
	{
		Blocks[1][0] = value;
		DequeSize++;
	}
	else
	{
		if (firstPos != 0)
		{
			firstPos--;
			Blocks[firstBlock][firstPos] = value;
			DequeSize++;
		}
		else
		{
			if (firstBlock == 0)
			{
				if (!expand(-1))
				{
					return;
				}
				firstBlock--;
				firstPos = 7;
				Blocks[firstBlock][firstPos] = value;
				DequeSize++;
			}
			else
			{
				firstBlock--;
				firstPos = 7;
				Blocks[firstBlock][firstPos] = value;
				DequeSize++;
			}
		}
	}
}

template<typename type>
void Deque<type>::insert(type value, int pos)
{
	if (pos<0 || pos > DequeSize)
	{
		std::cout << "Invalid position for insert\n";
		return;
	}
	if (pos == DequeSize)
	{
		this->push_back(value);
		return;
	}
	if (pos == 0)
	{
		this->push_front(value);
		return;
	}
	this->push_back(this->back());
	for (int it = (int)(DequeSize-2); it > pos; it--)
	{
		this->operator[](it) = this->operator[](it-1);
	}
	this->operator[](pos) = value;
}

template<typename type>
void Deque<type>::remove(int pos)
{
	if (pos<0 || pos >= DequeSize)
	{
		std::cout << "Invalid position for delete\n";
		return;
	}
	for (int it = pos; it < DequeSize-1; it++)
	{
		this->operator[](it) = this->operator[](it + 1);
	}
	pop_back();
}

template<typename type>
void Deque<type>::pop_back()
{
	if (empty())
	{
		std::cout << "Deque is empty.\n";
		return;
	}
	if (firstBlock == lastBlock && firstPos == lastPos)
	{
		firstPos = 0;
		lastPos = 0;
		firstBlock = 1;
		lastBlock = 1;
		DequeSize = 0;
		return;
	}
	if (lastPos != 0)
	{
		lastPos--;
		DequeSize--;
	}
	else
	{
		if (lastBlock == totalBlocksSize - 2)
		{
			if(!shrink(1)) return;
			lastBlock--;
			lastPos = 7;
			DequeSize--;
		}
		else
		{
			lastBlock--;
			lastPos = 7;
			DequeSize--;
		}
	}
}

template<typename type>
void Deque<type>::pop_front()
{
	if (empty())
	{
		std::cout << "Deque is empty.\n";
		return;
	}
	if (firstBlock == lastBlock && firstPos == lastPos)
	{
		firstPos = 0;
		lastPos = 0;
		firstBlock = 1;
		lastBlock = 1;
		DequeSize = 0;
		return;
	}
	if (firstPos != 7)
	{
		firstPos++;
		DequeSize--;
	}
	else
	{
		if (firstBlock == 1)
		{
			if(!shrink(-1)) return;
			firstBlock++;
			firstPos = 0;
			DequeSize--;
		}
		else
		{
			firstBlock++;
			firstPos = 0;
			DequeSize--;
		}
	}
}

template<typename type>
type& Deque<type>::front()
{
	if (empty())
	{
		static type x = type();
		std::cout << "Deque is empty.\n";
		return x;
	}
	else
	{
		return Blocks[firstBlock][firstPos];
	}
}

template<typename type>
type& Deque<type>::back()
{
	if (empty())
	{
		static type x = type();
		std::cout << "Deque is empty.\n";
		return x;
	}
	else
	{
		return Blocks[lastBlock][lastPos];
	}
}

template<typename type>
void Deque<type>::clear()
{
	for (int i = 0; i < totalBlocksSize; i++)
	{
		delete[] Blocks[i];
	}
	delete[] Blocks;
	Blocks = new type * [2];
	if (Blocks == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	Blocks[0] = new type[8];
	if (Blocks[0] == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	Blocks[1] = new type[8];
	if (Blocks[1] == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	firstBlock = 1;
	lastBlock = 1;
	firstPos = 0;
	lastPos = 0;
	totalBlocksSize = 2;
	DequeSize = 0;
}

template<typename type>
size_t Deque<type>::size()
{
	return DequeSize;
}

template<typename type>
Deque<type>::~Deque()
{
	for (int i = 0; i < totalBlocksSize; i++)
	{
		delete[] Blocks[i];
	}
	delete[] Blocks;
}

template<typename type>
Deque<type>::Deque(Deque<type>& copy)
{
	this->Blocks = new type * [copy.totalBlocksSize];
	if (this->Blocks == nullptr)
	{
		std::cout << "Memory allocation unsuccessful.\n";
		return;
	}
	this->totalBlocksSize = copy.totalBlocksSize;
	for (int i = 0; i < copy.totalBlocksSize; i++)
	{
		this->Blocks[i] = new type[8];
		if (Blocks[i] == nullptr)
		{
			std::cout << "Memory allocation unsuccessful.\n";
			for (int j = 0; j < i; j++)
			{
				delete[] this->Blocks[j];
			}
			delete[] this->Blocks;
			this->totalBlocksSize = 0;
			return;
		}
	}
	this->firstBlock = copy.firstBlock;
	this->firstPos = copy.firstPos;
	this->lastBlock = copy.lastBlock;
	this->lastPos = copy.lastPos;
	this->DequeSize = copy.DequeSize;
	for (size_t it = 0; it < DequeSize; it++)
	{
		(*this)[it] = copy[it];
	}
}

template<typename type>
Deque<type>& Deque<type>::operator=(Deque<type>& copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < this->totalBlocksSize; i++)
		{
			delete[] this->Blocks[i];
		}
		delete[] this->Blocks;
		this->Blocks = new type * [copy.totalBlocksSize];
		if (this->Blocks == nullptr)
		{
			std::cout << "Memory allocation unsuccessful.\n";
			return *this;
		}
		this->totalBlocksSize = copy.totalBlocksSize;
		for (int i = 0; i < copy.totalBlocksSize; i++)
		{
			this->Blocks[i] = new type[8];
			if (Blocks[i] == nullptr)
			{
				std::cout << "Memory allocation unsuccessful.\n";
				for (int j = 0; j < i; j++)
				{
					delete[] this->Blocks[j];
				}
				delete[] this->Blocks;
				this->totalBlocksSize = 0;
				return *this;
			}
		}
		this->firstBlock = copy.firstBlock;
		this->firstPos = copy.firstPos;
		this->lastBlock = copy.lastBlock;
		this->lastPos = copy.lastPos;
		this->DequeSize = copy.DequeSize;
		for (int it = 0; it < DequeSize; it++)
		{
			this->operator[](it) = copy.operator[](it);
		}
	}
	return *this;
}