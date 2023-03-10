#ifndef TEAM_LEADER
#define TEAM_LEADER

#include "Programmer.h"
#include <vector>

using namespace std;

class Programmer;

class TeamLeader : public Programmer
{
public:
	TeamLeader();
	TeamLeader(long id_, string& fullName_, int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_, int percentageOfFullTimeHours_) throw(const char*);
	virtual ~TeamLeader() {}

	Employee* getEmployee(int id_);

	void operator-=(Programmer* programmer_);
	void operator+=(Programmer* programmer_);
	virtual bool operator==(Employee& other_) const;
	virtual void promote(enum Position, Department& department_) { cout << "Can't promote this employee" << endl; }

	virtual int calcSalary() const;
	virtual void info(ostream& out) const;
	

private:
	vector<Programmer*> m_team;
};

#endif
