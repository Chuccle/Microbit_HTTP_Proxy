#include "serialstream.h"
#include "Run.h"


int main(void)
{

	//Initialise our objects...
	//Default times
	SerialOptions options;
	options.setDevice("COM4");
	options.setBaudrate(115200);
	options.setTimeout(boost::posix_time::seconds(2));

	SerialStream serial(options);
	serial.exceptions(std::ios::badbit | std::ios::failbit); //Important!

	while (true)
		Run(serial);

	return 0;

}




