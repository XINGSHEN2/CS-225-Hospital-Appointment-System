#include <iostream>
#include <fstream>
#include <string>
#include "Hospital.h"
using namespace std;


Hospital hospital[MAX_HOSPITAL_COUNT];

Hospital::Hospital()
{
	name = "";
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

	ifstream f("Hospital.txt");
	if (!f.is_open())
	{
		cout<<"cannot open the file"<< endl;
	}
	int i = 0;
	while (!f.eof())
	{
		f >> hospital[i].name;
		f >> hospital[i].address.x>> hospital[i].address.y;
		f >> hospital[i].capacity;
		i++;
	}
	f.close();
}