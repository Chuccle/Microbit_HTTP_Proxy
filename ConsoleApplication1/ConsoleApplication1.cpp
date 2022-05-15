
#include <iostream>
#include "serialstream.h"
#include "TimeData.h"
#include "Run.h"
#include <boost/asio.hpp>

using namespace std;

int main(void)
{

	TimeData times = { 00, 32 , 19, 24 };

	SerialOptions options;
	options.setDevice("COM3");
	options.setBaudrate(115200);
	options.setTimeout(boost::posix_time::seconds(10));

	SerialStream serial(options);
	serial.exceptions(ios::badbit | ios::failbit); //Important!

	//simulate a populated serial
	serial << "Hello world" << endl;

	while (true) {
		Run(serial, times);
	}
	return 0;

}




