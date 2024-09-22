#pragma once
#ifndef _APPOINTMENT
#define _APPOINTMENT


#include "Hospital.hpp"
#include "Person.hpp"
class Appointment
{
public:
	Appointment();
	~Appointment();

	Person* person;
	Hospital* hospital;
	time_t date;

	void set_appointment(Person* person, Hospital* hospital, int day);	// the day index during simulation
	void output(ostream& f, bool head=false);
	void load(vector <string> row);
	void replase(Person* p);
	void replase(Hospital* h);

	static void save(List<Appointment*>* list, const char* filename);
	static void load_data(List<Appointment*> *list, const char* filename);
	static bool compare(Appointment* p1, Appointment* p2);
private:

};

Appointment::Appointment()
{
}

Appointment::~Appointment()
{
	person = NULL;
	hospital = NULL;
}

void Appointment::set_appointment(Person* person, Hospital* hospital, int day)
{
	this->person = person;
	this->hospital = hospital;
	time(&date);
	date += day;
}

void Appointment::output(ostream& f, bool head)
{
	if (head)
	{
		f << "id_number\tname" << '\t' << "hospital" << '\t' << "date" << endl;
		return;
	}
	f << person->id_number << '\t' << person->name << '\t' << hospital->name << '\t' << date << endl;
}

void Appointment::load(vector <string> row)
{
	Person* p = new Person();
	Hospital* h = new Hospital();
	p->id_number = row[0];
	h->name = row[2];
	date = atoi(row[3].c_str());
}

void Appointment::load_data(List<Appointment*> *list, const char* filename)
{
	Appointment* p;
	CSV csv;
	csv.readFromFile(filename);
	for (int i = 1;i < csv.rowsNum();i++)
	{
		p = new Appointment();
		p->load(csv.getRow(i));
		list->append(p);
	}
}

bool Appointment::compare(Appointment* p1, Appointment* p2)
{
	return Person::compare(p1->person, p2->person);
}

void Appointment::save(List<Appointment*>* list, const char* filename)
{
	Appointment* p;
	fstream f;

	f.open(filename, ios::out);
	p = list->getitem(0);
	p->output(f, true);
	p->output(f);
	for (int i = 1; i < list->getlength(); i++)
	{
		p = list->getitem(i);
		p->output(f);
	}
	f.close();
}

void Appointment::replase(Hospital* h)
{
	delete hospital;
	hospital = h;
}

void Appointment::replase(Person* p)
{
	delete person;
	person = p;
}

#endif // !_APPOINTMENT
