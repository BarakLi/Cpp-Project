#include "Programmer.h"
#include "TeamLeader.h"
#include "SoftwareArchitect.h"
#include "Department.h"

Programmer::Programmer()
	: m_numOfAwards(0), m_percentageOfFullTimeHours(0)
{}

Programmer::Programmer(long id_, string& fullName_, int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_) throw(const char*)
:Employee(id_, fullName_, baseSalary_, seniority_, workerAssessment_)
{
	setNumOfAwards(numOfAwards_);
	setPercentageOfFullTimeHours(percentageOfFullTimeHours_);
}

Programmer::Programmer(long id_, string& fullName_, int baseSalary_, int seniority_,
	int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_, Department& department_) throw(const char*)
:Employee(id_, fullName_, baseSalary_, seniority_, workerAssessment_)
{
	setNumOfAwards(numOfAwards_);
	setPercentageOfFullTimeHours(percentageOfFullTimeHours_);

	if (department_.getAverageBaseProgrammerSalary() > baseSalary_)
	{
		setBaseSalary(department_.getAverageBaseProgrammerSalary());
	}
}

void Programmer::setNumOfAwards(int numOfAwards_) throw(const char*)
{
	if (numOfAwards_ < 0 || numOfAwards_ > 12)
	{
	

		throw  "Invalid number of awards.";
	}

	m_numOfAwards = numOfAwards_;
}

void Programmer::setPercentageOfFullTimeHours(int percentageOfFullTimeHours_) throw(const char*)
{
	if (percentageOfFullTimeHours_ <= 0 || percentageOfFullTimeHours_ > 100)
	{
		
		

		throw "Invalid percentage of full-time hours.";
	}
	m_percentageOfFullTimeHours = percentageOfFullTimeHours_;
}

bool Programmer::isEligableForPromotion() const
{
	if (m_numOfAwards >= 3 && getSeniority() >= 3 && getWorkerAssessment() >= 80)
	{
		return true;
	}
	return false;
}
//simple formula to calculate programmer's salary
int Programmer::calcSalary() const
{

	return (((getPercentageOfFullTimeHours() / 100) * getBaseSalary() + 3000 * getnumOfAwards()) * (1 + 0.1 * getSeniority()));
}


bool Programmer::operator==( Employee& other_) const
{
	if (!Employee::operator==(other_))
	{
		return false;
	}

	Programmer* programmer = dynamic_cast<Programmer*>(&other_);

	if (programmer) 
	{
		return (this->m_numOfAwards == programmer->m_numOfAwards && 
				this->m_percentageOfFullTimeHours == programmer->m_percentageOfFullTimeHours);
	}
	return false;
}


void Programmer::info(ostream& out_) const
{
	out_ << ", Num of awards: " <<getnumOfAwards() << 
			", % of Full time job: " << getPercentageOfFullTimeHours() << 
			", Final Salary " << calcSalary() << ", position: programmer. " << endl;
}

void Programmer::promote(Position position_, Department& department_)
{
	Employee* employee = NULL;
	string name = getFullName();
	long id = getID();
	int baseSalary = getBaseSalary();

	if (!isEligableForPromotion())
	{
		cout << "This Programmer is not eligable for promotion." << endl;
		return;
	}

	if (position_ == TEAMLEADER)
	{
		department_.addTeamLeader(getID(), name, getBaseSalary() * (1 + PROMOTE_COEF),
						          getSeniority(), getWorkerAssessment(), 0 , 100);
	}
	else if (position_ == SOFTWAREARCHITECT)
	{
		department_.addSoftwareArchitect(getID(), name, getBaseSalary() * (1 + PROMOTE_COEF),
										 getSeniority(), getWorkerAssessment(), 0, 100, NULL, false);
	}
	else
	{
		cout << "Invalid argument for promotion.";
	}

	delete this;
}