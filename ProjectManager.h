#ifndef  PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <map>
#include "Employee.h"
#include "Department.h"

class Department;

using namespace std;

#define COST_CRITERIA_REWARD 10000 
#define ASSESSMENT_CRITERIA_REWARD 10000
#define PROFITABLE_DEPARTMENT_BONUS 50000

class ProjectManager : public Employee
{
public:
	ProjectManager();
	ProjectManager(long id_, string& fullName_, int baseSalary_, int seniority_, int projectCost_, Department* department_) throw(const char*);

	virtual ~ProjectManager() {}

	void setProjectCost(int projectCost_) throw(char*);
	void setDepartment(Department* department_);
	int getProjectCost() const { return m_projectCost; }
	Employee* getEmployee(int id_);
	void operator+=(Employee* employee_) throw (char*); 
	void operator-=(int id_);

	float calcProjectToWorkerRatio() const;
	float calcTeamAssesment() const;

	void virtual info(ostream& out) const;
	virtual int calcSalary() const;
	virtual bool operator==(Employee& other_) const;
private:
	map<int, Employee* > m_team; 
	unsigned int m_projectCost;
	Department* m_department;
};

#endif
