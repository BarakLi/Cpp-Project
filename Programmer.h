#ifndef  PROGRAMMER_H
#define PROGRAMMER_H
#include "Employee.h"

class Department;

using namespace std;

#define TEAM_LEADER_SENIORITY_COEF 0.1
#define TEAM_SIZE_COEF 0.05
#define PROMOTE_COEF 0.5

class SoftwareArchitect;
class TeamLeader;

class Programmer : public Employee
{
public:
	Programmer();
	Programmer(long id_, string& fullName_, int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_) throw(const char*);
	Programmer(long id_, string& fullName_, int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_, Department& department_) throw(const char*);
	virtual ~Programmer() {}

	void setNumOfAwards(int numOfAwards_) throw(const char*);
	unsigned int getnumOfAwards() const { return m_numOfAwards; }
	void setPercentageOfFullTimeHours(int percentageOfFullTimeHours_) throw(const char*);
	unsigned int getPercentageOfFullTimeHours() const { return m_percentageOfFullTimeHours; }

	bool isEligableForPromotion() const;
	virtual void promote(Position position_, Department& department);

	void virtual info(ostream& out) const;
	virtual bool operator==(Employee& other_) const;
	virtual int calcSalary() const;

private:
	unsigned int m_numOfAwards;
	unsigned int m_percentageOfFullTimeHours;
};

#endif