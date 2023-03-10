#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "Employee.h"
#include "Programmer.h"
#include "SoftwareArchitect.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "AdministrationWorker.h"


using namespace std;

//The core of the entire project. Every main menu option is implemented here.


class Department
{
public:
	Department();
	Department(int workerAssesmentForAward_, float ratioForAward_, bool isProfitable_) throw (char*);
	Department(string& inputFileName_);
	~Department();

	Employee* getEmployee(int id_);
	void setWorkerAssessmentForAward(int workerAssesmentForAward_) throw (char *);
	int getWorkerAssessmentForAward() const { return m_workerAssesmentForAward; }
	void setRatioForAward(float ratioForAward_) throw (char *);
	float getRatioForAward() const { return m_ratioForAward; }
	void setIsProfitable(bool isProfitable_) { m_isProfitable = isProfitable_; }
	bool isProfitable() const { return m_isProfitable; }
	int getAverageBaseProgrammerSalary();
	int getAverageSalary();
	int getTotalSalary();
	unsigned int getDepartmentSize() const { return m_department.size(); }
	void readInputFile(string& inputFileName_);

	void printEmployeeInfo(ostream& out, Employee* employee_) const;
	void printAll(ostream& out, enum Position pos_);
	void printTopPayedEmployee(ostream& out);
	stringstream& printFinalReport(stringstream& out);

	void storeFinalReport(string& fileName_, stringstream& out);

	void addProgrammer(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_,
		int percentageOfFullTimeHours_) throw(char*);

	void addFemaleProgrammer(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_,
		int percentageOfFullTimeHours_) throw(char*);

	void addSoftwareArchitect(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_,
		int percentageOfFullTimeHours_, Programmer* trainee_,
		bool hasPHD_)throw(char*);

	void addTeamLeader(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int workerAssessment_, int numOfAwards_,
		int percentageOfFullTimeHours_)throw(char*);

	void addProjectManager(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int projectCost_, Department* department_)throw(char*);

	void addAdministrationWorker(long id_, string& fullName_,
		int baseSalary_, int seniority_,
		int workerAssessment_, bool isStudent_)throw(char*);

	void removeEmployee(int id_);

private:

	bool checkIfProgrammer(Employee* employee_);
	bool checkIfTeamLeader(Employee* employee_);
	bool checkIfSoftwareArchitect(Employee* employee_);
	bool checkIfProjectManager(Employee* employee_);
	bool checkIfAdministrationWorker(Employee* employee_);

	int m_workerAssesmentForAward;
	float m_ratioForAward;
	bool m_isProfitable;
	map<int, Employee*> m_department;
};

#endif