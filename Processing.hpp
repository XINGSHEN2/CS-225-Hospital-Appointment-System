#pragma once

#ifndef _PROCESSING
#define _PROCESSING

#include <iostream>

#include "List.hpp"
#include "Person.hpp"
#include "Hospital.hpp"
#include "Fibonacci.hpp"
#include "appointment.hpp"

#define REPORT_WEEKLY	0
#define REPORT_MONTHLY	1

class Processing
{
public:
	Processing();
	~Processing();

	List <Person *> *person_list;
	List <Hospital *> *hospital_list;
	FibHeap <Person*>* queue_heap;
	List <Appointment*>* appointment_list;

	void next_day();
	void show_persons();
	void show_hospitals();
	void set_person_hospital();
	void show_appointment();
	void reg();
	void clear_reg();			// clear reg num while the next day starts
	void queue();
	void appointment(int day);
	void load_person(const char* filename);
	void load_hospital(const char* filename);
	void load_appointment(const char* filename);
	void save_appointment(const char* filename);
	void report_weekly(int day);
	void report_monthly(int day);
	Person* withdraw(string id_number);

	//static int report_cycle;
	//static void set_report_cycle(int cycle);
	//static void show_report_cycle();
};

Processing::Processing()
{
	person_list = new List<Person*>();
	hospital_list = new List<Hospital*>();
	queue_heap = new FibHeap<Person*>();
	appointment_list = new List<Appointment*>();
}


Processing::~Processing()
{
	delete person_list;
	delete hospital_list;
	delete queue_heap;
	delete appointment_list;
}

void Processing::show_hospitals()
{
/*	Hospital* p;
	for (int i = 0;i < hospital_list->getlength(); i++)
	{
		p = (*hospital_list)[i];
		p->show();
	}*/
	hospital_list->prettyprint();
}

void Processing::show_persons()
{
	person_list->prettyprint();
}

void Processing::set_person_hospital()
{
	Person* p;
	for (int i = 0;i < person_list->getlength();i++)
	{
		p = person_list->getitem(i);
		if (p->hospital == NULL)
			p->get_hospital(hospital_list);
	}
}

void Processing::reg()
{
	Person* p;
	for (int i = 0;i < person_list->getlength();i++)
	{
		p = person_list->getitem(i);
		p->reg();
	}
}

void Processing::queue()
{
	//FibNode<Person*>* node;
	Person* p;
	for (int i = 0;i < person_list->getlength();i++)
	{
		p = person_list->getitem(i);
		if (NULL == queue_heap->search(p))		// if the person is not in the queue, add the person
			queue_heap->insert(p);
	}
	queue_heap->print();
}

void Processing::appointment(int day)
{
	int whole_capacity = 0;
	for (int i = 0; i < hospital_list->getlength(); i++)
		whole_capacity += (*hospital_list)[i]->capacity;

	for (int i = 0; i < whole_capacity; i++)
	{
		Person* p;
		Hospital* phospital;
		Appointment* appointment = new Appointment();
		p = queue_heap->get_min();		// find a person with highest priority
		if (p == NULL)
			break;
		queue_heap->removeMin();		// remove he from the heap
		cout << i << endl;
		if (p->hospital->reg_num < p->hospital->capacity)	// check if the default hospital can arrange the appointment or not
		{
			p->hospital->reg_num++;
			appointment->set_appointment(p, p->hospital, day);	// set appointment
		}
		else
		{
			for (int i = 0; i < hospital_list->getlength(); i++)
			{
				phospital = hospital_list->getitem(i);
				if (phospital->reg_num < phospital->capacity)
				{
					appointment->set_appointment(p, phospital, day);	// set appointment
					phospital->reg_num++;
					// phospital->person_list.append(p);
					break;
				}
			}
		}
		appointment_list->append(appointment);
	}
	Appointment::save(appointment_list, "appoint.csv");
}

void Processing::show_appointment()
{
	Appointment* p;
	p = appointment_list->getitem(0);
	p->output(cout, true);
	p->output(cout);
	for (int i = 0; i < appointment_list->getlength(); i++)
	{
		p = appointment_list->getitem(i);
		p->output(cout);
	}
}

void Processing::load_person(const char* filename)
{
	Person::load_data(person_list, filename);
	person_list->sort_items(Person::compare);
	set_person_hospital();
}

void Processing::load_hospital(const char* filename)
{
	Hospital::load_data(hospital_list, filename);
}


void Processing::save_appointment(const char* filename)
{
	Appointment::save(appointment_list, filename);
}

Person* Processing::withdraw(string id_number)
{
	Appointment* p;
	for (int i = 0; i < appointment_list->getlength(); i++)
	{
		p = appointment_list->getitem(i);
		if (p->person->id_number == id_number)
			appointment_list->remove(i);
		return p->person;
	}
	return NULL;
}

void Processing::load_appointment(const char* filename)
{
	List <Appointment*>* list = new List<Appointment*>();
	Appointment::load_data(list, filename);
	int index;
	for (int i = 0; i < list->getlength(); i++)			// merge appointment list loaded from csv file
	{
		Person* p;
		Hospital* h;
		Appointment* appointment=list->getitem(i);
		p = appointment->person;
		h = appointment->hospital;
		index = person_list->search(p, Person::equal);
		if (index > 0)
			appointment->replase(person_list->getitem(index));
		index = hospital_list->search(h, Hospital::equal);
		if (index > 0)
			appointment->replase(hospital_list->getitem(index));
	}
}

void Processing::next_day()
{
	for (int i = 0; i < person_list->getlength(); i++)
	{

	}
}

void Processing::report_monthly(int day)
{
	return;
}

void Processing::report_weekly(int day)
{
	struct tm p;
	time_t date;
	time(&date);
	date += day;
	gmtime_s(&p, &date);
	if (p.tm_wday == 6)
	{
		for (int i = 0;i < appointment_list->getlength(); i++)
		{
			Appointment* pa;
			pa = appointment_list->getitem(i);
			if (pa->date > date - 7)
				pa->person->show(false);
		}
	}
}

void Processing::clear_reg()
{
	Hospital* p;
	for (int i = 0; i < hospital_list->getlength(); i++)
	{
		p = hospital_list->getitem(i);
		p->clear_reg();
	}
}

#endif // !_PROCESSING
