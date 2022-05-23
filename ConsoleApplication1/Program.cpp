
#include <iostream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <socketapi.h>
#include <boost/bind.hpp>
#include "Run.h"
#include <cpr/cpr.h>



using namespace boost::asio;

using namespace boost;

using namespace boost::posix_time;


//const std::string DEVICEID = "EXAMPLE_DEVICE_HASH";
const std::string  DEVICEID = "JOEMAMA";





void SendEmail() {

	std::string bodySplit1 = R"({"p_microbit_id": ")";

	std::string bodySplit2 = R"("})";

	std::string body = bodySplit1 + DEVICEID + bodySplit2;


	// send request

	auto r = cpr::Post(cpr::Url{ "https://warm-ravine-35986.herokuapp.com/email" },
		cpr::Body{ body },
		cpr::Header{ { "Content-Type", "application/json" } });

	std::cout << "Returned Status: " << r.text << std::endl;


}




void Run(SerialStream& serial) {



	TimeData times;




	if (!times.CheckTime(DEVICEID)) {

		std::cout << "Time is not valid" << std::endl;
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		return;

	};

	std::cout << "Time is valid" << std::endl;



	//Data sent needs to be in the format of: DAT: TRUE <\n> or 44 41 54 3a 20 54 72 75 65 0d 0a in hex. S

	try {

		std::string t_str;

		serial >> t_str;


		getline(serial, t_str);


		if (t_str.empty()) {
			std::cout << "empty" << std::endl;
			return;

		}


		std::cout << t_str << std::endl;


		SendEmail();





		Poco::Thread::sleep(10000);

		// We put thread to sleep simply to not overwhelm the server

	}

	catch (TimeoutException&) {
		serial.clear(); //Don't forget to clear error flags after a timeout
		std::cerr << "Timeout occurred" << std::endl;

	}


}


