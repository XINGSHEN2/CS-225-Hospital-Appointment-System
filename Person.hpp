#pragma once
#ifndef _PERSON
#define _PERSON

#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Global.h"
#include "List.hpp"
#include "Hospital.hpp"
#include "csv.hpp"

using namespace std;

#define MAX_PERSON_COUNT	100
#define SORT_BY_NAME		1
#define SORT_BY_PROFESSION	2
#define SORT_BY_AGE_GROUP	3

class Person
{
public:
	Person();
	~Person();
	
	string id_number;
	string name;
	string e_mail;
	string phone;
	BIRTHDAY birthday;
	ADDRESS address;
	int profession;
	RISK risk;
	AGE_GROUP age_group;
	time_t timestamp;
	Hospital* hospital;
	unsigned int key;
	int waiting_days;

	int get_age();
	void get_hospital(List <Hospital*>* list);
	void set_age_group();
	void set_timestamp();
	void load(vector <string> row);
	void save(ofstream& f);
	void show(bool head=false, int property_count = 3);
	void reg();
	void generate_key();

	static bool compare(Person* p1, Person* p2);
	static void generate_data();
	static void load_data(List <Person*>* list, const char* filename);
	static void show_sortid();
	static void set_sortid(int id);
	static bool equal(Person* p1, Person* p2);
	static int sortid;

};

int Person::sortid = SORT_BY_NAME;

Person::Person()
{
	name = "";
	phone = "";
	e_mail = "";
	timestamp = 0;
	hospital = NULL;
	key = 0;
}

Person::~Person()
{
}

int Person::get_age()
{
	time_t timep;
	struct tm p;
	time(&timep);					// get current time
	gmtime_s(&p, &timep);
	return (p.tm_year - birthday.year + 1900);	// get person's age
}

void Person::set_timestamp()		// »ñÈ¡registrationµÄtimestamp
{
	time(&timestamp);
}

// set current person age group
void Person::set_age_group()
{
	int age = get_age();
	if (age <= CHILDREN)
	{
		age_group = CHILDREN;
	}
	else if (age <= ADOLESCENT)
	{
		age_group = ADOLESCENT;
	}
	else if (age <= YOUNG_ADULT)
	{
		age_group = YOUNG_ADULT;
	}
	else if (age <= ADULT)
	{
		age_group = ADULT;
	}
	else if (age <= SENIOR)
	{
		age_group = SENIOR;
	}
	else if (age <= ELDERLY_PEOPLE)
	{
		age_group = ELDERLY_PEOPLE;
	}
	else
	{
		age_group = OLD_PEOPLE;
	}

}

// get a hospital with min distance for the current person 
void Person::get_hospital(List <Hospital *> *list)
{
	int min_distance = MAX_DISTANCE, distance = 0;
	Hospital* p;
	for (int i=0; i<list->getlength(); i++)
	{
		p = (*list)[i];
		distance = (p->address.x - address.x) * (p->address.x - address.x) + (p->address.y - address.y) * (p->address.y - address.y);
		if (min_distance > distance)
		{
			min_distance = distance;
			hospital = p;
		}
		p++;
	}
}

// register a person
void Person::reg()
{
	set_timestamp();		// set timestamp
	generate_key();			// at the same time, generate key for sorting
}

// save a person to the file stream f
void Person::save(ofstream& f)
{
	f << id_number << endl;
	f << name << endl;
	f << e_mail << endl;
	f << phone << endl;
	f << birthday.year << '\t' << birthday.month << '\t' << birthday.day << endl;
	f << address.x << '\t' << address.y << endl;
	f << profession << endl;
	f << risk << endl;
	f << age_group << endl;
	f << timestamp << endl;
	if (hospital != NULL)
		f << hospital->name << endl;
	else
		f << endl;
}

// load a person from a csv file line
void Person::load(vector <string> row)
{
	int i;
	id_number = row[0];
	name = row[1];
	e_mail = row[2];
	phone = row[3];
	birthday.year = atoi(row[4].c_str());
	birthday.month = atoi(row[5].c_str());
	birthday.day = atoi(row[6].c_str());
	address.x = atoi(row[7].c_str()); 
	address.y = atoi(row[8].c_str());
	profession = atoi(row[9].c_str());
	risk = (RISK)atoi(row[10].c_str());
	set_age_group();
	timestamp = atoi(row[12].c_str());
	hospital = NULL;
}

void Person::generate_data()
{
	ofstream f("Person.txt");
	f << MAX_PERSON_COUNT << endl;
	Person person;	// create a demo person object
	for (int i = 0; i < MAX_PERSON_COUNT; i++)
	{
		person.id_number = std::to_string(11120000 + i);	// generate demo data
		person.name = "demo_" + std::to_string(i);
		person.birthday.year = 1950 + rand() % 72;
		person.birthday.day = (rand() % 28) + 1;
		person.birthday.month = (rand() % 12) + 1;
		person.risk = RISK(rand() % 4);
		person.address.x = rand() % MAX_ADDRESS;
		person.address.y = rand() % MAX_ADDRESS;
		person.e_mail = person.id_number + "@zju.edu.cn";
		person.phone = "12345678901";
		person.set_age_group();
		person.save(f);
	}
	f.close();
}

// using person properties to generate key
void Person::generate_key()
{
	struct tm p;
	gmtime_s(&p, &timestamp);

	key = (((int)risk) << 28) + (profession << 24) + (((int)age_group) << 16) + ((p.tm_year - 1900) << 8) + (p.tm_mon << 4) + p.tm_mday;
}

void Person::show(bool head, int property_count)
{
	if (head)
	{
		cout << "id_number" << '\t' << "name" << '\t' << "profession" << '\t' << "risk\t" << "age_group\ttimestamp" << endl;
		return;
	}
	cout << id_number << '\t' << name << '\t' << profession << '\t' << risk << '\t' << age_group << '\t' << timestamp << endl;
	if (property_count > 4)
	{
		cout << e_mail << '\t' << endl;
		cout << phone << '\t' << birthday.year << birthday.month << birthday.day << '\t';
		cout << '(' << address.x << ',' << address.y << ')';
		cout << profession << '\t';
		cout << risk << '\t';
		
		if (hospital != NULL)
			cout << hospital->name << endl;
	}
}

// load pserson data from a file to a person list
void Person::load_data(List <Person*> *list, const char * filename)
{
	Person* p;
	CSV csv;
	csv.readFromFile(filename);
	for (int i = 1;i < csv.rowsNum();i++)
	{
		p = new Person();
		p->load(csv.getRow(i));
		list->append(p);
	}
}

void Person::set_sortid(int id)
{
	Person::sortid = id;
}

bool Person::compare(Person* p1, Person* p2)
{
	switch (Person::sortid)
	{
	case SORT_BY_NAME:
		// cout << p1->name << '\t' << p2->name << '\t' << p1->name.compare(p2->name) << endl;
		return p1->name < p2->name;
	case SORT_BY_PROFESSION:
		return p1->profession < p2->profession;
	case SORT_BY_AGE_GROUP:
		return p1->age_group < p2->age_group;
	default:
		return p1->id_number < p2->id_number;
	}
}

bool Person::equal(Person* p1, Person *p2)
{
	return p1->id_number == p2->id_number;
}

void Person::show_sortid()
{
	switch (Person::sortid)
	{
	case SORT_BY_AGE_GROUP:
		cout << "age_group" << endl;
		break;
	case SORT_BY_NAME:
		cout << "name" << endl;
		break;
	case SORT_BY_PROFESSION:
		cout << "profession" << endl;
		break;
	default:
		break;
	}
}

#endif // !_PERSON
