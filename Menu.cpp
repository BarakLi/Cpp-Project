#include "Menu.h"
#include <fstream>
#include "Programmer.h"

Menu::Menu(Department& dep_) : m_state(MAIN_MENU), m_dep(dep_)
{}

void Menu::Run()
{
	cout << "Welcome to our Employee management app" << endl;

	
		while (m_state != EXIT)
		{
			try
			{
				switch (m_state)
				{
				case MAIN_MENU:
					mainMenu();
					break;

				case ADD_EMPLOYEE_MENU:
					addEmployeeMenu();
					break;

				case PRINT_MENU:
					printOptionsMenu();
					break;

				case EXIT:
					m_state = EXIT;
					cout << "Thank you and goodbye" << endl;
					break;

				default:
					cout << "Wrong choice. Try again." << endl;
				}
			}
			catch (const char* error)
			{
				cout << error << endl << "Program will go back to main menu" << endl;
				m_state = MAIN_MENU;
			}
		}
}

void Menu::mainMenu()
{
	
	int choice;
	long id;
	string fileName;
	stringstream stream;
	int pos;

	cout << "Please select one of the following options (insert number between 1-8):" << endl
		 << "1) Load info from existing file" << endl
		 << "2) Add employee menu" << endl
		 << "3) Remove employee" << endl
		 << "4) Promote programmer" << endl
		 << "5) Print options menu" << endl
		 << "6) Save info to file" << endl
		 << "7) Modify employee" << endl
		 << "8) Quit program" << endl << endl
		 << "Your choice?" << endl;

	
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Please enter file name to read from" << endl;
			cin >> fileName;
			m_dep.readInputFile(fileName);
			break;

		case 2:
			m_state = ADD_EMPLOYEE_MENU;
			break;

		case 3:
			cout << "Enter the id of the employee you wish to remove:" << endl;
			cin >> id;
			m_dep.removeEmployee(id);
			break;

		case 4:
			cout << "Enter the id of the programmer you wish to promote:" << endl;
			cin >> id;
			cout << "Enter the 1 to promote to Software Architect, or 2 to promote to team leader" << endl;
			cin >> pos;
			m_dep.getEmployee(id)->promote((Position)pos, m_dep);

			break;

		case 5:
			m_state = PRINT_MENU;
			break;

		case 6:
			cout << " Enter file name to save the info." << endl;
			cin >> fileName;
			m_dep.storeFinalReport(fileName, m_dep.printFinalReport(stream));
			cout << "Your info was saved as a file" << endl;
			break;

		case 7:
			cout << "Enter the id of the employee you wish to modify:" << endl;
			cin >> id;
			modifyEmployee(id);
			break;

		case 8:
			cout << "Thank you. Exiting the program." << endl;
			m_state = EXIT;
			break;
		}
}

void Menu::modifyEmployee(int id_)
{
	Employee* employee = m_dep.getEmployee(id_);
	if (!employee)
	{
		return;
	}

	if (dynamic_cast<SoftwareArchitect*>(employee))
		modifySoftwareArchitect(employee);
	else if (dynamic_cast<TeamLeader*>(employee))
		modifyTeamLeader(employee);
	else if (dynamic_cast<Programmer*>(employee))
		modifyProgrammer(employee);
	else if (dynamic_cast<AdministrationWorker*>(employee))
		modifyAdministrationWorker(employee);
	else if (dynamic_cast<ProjectManager*>(employee))
		modifyProjectManager(employee);
}

void Menu::modifyProgrammer(Employee* employee_)
{
	int choice;
	long input;
	
	cout << "Please select the attribute you wish to modify" << endl

		 << "1) Base salary" << endl
		 << "2) Seniority" << endl
		 << "3) Worker assesment" << endl
		 << "4) Number of Programmer of the month awards" << endl
		 << "5) Percentage of Full time hours" << endl;

	
	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "Please enter new base salary." << endl;
		cin >> input;
		employee_->setBaseSalary(input);
		break;
	case 2:
		cout << "Please enter new seniority." << endl;
		cin >> input;
		employee_->setSeniority(input);
		break;
	case 3:
		cout << "Please enter new worker assesment." << endl;
		cin >> input;
		employee_->setWorkerAssessment(input);
		break;
	case 4:
		cout << "Please enter number of worker of the month awards." << endl;
		cin >> input;
		((Programmer *)employee_)->setNumOfAwards(input);
		break;
	case 5:
		cout << "Please enter percentage of full time hours." << endl;
		cin >> input;
		((Programmer *)employee_)->setPercentageOfFullTimeHours(input);
		break;
	default:
		cout << "invalid input" << endl;
	}
}


void Menu::modifySoftwareArchitect(Employee* employee_)
{
	int choice;
	int input;
	long id;

	cout << "Please select the attribute you wish to modify" << endl

		<< "1) Base salary" << endl
		<< "2) Seniority" << endl
		<< "3) Worker assesment" << endl
		<< "4) Add programmer trainee" << endl
		<< "5) Add PHD" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "Please enter new base salary." << endl;
		cin >> input;
		employee_->setBaseSalary(input);
		break;

	case 2:
		cout << "Please enter new seniority." << endl;
		cin >> input;
		employee_->setSeniority(input);
		break;

	case 3:
		cout << "Please enter new worker assesment." << endl;
		cin >> input;
		employee_->setWorkerAssessment(input);
		break;

	case 4:
		cout << "Please enter the ID of the trainee" << endl;
		cin >> id;
		if (dynamic_cast<Programmer *>(m_dep.getEmployee(id)))
		{
			((SoftwareArchitect *)employee_)->setTrainee((Programmer *)m_dep.getEmployee(id));
		}
		else
		{
			cout << "Invalid employee to train" << endl;
		}
		break;

	case 5:
		((SoftwareArchitect *)employee_)->setHasPHD(true);
		cout << "PHD added" << endl;
		break;

	default:
		cout << "invalid input" << endl;
	}
}

void Menu::modifyTeamLeader(Employee* employee_)
{
	int choice;
	int input;
	long id;

	cout << "Please select the attribute you wish to modify" << endl

		<< "1) Base salary" << endl
		<< "2) Seniority" << endl
		<< "3) Worker assesment" << endl
		<< "4) Add team member" << endl
		<< "5) Remove team member" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "Please enter new base salary." << endl;
		cin >> input;
		employee_->setBaseSalary(input);
		break;

	case 2:
		cout << "Please enter new seniority." << endl;
		cin >> input;
		employee_->setSeniority(input);
		break;

	case 3:
		cout << "Please enter new worker assesment." << endl;
		cin >> input;
		employee_->setWorkerAssessment(input);
		break;

	case 4:
		cout << "Please enter new team member ID." << endl;
		cin >> id;
		if (dynamic_cast<Programmer *>(m_dep.getEmployee(id)))
		{
			((TeamLeader *)employee_)->operator+=((Programmer *)m_dep.getEmployee(id));
		}
		else
		{
			cout << "invalid employee type" << endl;
		}
		break;

	case 5:
		cout << "Please enter id of a team member to remove." << endl;
		cin >> id;
		if (dynamic_cast<Programmer *>(m_dep.getEmployee(id)))
		{
			((TeamLeader *)employee_)->operator-=((Programmer *)m_dep.getEmployee(id));
		}
		else
		{
			cout << "invalid employee type" << endl;
		}
		break;

	default:
		cout << "invalid input" << endl;
	}
}
void Menu::modifyProjectManager(Employee* employee_)
{
	int choice;
	int input;
	long id;

	cout << "Please select the attribute you wish to modify" << endl

		<< "1) Base salary" << endl
		<< "2) Seniority" << endl
		<< "3) Change project cost" << endl
		<< "4) Add team member" << endl
		<< "5) Remove team member" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "Please enter new base salary." << endl;
		cin >> input;
		employee_->setBaseSalary(input);
		break;

	case 2:
		cout << "Please enter new seniority." << endl;
		cin >> input;
		employee_->setSeniority(input);
		break;

	case 3:
		cout << "Please enter new project cost." << endl;
		cin >> input;
		((ProjectManager*)employee_)->setProjectCost(input);
		break;

	case 4:
		cout << "Please enter new team member ID." << endl;
		cin >> id;
		
		((ProjectManager *)employee_)->operator+=(m_dep.getEmployee(id));
		break;

	case 5:
		cout << "Please enter id of a team member to remove." << endl;
		cin >> id;
		
		((ProjectManager *)employee_)->operator-=(id);
		
		break;

	default:
		cout << "invalid input" << endl;
	}
}
void Menu::modifyAdministrationWorker(Employee* employee_)
{
	int choice;
	int input;

	cout << "Please select the attribute you wish to modify" << endl

		<< "1) Base salary" << endl
		<< "2) Seniority" << endl
		<< "3) Change worker Assesment" << endl
		<< "4) Change student status" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "Please enter new base salary." << endl;
		cin >> input;
		employee_->setBaseSalary(input);
		break;

	case 2:
		cout << "Please enter new seniority." << endl;
		cin >> input;
		employee_->setSeniority(input);
		break;

	case 3:
		cout << "Please enter new worker assesment." << endl;
		cin >> input;
		employee_->setWorkerAssessment(input);
		break;

	case 4:
		cout << "Please enter 1 if student or 0 if not" << endl;
		cin >> input;
		((AdministrationWorker *)employee_)->setIsStudent(input);
		break;

	default:
		cout << "invalid input" << endl;
	}
}


void Menu::addEmployeeMenu() throw(char*)
{
	int input;
	long id = 0;
	string fullName;
	int baseSalary = 0, seniority = 0, workerAssessment = 0, isStudent = 0, projectCost = 0,
		numOfAwards = 0, percentageOfFullTimeHours = 100, hasPHD = 0;

	cout << " What is the employee role? " << endl
		<< "1. Administration worker" << endl
		<< "2. Programmer" << endl
		<< "3. Software architect" << endl
		<< "4. Team leader" << endl
		<< "5. Project manager" << endl
		<< "6. Back to main menu" << endl << endl
		<< "Choose an option between 1-6." << endl;

	cin >> input;

	switch (input)
	{
	case 1:
		cout << "Enter administration worker data: id, fullname(not separated with space), base salary, seniority," << endl
			<< "worker assessment, Are they a student? (insert 0 or 1 (0-no, 1 yes)). Separate all with spaces." << endl;

		cin >> id >> fullName >> baseSalary >> seniority >> workerAssessment >> isStudent;
		m_dep.addAdministrationWorker(id, fullName, baseSalary, seniority, workerAssessment, isStudent);
		break;

	case 2:
		cout << "Enter programmer data: id, fullname(not separated with space), base salary, seniority, worker assessment, " << endl
			<< "number of awards and percentage of full time hours(0-100). Separate all with spaces." << endl;

		cin >> id >> fullName >> baseSalary >> seniority >> workerAssessment >> numOfAwards >> percentageOfFullTimeHours;
		m_dep.addProgrammer(id, fullName, baseSalary, seniority, workerAssessment, numOfAwards, percentageOfFullTimeHours);
		break;

	case 3:
		cout << "Enter software architect data: id,  fullname(not separated with space), base salary, seniority, " << endl
			<< "worker assessment, number of awards and percentage of full time hours(0-100), " << endl
			<< " Do they have Phd?(insert 0 or 1 (0-no, 1 yes)) Separate all with spaces." << endl;

		cin >> id >> fullName >> baseSalary >> seniority >> workerAssessment >> numOfAwards >> percentageOfFullTimeHours
			>> hasPHD;

		m_dep.addSoftwareArchitect(id, fullName, baseSalary, seniority, workerAssessment,
			numOfAwards, percentageOfFullTimeHours, NULL, hasPHD);
		break;

	case 4:
		cout << "Enter team leader data: id, fullname(not separated with space), base salary, seniority, worker assessment, " << endl
			<< "number of awards and percentage of full time hours(0-100). Separate all with spaces." << endl;

		cin >> id >> fullName >> baseSalary >> seniority >> workerAssessment >> numOfAwards >> percentageOfFullTimeHours;
		m_dep.addTeamLeader(id, fullName, baseSalary, seniority, workerAssessment, numOfAwards, percentageOfFullTimeHours);
		break;

	case 5:
		cout << "Enter project manager data: id, full name, base salary, seniority and project cost. " << endl
			<< "Separate all with spaces(except for full name)." << endl;

		cin >> id >> fullName >> baseSalary >> seniority >> projectCost;
		m_dep.addProjectManager(id, fullName, baseSalary, seniority, projectCost, &this->m_dep);
		break;

	case 6:
		m_state = MAIN_MENU;
		break;
	default:
		cout << "wrong option." << endl;
	}
}

void Menu::printOptionsMenu()
{
	int input;
	long id;
	stringstream stream;
	cout << "  Printing options:" << endl
		<< "1. Print employee info" << endl
		<< "2. Print final report" << endl
		<< "3. Print top paid employee" << endl
		<< "4. Print total salary" << endl
		<< "5. Print average salary" << endl
		<< "6. Print one employee type list " << endl
		<< "7. return to main menu" << endl << endl
		<< "Your choice?(insert number between 1-6)" << endl;

	cin >> input;

	switch (input)
	{
	case 1:
		cout << "Enter the id of the employee to print their info: " << endl;
		cin >> id;
		m_dep.getEmployee(id);
		cout << *(m_dep.getEmployee(id));
		break;

	case 2:
		cout << m_dep.printFinalReport(stream).str().c_str();
		break;

	case 3:
		cout << "Top paid employee is:" << endl;
		m_dep.printTopPayedEmployee(stream);
		break;

	case 4:
		cout << "The total salary is:" << m_dep.getTotalSalary() << endl;
		break;

	case 5:
		cout << "The average salary is:" << m_dep.getAverageSalary() << endl;
		break;

	case 6:
		cout << "Enter Employee type 0:programmer 1:Software architect 2:Team leader" << endl <<
			    "3:project manager 4:administration worker" << endl;
		cin >> input;

		 m_dep.printAll(stream , (Position)input);
		 cout << stream.str().c_str();

	case 7:
		m_state = MAIN_MENU;
		break;

	default:
		cout << "Wrong choice." << endl;
	}
}

Menu::~Menu()
{}