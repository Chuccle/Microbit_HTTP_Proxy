
#include <iostream>
#include "serialstream.h"
#include "TimeData.h"
#include "Run.h"
#include <boost/asio.hpp>

using namespace std;

int main(void)
{


	//Initialise our objects...
	//Default times
	SerialOptions options;
	options.setDevice("COM4");
	options.setBaudrate(115200);
	options.setTimeout(boost::posix_time::seconds(2));

	SerialStream serial(options);
	serial.exceptions(ios::badbit | ios::failbit); //Important!


	while (true)
		Run(serial);



	return 0;

}




