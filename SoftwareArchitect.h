#ifndef SOFTWAREARCHITECT_H
#define SOFTWAREARCHITECT_H

#include "Programmer.h"

using namespace std;

#define TRAINEE_COEFFICIENT 0.2 // Coefficient used in the salary calculation formula for Software Architect
#define PHD_COEFFICIENT 0.3     // " " " " " " " " " "

class Programmer;

class SoftwareArchitect : public Programmer
{
public:
	SoftwareArchitect();
	SoftwareArchitect(long id_, string& fullName_,
	                  int baseSalary_, int seniority_,
		              int workerAssessment_, int numOfAwards_,
		              int percentageOfFullTimeHours_, Programmer* trainee_,
		              bool hasPHD_) throw(const char*);

	~SoftwareArchitect() {}

	void setHasPHD(bool hasPHD_);
	bool getHasPHD() { return m_hasPHD; }
	void setTrainee(Programmer* trainee_) throw(char*);
	Programmer* getTrainee() { return m_trainee; }

	virtual int calcSalary() const;
	void virtual info(ostream& out) const;
	virtual bool operator==(Employee& other_) const;
	virtual void promote(enum Position, Department& department) { cout << "Can't promote this employee" << endl; }
private:
	Programmer* m_trainee;
	bool m_hasPHD;
};

#endif