#include "Department.h"
#include "Menu.h"

using namespace std;

int main()
{
	string fileName("test.txt");
	Department dep(fileName);
	Menu menu(dep);
	menu.Run();

	system("pause");
}