#include "map.h"
#include <map>
#include <stack>

void printMenu()
{
	std::cout << "---------------------------\n";
	std::cout << "| 0  Exit                 |\n";
	std::cout << "| 1  Find [key]           |\n";
	std::cout << "| 2  Insert [key,value]   |\n";
	std::cout << "| 3  Erase [key]          |\n";
	std::cout << "| 4  Print Keys           |\n";
	std::cout << "| 5  Print Values         |\n";
	std::cout << "| 6  Size                 |\n";
	std::cout << "| 7  Empty                |\n";
	std::cout << "| 8  Clear                |\n";
	std::cout << "| 9  Max Key              |\n";
	std::cout << "| 10 Min Key              |\n";
	std::cout << "| 11 Print w iterator     |\n";
	std::cout << "| -1 Undo                 |\n";
	std::cout << "| -2 Redo                 |\n";
	std::cout << "---------------------------\n";
}

int main()
{
	map<int, int> myMap;
	std::stack<map<int, int>> undo;
	std::stack<map<int, int>> redo;
	undo.push(myMap);
	printMenu();
	int option = -2;
	int x, y;
	map<int, int>::iterator found;
	while (option != 0)
	{
		std::cout << "$ ";
		std::cin >> option;
		switch (option)
		{
		case -2:
			if (redo.size() <= 0)
			{
				std::cout << "There is nothing to redo.\n";
			}
			else
			{
				undo.push(myMap);
				myMap = redo.top();
				redo.pop();
			}
			break;
		case -1:
			if (undo.size()<=1)
			{
				std::cout << "There is nothing to undo.\n";
			}
			else
			{
				redo.push(myMap);
				undo.pop();
				myMap = undo.top();
			}
			break;
		case 0:
			std::cout << "Shuting down...\n";
			return 0;
		case 1:
			std::cin >> x;
			found = myMap.find(x);
			if (found != myMap.end())
			{
				std::cout << found->second << "\n";
			}
			else
			{
				std::cout << "Key was not found.\n";
			}
			undo.push(myMap);
			break;
		case 2:
			std::cin >> x >> y;
			myMap.insert(std::pair<int, int>(x, y));
			undo.push(myMap);
			break;
		case 3:
			std::cin >> x;
			myMap.erase(x);
			undo.push(myMap);
			break;
		case 4:
			myMap.printKeys();
			break;
		case 5:
			myMap.printValues();
			break;
		case 6:
			std::cout << myMap.size() <<"\n";
			break;
		case 7:
			if (myMap.empty()) std::cout << "Empty.\n";
			else std::cout << "Not empty.\n";
			break;
		case 8:
			myMap.clear();
			undo.push(myMap);
			break;
		case 9:
			std::cout << myMap.maxKey() << "\n";
			break;
		case 10:
			std::cout << myMap.minKey() << " \n";
			break;
		case 11:
			for (auto& it : myMap)
			{
				std::cout << it.first << "-" << it.second << " ";
			}
			std::cout << "\n";
			break;
		default:
			std::cout << "Invalid option.\n";
			break;
		}
	}
	return 0;
}