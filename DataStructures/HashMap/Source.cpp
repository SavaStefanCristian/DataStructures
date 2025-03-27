#include "unordered_map.h"
#include <fstream>
void printMenu()
{
	std::cout << "-----------------------------\n";
	std::cout << "| 0 Exit                    |\n";
	std::cout << "| 1 Find [key]              |\n";
	std::cout << "| 2 Insert [key,value]      |\n";
	std::cout << "| 3 Erase [key]             |\n";
	std::cout << "| 4 Operator[] [key,value]  |\n";
	std::cout << "| 5 Print map               |\n";
	std::cout << "-----------------------------\n";
}

bool readTable(unordered_map<int, int>& hashTable, std::string filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		std::cout << "Could not open input file!\n";
		return false;
	}
	int a, b;
	while (file >> a >> b)
	{
		hashTable.insert(std::pair<int, int>(a, b));
	}
	file.close();
	return true;
}

int main()
{
	unordered_map<int, int> hashTable;
	if(!readTable(hashTable, "inputTest.txt")) return 1;
	printMenu();
	int option = -1;
	int key, value;
	while (option != 0)
	{
		std::cout << "$ ";
		std::cin >> option;
		switch (option)
		{
		case 0:
			std::cout << "Shuting down...\n";
			break;
		case 1:
			std::cin >> key;
			if (hashTable.find(key) != hashTable.end()) std::cout << "Element was found and its value is " << hashTable.find(key)->second<<".\n";
			else std::cout << "Element is not inside the hash map.\n";
			break;
		case 2:
			std::cin >> key >> value;
			hashTable.insert(std::pair<int, int>(key, value));
			std::cout << "Insertion succesful.\n";
			break;
		case 3:
			std::cin >> key;
			hashTable.erase(key);
			std::cout << "Element was erased.\n";
			break;
		case 4:
			std::cin >> key >> value;
			hashTable[key] = value;
			break;
		case 5:
			if (hashTable.empty()) std::cout << "Hash map is empty.\n";
			else
			{
				for (auto& element : hashTable)
				{
					std::cout << "Bucket: " << hashTable.bucket(element.first) << " - Key: " << element.first << " - Value: " << element.second << "\n";
				}
			}
			break;
		default:
			break;
		}
	}
	return 0;
}