
#include "TimeData.h"
#include "iostream"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <boost/thread.hpp>
#include <cpr/cpr.h>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>



struct Schedule {


	time_t beginUnixTime;

	//Will always be an additional day more
	time_t endUnixTime;


};




void TimeData::FetchTime(std::string const& DEVICEID_2) {

	std::string bodySplit1 = R"({"p_microbit_id": ")";

	std::string bodySplit2 = R"("})";

	std::string body = bodySplit1 + DEVICEID_2 + bodySplit2;



	// send request

	auto r = cpr::Post(cpr::Url{ "https://warm-ravine-35986.herokuapp.com/updateschedule" },
		cpr::Body{ body },
		cpr::Header{ { "Content-Type", "application/json" } });


	boost::property_tree::ptree pt;

	std::istringstream is(r.text);

	boost::property_tree::json_parser::read_json(is, pt);


	beginHours = stoi(pt.get<std::string>("begin_hours"));
	beginMins = stoi(pt.get<std::string>("begin_minutes"));
	endHours = stoi(pt.get<std::string>("end_hours"));
	endMins = stoi(pt.get<std::string>("end_minutes"));



};




bool TimeData::CheckTime(std::string const& DEVICEID) {


	FetchTime(DEVICEID);


	if (beginHours == endHours && beginMins == endMins) {

		return true;

	}



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




	if (beginHours <= endHours) {

		return (currentUnixTime >= beginUnixTime && currentUnixTime <= endUnixTime);

	}

	else if (beginHours > endHours) {

		return (currentUnixTime >= beginUnixTime || currentUnixTime <= endUnixTime);

	}

}
