#include "TeamLeader.h"
#include <algorithm>
#include <iterator>

TeamLeader::TeamLeader() 
{}

TeamLeader::TeamLeader(long id_, string& fullName_, int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_) throw(const char*)
	: Programmer(id_, fullName_, baseSalary_, seniority_, workerAssessment_, numOfAwards_, percentageOfFullTimeHours_)
{

}

int TeamLeader::calcSalary() const
{
	return getBaseSalary() * (1 + TEAM_LEADER_SENIORITY_COEF * getSeniority()) * (1 + TEAM_SIZE_COEF * m_team.size());
}

void TeamLeader::info(ostream& out) const
{
	out << ", Final Salary: " << calcSalary() << ", " << getFullName() << " is a team leader of " << m_team.size() << " programmers." << endl;
}

void TeamLeader::operator+=(Programmer* programmer_)  
{
	if (dynamic_cast<TeamLeader*>(programmer_))
	{
		cout << "Attempted to add a team leader to team leader's team." << endl;
		return;
	}
	m_team.push_back(programmer_);	
}

void TeamLeader::operator-=(Programmer* programmer_)
{
	auto result = find(begin(m_team), end(m_team), programmer_); 

	if (result == m_team.end())
	{
		cout << "Team member not found." << endl;
		return;
	}
	m_team.erase(result);
}


bool TeamLeader::operator==(Employee& employee_) const
{
	return Programmer::operator==(employee_);
}

Employee* TeamLeader::getEmployee(int id_)
{
	return m_team[id_];
}