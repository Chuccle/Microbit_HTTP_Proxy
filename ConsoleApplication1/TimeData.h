#pragma once

#include <string>


class TimeData
{

public:

	bool CheckTime(std::string const& DEVICEID);

private:

	void FetchTime(std::string const& DEVICEID_2);
	int beginHours, beginMins, endHours, endMins;

};



