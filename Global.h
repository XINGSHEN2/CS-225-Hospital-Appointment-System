#pragma once
#ifndef _GLOBAL
#define _GLOBAL
#define MAX_LENGTH 255
#define MAX_DISTANCE 0x00FFFFFF
#define MAX_ADDRESS	50
#define START_DATE	1649431536

#include <string>


enum RISK
{
	NO_RISK, LOW_RISK, MEDIUM_RISK, HIGH_RISK
};

enum AGE_GROUP
{
	CHILDREN = 12, ADOLESCENT = 18, YOUNG_ADULT = 35, ADULT = 50, SENIOR = 65, ELDERLY_PEOPLE = 75, OLD_PEOPLE = 100
};

struct ADDRESS
{
	int x, y;
};

struct BIRTHDAY
{
	int year, month, day;
};
#endif