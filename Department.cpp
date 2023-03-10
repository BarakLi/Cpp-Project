#include "Department.h"
#include <algorithm>
#include <fstream>

Department::Department(int workerAssesmentForAward_, float ratioForAward_,
	bool isProfitable_) throw (char*)
	:m_isProfitable(isProfitable_)
{
	setRatioForAward(ratioForAward_);
	setWorkerAssessmentForAward(workerAssesmentForAward_);
}

Department::Department() :Department(80, 4, true)
{}

Department::~Department()
{
	//Using for_each to iterate over the department map and delete every item. for the function, using lambda function.
	for_each(m_department.begin(), m_department.end(), [](const auto& pair_)
	{
		delete pair_.second;
	});
}
//algorithm to find employee
Employee* Department::getEmployee(int id_)
{
	auto result = m_department.find(id_);

	if (result == m_department.end())
	{
		cout << "Employee not found." << endl;
		return NULL;
	}

	return result->second;
}

void  Department::addProgrammer(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_,
	int percentageOfFullTimeHours_) throw(char*)
{
	m_department[id_] = new Programmer(id_, fullName_, baseSalary_,
		seniority_, workerAssessment_,
		numOfAwards_, percentageOfFullTimeHours_);
}

void  Department::addFemaleProgrammer(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_,
	int percentageOfFullTimeHours_) throw(char*)
{
	m_department[id_] = new Programmer(id_, fullName_, baseSalary_,
		seniority_, workerAssessment_,
		numOfAwards_, percentageOfFullTimeHours_, *this);
}

void  Department::addSoftwareArchitect(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_,
	int percentageOfFullTimeHours_, Programmer* trainee_,
	bool hasPHD_)throw(char*)
{
	m_department[id_] = new SoftwareArchitect(id_, fullName_,
		baseSalary_, seniority_,
		workerAssessment_, numOfAwards_,
		percentageOfFullTimeHours_, trainee_,
		hasPHD_);
}

void Department::addTeamLeader(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_,
	int percentageOfFullTimeHours_)throw(char*)
{
	m_department[id_] = new TeamLeader(id_, fullName_,
		baseSalary_, seniority_,
		workerAssessment_, numOfAwards_,
		percentageOfFullTimeHours_);
}

void Department::addProjectManager(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int projectCost_, Department* department_)throw(char*)
{
	m_department[id_] = new ProjectManager(id_, fullName_,
		baseSalary_, seniority_,
		projectCost_, this);
}

void Department::addAdministrationWorker(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, bool isStudent_)throw(char*)
{
	m_department[id_] = new AdministrationWorker(id_, fullName_,
		baseSalary_, seniority_,
		workerAssessment_, isStudent_);
}

void Department::removeEmployee(int id_)
{
	Employee* employee = getEmployee(id_);
	if (!employee)
	{
		cout << "Employee wasn't found." << endl;
		return;
	}

	delete employee;
	m_department.erase(id_);
}

void Department::printEmployeeInfo(ostream& out, Employee* employee_) const
{
	out << *employee_;
}

void Department::setWorkerAssessmentForAward(int workerAssesmentForAward_) throw (char *)
{
	if ((workerAssesmentForAward_ < 40 || workerAssesmentForAward_ > 100) && workerAssesmentForAward_ != 0)
	{

		throw  "Invalid worker Assessment for award value.";
	}

	m_workerAssesmentForAward = workerAssesmentForAward_;
}

void Department::setRatioForAward(float ratioForAward_) throw (char *)
{
	if (ratioForAward_ < 0)
	{

		throw  "Invalid ratio for award value.";
	}
}

int Department::getAverageBaseProgrammerSalary()
{
	int averageSalary = 0;
	int counter = 0;

	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		if (dynamic_cast<Programmer*>(iterator->second) &&
			!(dynamic_cast<SoftwareArchitect*>(iterator->second)) &&
			!(dynamic_cast<TeamLeader*>(iterator->second)))
		{
			averageSalary += iterator->second->getBaseSalary();
			counter++;
		}
	}

	averageSalary /= counter;

	return averageSalary;
}

int Department::getAverageSalary()
{
	int meanSalary = 0;
	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		meanSalary += iterator->second->calcSalary();
	}
	meanSalary /= m_department.size(); //getDepartmentSize()
	return meanSalary;
}

int Department::getTotalSalary()
{
	int totalSalary = 0;
	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		totalSalary += iterator->second->calcSalary();
	}
	return totalSalary;
}

void Department::printAll(ostream& out, enum Position pos_)
{
	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		bool isCorrectEmployee = false;

		switch (pos_)
		{
		case SOFTWAREARCHITECT:
			isCorrectEmployee = checkIfSoftwareArchitect(iterator->second);
			break;
		case TEAMLEADER:
			isCorrectEmployee = checkIfTeamLeader(iterator->second);
			break;
		case PROGRAMMER:
			isCorrectEmployee = checkIfProgrammer(iterator->second);
			break;
		case PROJECTMANAGER:
			isCorrectEmployee = checkIfProjectManager(iterator->second);
			break;
		case ADMINISTRATIONWORKER:
			isCorrectEmployee = checkIfAdministrationWorker(iterator->second);
			break;
		default:
			cout << "Wrong position input" << endl;
		}

		if (isCorrectEmployee)
		{
			out << *(iterator->second);
		}
	}
}


void Department::printTopPayedEmployee(ostream& out)
{
	Employee* employee = m_department.begin()->second;
	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		if (employee->calcSalary() < iterator->second->calcSalary())
		{
			employee = iterator->second;
		}
	}

	out << *employee;
}

stringstream& Department::printFinalReport(stringstream& out)
{
	out << "---------------Final Department Report----------------" << endl <<
		"......................................................" << endl <<
		"Department size: " << m_department.size() << " employees." <<
		" The department is" << (m_isProfitable ? " profitable." : " not profitable.") << endl << endl <<
		"----Employee list:----" << endl;

	for (auto iterator = m_department.begin(); iterator != m_department.end(); ++iterator)
	{
		out << *(iterator->second);
	}

	out << endl;

	return out;
}

void Department::storeFinalReport(string& fileName_, stringstream& out_)
{
	ofstream outputfile(fileName_);

	outputfile << out_.str();
}

void Department::readInputFile(string& inputFileName_)
{
	ifstream inputFile(inputFileName_);

	long id = 0;
	string fullName;
	int baseSalary = 0;
	int seniority = 0;
	int workerAssessment = 0;
	int isStudent = 0;
	int projectCost = 0;
	int numOfAwards = 0;
	int percentageOfFullTimeHours = 100;
	int hasPHD = 0;

	if (inputFile.bad())
	{
		cout << "Can't open file" << endl;
	}

	int pos = 0;

	while (inputFile >> pos)
	{
		switch (pos)
		{
		case SOFTWAREARCHITECT:
			inputFile >> id >> fullName >> baseSalary >> seniority >> workerAssessment >>
				numOfAwards >> percentageOfFullTimeHours >> hasPHD;
			addSoftwareArchitect(id, fullName, baseSalary, seniority, workerAssessment,
				numOfAwards, percentageOfFullTimeHours, NULL, hasPHD);
			break;

		case TEAMLEADER:
			inputFile >> id >> fullName >> baseSalary >> seniority >> workerAssessment >>
				numOfAwards >> percentageOfFullTimeHours;
			addTeamLeader(id, fullName, baseSalary, seniority, workerAssessment,
				numOfAwards, percentageOfFullTimeHours);
			break;

		case PROGRAMMER:
			inputFile >> id >> fullName >> baseSalary >> seniority >> workerAssessment >>
				numOfAwards >> percentageOfFullTimeHours;
			addProgrammer(id, fullName, baseSalary, seniority, workerAssessment,
				numOfAwards, percentageOfFullTimeHours);
			break;

		case PROJECTMANAGER:
			inputFile >> id >> fullName >> baseSalary >> seniority >> projectCost;
			addProjectManager(id, fullName, baseSalary, seniority, projectCost, this);
			break;

		case ADMINISTRATIONWORKER:
			inputFile >> id >> fullName >> baseSalary >> seniority >> workerAssessment >> isStudent;
			addAdministrationWorker(id, fullName, baseSalary, seniority, workerAssessment, isStudent);
			break;

		default:
			cout << "Wrong position input" << endl;
			return;
		}
	}
}

Department::Department(string& inputFileName_)
{
	readInputFile(inputFileName_);
}

bool Department::checkIfProgrammer(Employee* employee_)
{
	return (dynamic_cast<Programmer*>(employee_) &&
		!(dynamic_cast<TeamLeader*>(employee_)) &&
		!(dynamic_cast<SoftwareArchitect*>(employee_)));
}
bool Department::checkIfTeamLeader(Employee* employee_)
{
	return (dynamic_cast<TeamLeader*>(employee_));
}
bool Department::checkIfSoftwareArchitect(Employee* employee_)
{
	return (dynamic_cast<SoftwareArchitect*>(employee_));
}
bool Department::checkIfProjectManager(Employee* employee_)
{
	return (dynamic_cast<ProjectManager*>(employee_));
}
bool Department::checkIfAdministrationWorker(Employee* employee_)
{
	return (dynamic_cast<AdministrationWorker*>(employee_));
}