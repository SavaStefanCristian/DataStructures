#include "Deque.h"
#ifdef _WIN32
#include <Windows.h>
#endif

void printMenu()
{
	
	std::cout << "----------------------------\n";
	std::cout << "| 0  Exit                  |\n";
	std::cout << "| 1  Push_back [value]     |\n";
	std::cout << "| 2  Push_front [value]    |\n";
	std::cout << "| 3  Pop_back              |\n";
	std::cout << "| 4  Pop_front             |\n";
	std::cout << "| 5  Front                 |\n";
	std::cout << "| 6  Back                  |\n";
	std::cout << "| 7  Empty                 |\n";
	std::cout << "| 8  Clear                 |\n";
	std::cout << "| 9  Size                  |\n";
	std::cout << "| 10 Operator[] [pos]      |\n";
	std::cout << "| 11 Insert [value] [pos]  |\n";
	std::cout << "| 12 Delete [pos]          |\n";
	std::cout << "| 13 Print                 |\n";
	std::cout << "----------------------------\n";
}

int main()
{
	Deque<int> deque; //se pot adauga elemente chiar din constructor, ex: Deque<int> deque(1, -1, 2, -2, 3, -3);
	int option = -1;
	int x=0;
	int pos=0;
	printMenu();
	while (option != 0)
	{
		std::cout << "$ ";
		std::cin >> option;
		switch (option)
		{
		case 0:
			std::cout << "Shuting down";
#ifdef _WIN32
			Sleep(700);
			std::cout << ".";
			Sleep(700);
			std::cout << ".";
			Sleep(700);
			std::cout << ".\n";
			Sleep(1150);
#endif
			return 0;
			break;
		case 1:
			std::cin >> x;
			deque.push_back(x);
			break;
		case 2:
			std::cin >> x;
			deque.push_front(x);
			break;
		case 3:
			deque.pop_back();
			break;
		case 4:
			deque.pop_front();
			break;
		case 5:
			std::cout << deque.front() << "\n";
			break;
		case 6:
			std::cout << deque.back() << "\n";
			break;
		case 7:
			if (deque.empty()) std::cout << "Is empty.\n";
			else std::cout << "Is not empty.\n";
			break;
		case 8:
			deque.clear();
			break;
		case 9:
			std::cout << deque.size()<<"\n";
			break;
		case 10:
			std::cin >> pos;
			std::cout << deque[pos] << "\n";
			break;
		case 11:
			std::cin >> x >> pos;
			deque.insert(x, pos);
			break;
		case 12:
			std::cin >> pos;
			deque.remove(pos);
			break;
		case 13:
			for (int i = 0; i < deque.size(); i++)
			{
				std::cout << deque[i] << " ";
			}
			std::cout << "\n";
			break;
		default:
			std::cout << "Invalid option!\n";
		}
	}
	return 0;

}