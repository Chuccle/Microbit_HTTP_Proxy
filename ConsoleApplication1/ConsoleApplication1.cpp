
#include <iostream>
#include "TimeData.h"


int main(void)
{

	TimeData times = { 00, 32 , 22, 24 };


	if (!times.CheckTime(times.beginHours, times.beginMins, times.endHours, times.endMins)) {


		std::cout << "Time is not valid" << std::endl;
		return 0;

	};

	std::cout << "Time is valid" << std::endl;
	return 0;
}