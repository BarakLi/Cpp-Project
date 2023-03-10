#include "Employee.h"

Employee::Employee() : m_id(0), m_fullName("Unknown"), m_baseSalary(0), m_seniority(0), m_workerAssessment(0)
{}

Employee::Employee(long id_, string& fullName_, int baseSalary_, int seniority_, int workerAssessment_) throw(const char *)
{
	setID(id_);
	setFullName(fullName_);
	setBaseSalary(baseSalary_);
	setSeniority(seniority_);
	setWorkerAssessment(workerAssessment_);
}

//For every exception there is a string stream created that is casted into string to be thrown.

void Employee::setID(long id_) throw(const char*)
{
	if (id_ < 0)
	{

		throw "Invalid ID.";
	}

	m_id = id_;
}

void Employee::setFullName(const string& fullName_) throw(const char*)
{
	ValidateString(fullName_);
	m_fullName = fullName_;
}

//Validate that the string doesn't include digits or non-letter characters
void Employee::ValidateString(const string& str_) throw(const char*) 
{
	bool isValid = true;

	int len = str_.length();
	for (int i = 0; i < len; i++)
	{
		if (!(str_.c_str()[i] >= 'a' && str_.c_str()[i] <= 'z' ||
			(str_.c_str()[i] >= 'A' && str_.c_str()[i] <= 'Z')))
		{
			isValid = false;
			break;
		}
	}

	if (str_.length() == 0 || !isValid)
	{

		throw  "Invalid name.";
	}
}

void Employee::setBaseSalary(int baseSalary_) throw(const char*)
{
	if (baseSalary_ < 0)
	{

		throw "Invalid Salary value.";
	}

	m_baseSalary = baseSalary_;
}

void Employee::setSeniority(int seniority_) throw(const char*)
{
	if (seniority_ < 0)
	{


		throw "Invalid value of seniority.";
	}

	m_seniority = seniority_;
}

void Employee::setWorkerAssessment(int workerAssessment_) throw(const char*)
{
	if ((workerAssessment_ < 40 || workerAssessment_ > 100) && workerAssessment_ != 0)
	{

		throw "Invalid worker Assessment value.";
	}

	m_workerAssessment = workerAssessment_;
}

ostream& operator<<(ostream& out, const Employee& employee_)
{

	out << "ID: " << employee_.m_id << ", Name: " <<
		employee_.m_fullName << ", Base Salary: " <<
		employee_.m_baseSalary << ", Seniority: " <<
		employee_.m_seniority << ", Assesment: " <<
		employee_.m_workerAssessment << ", ";

	employee_.info(out);
	return out;

}

bool Employee:: operator==(const Employee& other_) const
{
	return (m_id == other_.m_id &&
			m_fullName == other_.m_fullName &&
			m_baseSalary == other_.m_baseSalary &&
			m_seniority == other_.m_seniority &&
			m_workerAssessment == other_.m_workerAssessment);
}