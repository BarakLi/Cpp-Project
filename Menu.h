#ifndef  MENU_H
#define MENU_H

#include "Employee.h"
#include "Department.h"

//This class contains the menues for the program. every option has it's own menu controled by enum class member.

enum State { EXIT, ADD_EMPLOYEE_MENU, PRINT_MENU, MAIN_MENU };

class Menu
{
public:
	Menu(Department& dep_);
	~Menu();

	void Run();

private:
	void mainMenu();
	void addEmployeeMenu()throw(char*);
	void printOptionsMenu();

	void modifyEmployee(int id_);
	void modifyProgrammer(Employee* employee_);
	void modifySoftwareArchitect(Employee* employee_);
	void modifyTeamLeader(Employee* employee_);
	void modifyProjectManager(Employee* employee_);
	void modifyAdministrationWorker(Employee* employee_);

	Department& m_dep;
	State m_state;
};
#endif