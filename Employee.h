#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#pragma warning(disable : 4996)
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum Position { PROGRAMMER, SOFTWAREARCHITECT, TEAMLEADER, PROJECTMANAGER, ADMINISTRATIONWORKER }; //Employee's Role
#define SENIORITY_MULTIPLIER 0.1 // Coefficient used for Employee's salary calculation 


class Department;
class Employee
{
public:
	Employee();
	Employee(long id_, string& fullName_, int baseSalary_, int seniority_, int workerAssessment_ = 0) throw(const char *);
	virtual ~Employee() { }

	void setID(long id_) throw(const char*);
	long getID() const { return m_id; }
	void setFullName(const string& fullName_) throw(const char*);
	string getFullName() const { return m_fullName; }
	void setBaseSalary(int baseSalary_) throw(const char*);
	unsigned int getBaseSalary() const { return m_baseSalary; }
	void setSeniority(int seniority_) throw(const char*);
	unsigned int getSeniority() const { return m_seniority; }
	void setWorkerAssessment(int workerAssessment_) throw(const char*);
	unsigned int getWorkerAssessment() const { return m_workerAssessment; }

	friend ostream& operator<<(ostream& out, const Employee& employee_);
	virtual bool operator==(const Employee& other_) const;

	virtual int calcSalary() const = 0;
	virtual void info(ostream& out) const = 0; //Print employee information
	virtual void promote(enum Position, Department& department_) { cout << "Can't promote this employee" << endl; }

private:
	long m_id;
	string m_fullName;
	unsigned int m_baseSalary;
	unsigned int m_seniority;
	unsigned int m_workerAssessment;

	void ValidateString(const string& str_) throw(const char*); // a method to validate string input

	Employee(const Employee& other_); //Disable CC'tor
	Employee& operator=(const Employee& other_); //Disable assign operator

};

#endif // !EMPLOYEE_H