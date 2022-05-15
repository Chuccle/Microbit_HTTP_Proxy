
#include "TimeData.h"
#include "iostream"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>


bool TimeData::CheckTime(int const& beginHours, int const& beginMins, int const& endHours, int const& endMins) {

	//better to pass by reference and pointers here if we can simply because copying each parameter is going to be high in memory (long long being 8 bytes)

	//Make this a pointer since we don't want to be constantly copy and recalling for each condition
	time_t* currentUnixTime = new time_t(time(0));

	//instantiate tm class
	struct tm currentTime;


	//using address of our tm class, we take in the current time ponter to populate it
	localtime_s(&currentTime, currentUnixTime);


	int TotalSec1, TotalSec2, CurrentSec;

	TotalSec1 = (beginHours * 3600) + (beginMins * 60);

	TotalSec2 = (endHours * 3600) + (endMins * 60);

	CurrentSec = (currentTime.tm_hour * 3600) + (currentTime.tm_min * 60);


	if (beginHours < endHours) {

		if (!(CurrentSec >= TotalSec1 && CurrentSec <= TotalSec2))
		{

			std::cout << "outside of range in option 1" << "\n";

			currentUnixTime = NULL;

			delete currentUnixTime;

			return false;

		}


	}
	else if (beginHours > endHours) {


		TotalSec2 += 86400;
		CurrentSec += 86400;


		if (!(CurrentSec >= TotalSec1 && CurrentSec <= TotalSec2))
		{

			std::cout << "outside of range in option 2" << "\n";

			currentUnixTime = NULL;

			delete currentUnixTime;

			return false;

		}



	}
	else {

		std::cout << "ranges are equal" << "\n";

		currentUnixTime = NULL;

		delete currentUnixTime;

		return false;

	}


	currentUnixTime = NULL;

	delete currentUnixTime;

	return true;

}




