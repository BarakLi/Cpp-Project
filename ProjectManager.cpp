#include "ProjectManager.h"

ProjectManager::ProjectManager() :m_projectCost(0)
{

}

ProjectManager::ProjectManager(long id_, string& fullName_, int baseSalary_, int seniority_, int projectCost_, Department* department_) throw(const char*)
	: Employee(id_, fullName_,baseSalary_, seniority_), m_department(department_)
{
	setProjectCost(projectCost_);
}


void ProjectManager::setProjectCost(int projectCost_) throw (char*)
{
	if (projectCost_ < 0)
	{

		throw "Invalid project cost.";
	}
	
	m_projectCost = projectCost_;
}

bool ProjectManager::operator==(Employee& employee_) const
{
		if (!Employee::operator==(employee_))
		{
			return false;
		}

		ProjectManager* pManager = dynamic_cast<ProjectManager*>(&employee_);

		if (pManager)
		{
			return (this->m_projectCost == pManager->m_projectCost);
		}
		return false;
}

Employee* ProjectManager::getEmployee(int id_)
{
	return m_team[id_];
}

void ProjectManager::setDepartment(Department* department_)
{
	m_department = department_;
}

void ProjectManager::operator+=(Employee* employee_) throw (char*)
{
	if (dynamic_cast<ProjectManager*>(employee_) == NULL)
	{
		throw "NULL pointer or Project Manager insert attempt.";
	}

	//Check if employee already has been added to m_team.
	bool employeeAlreadyExist = true;
	if (m_team.find(employee_->getID()) == m_team.end())
	{
		employeeAlreadyExist = false;
	}
	if (employeeAlreadyExist)
	{
		throw "Attempted to add an exsisting employee.";
	}
	
	m_team[employee_->getID()] = employee_;
}

void ProjectManager::operator-=(int id_)
{
	if (m_team.find(id_) == m_team.end())
	{
		cout << "Employee not found." << endl;
		return;
	}
	m_team.erase(id_);
}

float ProjectManager::calcProjectToWorkerRatio() const
{
	int baseSalarySum = 0;
	for (auto iterator = m_team.begin(); iterator != m_team.end(); ++iterator)
	{
		baseSalarySum += iterator->second->getBaseSalary();
	}
	if (baseSalarySum == 0)
	{
		return 1;
	}

	return (m_projectCost / baseSalarySum);
}

float ProjectManager::calcTeamAssesment() const
{
	int meanTeamAssessment = 0;
	for (auto iterator = m_team.begin(); iterator != m_team.end(); ++iterator)
	{
		meanTeamAssessment += iterator->second->getWorkerAssessment();
	}
	
	if (meanTeamAssessment == 0)
	{
		return 0;
	}
	meanTeamAssessment /= m_team.size();
	return meanTeamAssessment;
}

void ProjectManager::info(ostream& out) const
{
	out << ", Project cost: "<< m_projectCost << ", Final Salary: "<< calcSalary() << ", position: project manager. " << endl;
}

int ProjectManager::calcSalary() const
{
	return getBaseSalary() +
		   COST_CRITERIA_REWARD * (calcProjectToWorkerRatio() > m_department->getRatioForAward()) +
		   ASSESSMENT_CRITERIA_REWARD * (calcTeamAssesment() > m_department->getWorkerAssessmentForAward() + 
		   PROFITABLE_DEPARTMENT_BONUS * m_department->isProfitable());
}