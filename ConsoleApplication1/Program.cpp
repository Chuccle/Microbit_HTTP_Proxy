
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



using namespace boost::asio;

using namespace boost;

using namespace boost::posix_time;



const std::string DEVICEID = "EXAMPLE_DEVICE_HASH";






void Run(SerialStream& serial) {


	//Data sent needs to be in the format of: DAT: TRUE <\n> or 44 41 54 3a 20 54 72 75 65 0d 0a in hex. S


	TimeData times = { 17, 32 , 16, 46 };



	if (!times.CheckTime(times.beginHours, times.beginMins, times.endHours, times.endMins)) {


		std::cout << "Time is not valid" << std::endl;
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		return;

	};

	std::cout << "Time is valid" << std::endl;




	try {

		std::string t_str;

		serial >> t_str;


		getline(serial, t_str);


		if (t_str == "") {
			std::cout << "empty" << std::endl;
			return;

		}

		std::cout << t_str << std::endl;
		//set this to the route inside our server which handles the email
		//we also need to send the unique device ID to the server to identify the user
		Poco::URI uri("https://www.google.com");

		Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

		std::string path(uri.getPathAndQuery());

		if (path.empty()) path = "/";

		// send request
		Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path);

		session.sendRequest(req);

		Poco::Net::HTTPResponse res;

		std::cout << "Response Status = " << res.getStatus() << std::endl;

		std::cout << "Response Reason = " << res.getReason() << std::endl;

		Poco::Thread::sleep(10000);

		// We put thread to sleep simply to not overwhelm the server

	}

	catch (TimeoutException&) {
		serial.clear(); //Don't forget to clear error flags after a timeout
		std::cerr << "Timeout occurred" << std::endl;

	}
}