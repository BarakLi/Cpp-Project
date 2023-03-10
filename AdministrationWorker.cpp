#include "AdministrationWorker.h"

#include "AdministrationWorker.h"

AdministrationWorker::AdministrationWorker()
	: m_isStudent(false)
{}

AdministrationWorker::AdministrationWorker(long id_, string& fullName_,
	int baseSalary_, int seniority_,
	int workerAssessment_, bool isStudent_) throw(char*)
	: Employee(id_, fullName_, baseSalary_, seniority_, workerAssessment_), m_isStudent(isStudent_)
{}

void AdministrationWorker::setIsStudent(bool isStudent_)
{
	m_isStudent = isStudent_;
}

int AdministrationWorker::calcSalary() const
{
	return (getBaseSalary() * (1 - (1 - STUDENT_COEFFICIENT) * m_isStudent) * (1 + SENIORITY_MULTIPLIER * getSeniority()));
}

void AdministrationWorker::info(ostream& out) const
{
	if(m_isStudent)
	{ 
		out << ", Is student" << ", Final Salary " << calcSalary() << ", position: administration worker. "<< endl;
		return;
	}
	out << ", Final Salary " << calcSalary() << ", position: administration worker. " << endl;

}

bool AdministrationWorker::operator==(Employee& other_) const
{
	if (!Employee::operator==(other_))
	{
		return false;
	}

	AdministrationWorker* adminWorker = dynamic_cast<AdministrationWorker*>(&other_);
	if (!adminWorker)
	{
		return false;
	}
	return m_isStudent == adminWorker->getIsStudent();
}