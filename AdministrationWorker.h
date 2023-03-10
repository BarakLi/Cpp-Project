#ifndef ADMINISTRATIONWORKER_H
#define ADMINISTRATIONWORKER_H
#include "Employee.h"

#define STUDENT_COEFFICIENT 0.7 // Coefficient used for administration worker's salary calculation 

using namespace std;

class AdministrationWorker : public Employee
{
public:
	AdministrationWorker();
	AdministrationWorker(long id_, string& fullName_, int baseSalary_, int seniority_, int workerAssessment_, bool isStudent_) throw(char*);
	virtual ~AdministrationWorker() {}

	void setIsStudent(bool isStudent_);
	bool getIsStudent()  const { return m_isStudent; }

	bool operator==(Employee& other_) const;

	int virtual calcSalary() const;
	void virtual info(ostream& out) const;

private:
	bool m_isStudent;
};

#endif
