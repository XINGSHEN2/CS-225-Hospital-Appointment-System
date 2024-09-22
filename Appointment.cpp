// Appointment.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
// #include <unistd.h>                  // use this line in a linux system
// #include "Person.h"
// #include "Hospital.h"
#include "Processing.hpp"
using namespace std;

int main()
{
    char key;
	Processing processing;
    int day = 1;
    string s;
    bool person_loaded = false;
    bool hospital_loaded = false;
    bool registered = false;
    bool queued = false;
    bool appointed = false;
	string id_number = "";

    while (true)
    {
        system("cls");          // using system("clear"); in a linux system
        cout << "Welcome to using register & appointment system" << endl;
        cout << "Day\t" << day << endl;
        cout << "Press key to using the system" << endl;
        cout << "H: load and show hospital data" << endl;
		cout << "P: load and show person data for today" << endl;
        cout << "R: register all persons" << endl;
        cout << "Q: queue all persons" << endl;
        cout << "A: appoint all available hospital treatment" << endl;
        cout << "W: withdraw a person" << endl;
        cout << "O: report" << endl;
        cout << "N: next day" << endl;
        cout << "X: exit" << endl;
        cin >> key;
        cin.get();
        switch (key)
        {
        case 'X':
        case 'x':   return 0;
        case 'N':
        case 'n':
            day++;
            person_loaded = false;
            registered = false;
            queued = false;
            appointed = false;
            processing.clear_reg();
            break;
        case 'P':
        case 'p':
            if (!hospital_loaded)
            {
                cout << "please load hospital data first..." << endl;
                break;
            }
            if (!person_loaded)
            {
				s = "person" + std::to_string(day) + ".csv";
				processing.load_person(s.c_str());
            }
            processing.show_persons();
            person_loaded = true;
            break;
        case 'H':
        case 'h':
            if (!hospital_loaded)
            {
				processing.load_hospital("hospital.csv");
                hospital_loaded = true;
            }
            processing.show_hospitals();
            break;
        case 'R':
        case 'r':
            if (!registered)
            {
                processing.reg();
                registered = true;
            }
            processing.show_persons();
            break;
        case 'Q':
        case 'q':
            if (!registered)
            {
                cout << "please register first..." << endl;
                break;
            }
            if (!queued)
            {
                processing.queue();
                queued = true;
            }
            cout << "all persons all queued..." << endl;
            break;
        case 'W':
        case 'w':
            if (!registered || !queued)
            {
                cout << "please register or queue first..." << endl;
                break;
            }
            if (!appointed)
            {
                cout << "not appointed yet, please appoint first" << endl;
                break;
            }
            Person* p;
            cout << "please input the person's id_number..." << endl;
            cin >> id_number;
            // cin.get();
            if ((p = processing.withdraw(id_number)) == NULL)
                cout << id_number << '\t' << p->name << "\thas been withdrawed" << endl;
            break;
        case 'A':
        case 'a':
			if (!registered || !queued)
			{
				cout << "please register or queue first..." << endl;
				break;
			}
            if (!appointed)
            {
                processing.appointment(day);
                appointed = true;
            }
            processing.show_appointment();
            break;
        case 'O':
        case 'o':
            while (key!='X')
            {
			    system("cls");          // using system("clear"); in a linux system
                cout << "Sub-menu of report menu item" << endl;
                cout << "-T: Treated  persons" << endl;
                cout << "-R: Registered persons" << endl;
                cout << "-Q: Queuing Persons" << endl;
                cout << "-S: Sorting property:\t";
                Person::show_sortid();
                cout << "-P: rePorting cycle:\t";
				cout << "-X: exit to main menu" << endl;
			    cin >> key;
			    cin.get();
                switch (key)
                {
                case 'T':
                case 't':
                    break;
                case 'R':
                case 'r':
                    break;;
                case 'Q':
                case 'q':
                    break;
                case 'S':
                case 's':
                    cout << "choose sorting property: (N) name, (A) Age group, (P) Profession" << endl;
                    cin >> key;
                    switch (key)
                    {
                    case 'A':
                    case 'a':
                        Person::set_sortid(SORT_BY_AGE_GROUP);
                        break;
                    case 'P':
                    case 'p':
                        Person::set_sortid(SORT_BY_PROFESSION);
                        break;
                    case 'N':
                    case 'n':
                        Person::set_sortid(SORT_BY_NAME);
                        break;
                    }
                    break;
                case 'X':
                case 'x':
                    key = 'X';
                    break;
                default:
                    break;
                }
			}
            break;
        default:
            break;
        }
		cout << "press any key to return main menu..." << endl;
		cin.get();
    }

}
