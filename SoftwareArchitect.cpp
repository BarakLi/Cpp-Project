#include "SoftwareArchitect.h"
#include "TeamLeader.h"

SoftwareArchitect::SoftwareArchitect(long id_, string& fullName_,
									 int baseSalary_, int seniority_,
									 int workerAssessment_, int numOfAwards_,
									 int percentageOfFullTimeHours_, Programmer* trainee_,
									 bool hasPHD_) throw(const char*)
: Programmer(id_, fullName_, baseSalary_, seniority_, workerAssessment_, numOfAwards_, percentageOfFullTimeHours_)
{
	setHasPHD(hasPHD_);
	setTrainee(trainee_);
}

SoftwareArchitect::SoftwareArchitect() : m_hasPHD(false), m_trainee(NULL)
{}

void SoftwareArchitect::setHasPHD(bool hasPHD_)
{
	m_hasPHD = hasPHD_;
}

void SoftwareArchitect::setTrainee(Programmer* trainee_) throw(char*)
{
	if (dynamic_cast<TeamLeader*>(trainee_) || dynamic_cast<SoftwareArchitect*>(trainee_))
	{
		throw "Invalid type of programmer recieved.";
	}

	m_trainee = trainee_;
}

void SoftwareArchitect::info(ostream& out) const
{
	if (m_hasPHD)
	{
		out << ", Has PHD" << ", Final Salary: " << calcSalary() << ", position: software architect. " << endl;
		return;
	}
	out << ", Final Salary: " << calcSalary() << ", position: software architect. " << endl;
}

//Simple formula to calculate software architect's salary
int SoftwareArchitect::calcSalary() const
{

	return getBaseSalary() * (1 + SENIORITY_MULTIPLIER) *
		                    (1 + PHD_COEFFICIENT * m_hasPHD) *
		                    (1 + TRAINEE_COEFFICIENT * !(!(m_trainee))); // A trick to turn m_trainee to boolean
}

bool SoftwareArchitect::operator==(Employee& other_) const
{
	if (!Employee::operator==(other_))
	{
		return false;
	}

	SoftwareArchitect* sArchitect = dynamic_cast<SoftwareArchitect*>(&other_);

	if (sArchitect)
	{
		return (this->m_hasPHD == sArchitect->m_hasPHD && this->m_trainee == sArchitect->m_trainee);
	}
	return false;
}