#ifndef Datatype_h
#define Datatype_h

#include <ostream>
#include <string>

struct name {
	std::string fname, lname, birthday;

	bool operator<(name) const;
	bool operator>(name) const;
	void operator=(name);
};

struct birthdate {
	std::string fname, lname, birthday;

	bool operator<(birthdate) const;
	bool operator>(birthdate) const;
	void operator=(birthdate);
};

std::ostream& operator<<(std::ostream& os, const name& na)
{
	return os << na.fname << " " << na.lname << '\t' << na.birthday;
}

std::ostream& operator<<(std::ostream& os, const birthdate& bi)
{
	return os << bi.fname << " " << bi.lname << '\t' << bi.birthday;
}

bool name::operator<(name person) const
{
	if (this->lname < person.lname)
		return true;
	else if (lname > person.lname)
		return false;

	if (this->lname == person.lname) {
		if (this->fname < person.fname)
			return true;
		else if (fname >= person.fname)
			return false;
	}
}

bool name::operator>(name person) const
{
	if (this->lname > person.lname)
		return true;
	else if (lname < person.lname)
		return false;

	if (this->lname == person.lname) {
		if (this->fname > person.fname)
			return true;
		else if (fname <= person.fname)
			return false;
	}
}

void name::operator=(name person) {
	this->fname = person.fname;
	this->lname = person.lname;
	this->birthday = person.birthday;
}

bool birthdate::operator<(birthdate person) const
{
	if (this->birthday < person.birthday)
		return true;
	else if (birthday >= person.birthday)
		return false;
}

bool birthdate::operator>(birthdate person) const
{
	if (this->birthday > person.birthday)
		return true;
	else if (birthday <= person.birthday)
		return false;
}

void birthdate::operator=(birthdate person) {
	this->fname = person.fname;
	this->lname = person.lname;
	this->birthday = person.birthday;
}

#endif