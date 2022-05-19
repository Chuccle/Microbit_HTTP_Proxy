
#include "TimeData.h"
#include "iostream"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>



struct Schedule {


	time_t beginUnixTime;

	//Will always be an additional day more
	time_t endUnixTime;


};


//TODO Add function to update the begin and end times from database





bool TimeData::CheckTime(int const& beginHours, int const& beginMins, int const& endHours, int const& endMins) {

	//better to pass by reference and pointers here if we can simply because copying each parameter is going to be high in memory (long long being 8 bytes)
	time_t currentUnixTime = time(0);
	time_t beginUnixTime = 0;
	time_t endUnixTime = 0;


	//instantiate tm class
	struct tm currentTime;


	//using address of our tm class, we take in the current time ponter to populate it
	localtime_s(&currentTime, &currentUnixTime);

	currentTime.tm_sec = 00;

	currentTime.tm_min = beginMins;
	currentTime.tm_hour = beginHours;

	beginUnixTime = _mktime64(&currentTime);

	currentTime.tm_min = endMins;
	currentTime.tm_hour = endHours;

	endUnixTime = _mktime64(&currentTime);

	
	static Schedule Current = { beginUnixTime - 86400, endUnixTime };
	static Schedule Next = { beginUnixTime,  endUnixTime + 86400 };




	if (beginHours <= endHours) {

		std::cout << beginUnixTime << "\n";;
		std::cout << currentUnixTime << "\n";;
		std::cout << endUnixTime << "\n";

		if (currentUnixTime >= beginUnixTime && currentUnixTime <= endUnixTime)
		{

			std::cout << "inside of range in option 1" << "\n";


			return true;

		}


	}

	else if (beginHours > endHours) {

		//remove a day from the calculated time or the LB of my range will be too high
		//find diffence in seconds, divide into 2, add to lb and ub



		if (currentUnixTime >= Current.endUnixTime) {

			std::cout << "swapping times" << "\n";


			Current = Next;

			Next.beginUnixTime += 86400;

			Next.endUnixTime += (86400 * 2);


		}



		// if currenttime is more than current.end and less than next.begin

		if (currentUnixTime >= Current.beginUnixTime && currentUnixTime <= Current.endUnixTime) {

			std::cout << "inside of range in option 2" << "\n";
			return true;

		}

		return false;

	}

}

