
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

using namespace std;

using namespace boost::asio;

using namespace boost;

using namespace boost::posix_time;


void Run(SerialStream& serial, TimeData& times)


try {


	std::string t_str;
	//string c;


	getline(serial, t_str);

	std::cout << t_str;

	if (!times.CheckTime(times.beginHours, times.beginMins, times.endHours, times.endMins)) {

		std::cout << "Time is not valid" << std::endl;
		return;

	};

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



}

catch (TimeoutException&) {
	serial.clear(); //Don't forget to clear error flags after a timeout
	cerr << "Timeout occurred" << endl;

}
