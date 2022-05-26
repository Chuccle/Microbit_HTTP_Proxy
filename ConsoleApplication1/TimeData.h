#pragma once

#include <string>


class TimeData
{

public:

	int beginHours, beginMins, endHours, endMins;

public:

	bool CheckTime(std::string const& DEVICEID);

private:

	void FetchTime(std::string const& DEVICEID_2);


};



