#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "Global.h"
#include "List.hpp"
#include "csv.hpp"

#define TIME_SLOT 1
#define MAX_HOSPITAL_COUNT 10
#define MAX_CANPACITY	10

using namespace std;

class Hospital
{
public:
	Hospital();
	~Hospital();

	string name;
	ADDRESS address;
	int capacity;
	int reg_num;

	void save(ofstream& f);
	void load(ifstream& f);
	void show(bool head = false, int property_count = 3);
	void clear_reg();

	static void load_data();		// 静态函数，装载数据
	static void load_data(List <Hospital*> *list, const char* filename);
	static void generate_data();
	static bool equal(Hospital* h1, Hospital* h2);

private:

};

Hospital::Hospital()
{
	name = "";
	reg_num = 0;
}

Hospital::~Hospital()
{
}

void Hospital::load(ifstream& f)
{
	f >> name;
	f >> address.x >> address.y;
	f >> capacity;
}

void Hospital::save(ofstream& f)
{
	f << name << endl;
	f << address.x << '\t' << address.y << endl;
	f << capacity << endl;
}

void Hospital::generate_data()
{
	ofstream f("Hospital.txt");
	Hospital hospital;
	f << MAX_HOSPITAL_COUNT << endl;
	for (int i = 0; i < MAX_HOSPITAL_COUNT; i++)
	{
		hospital.name = "demo_hospital_" + std::to_string(i);
		hospital.capacity = (rand() % MAX_CANPACITY) + 1;
		hospital.address.x = rand() % MAX_ADDRESS;
		hospital.address.y = rand() % MAX_ADDRESS;
		hospital.save(f);
	}
	f.close();
}

void Hospital::load_data()
{
}

void Hospital::load_data(List <Hospital*> *list, const char * filename)
{
	cout << "loading hospital data" << endl;
	Hospital* p;
	CSV csv;
	csv.readFromFile(filename);
	for (int i = 1;i < csv.rowsNum();i++)
	{
		vector <string> row = csv.getRow(i);
		p = new Hospital();
		p->name = row[0];
		p->address.x = atoi(row[1].c_str());
		p->address.y = atoi(row[2].c_str());
		p->capacity = atoi(row[3].c_str());
		list->append(p);
	}
}

void Hospital::show(bool head, int property_count)
{
	if (head)
	{
		cout << "name" << '\t' << "\taddress" << '\t' << "capacity" << '\t' << "reg_num" << endl;
		return;
	}
	cout << name << '\t' << '(' << address.x << ',' << address.y << ')' << '\t' << capacity << '\t' << reg_num;
	cout << endl;
}

bool Hospital::equal(Hospital* h1, Hospital* h2)
{
	return h1->name == h2->name;
}

void Hospital::clear_reg()
{
	reg_num = 0;
}