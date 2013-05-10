//
//  main.cpp
//  P2PServer
//
//  Created by Wen ShaoHong on 10/25/12.
//  Copyright (c) 2012 Centny. All rights reserved.
//

#include <iostream>
#include "P2PBuilder/P2PBuilder.h"
#include <SocketBuilder.h>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::udp;
using namespace SocketBuilder;
enum {
	max_length = 1024
};

int main(int argc, char* argv[]) {
	try {
        io_service ios;
		UDPBuilder udp(ios,10000);
		for (;;) {
			char data[max_length];
			udp::endpoint sender_endpoint;
			size_t length = udp.receive(boost::asio::buffer(data, max_length),
					sender_endpoint);
			udp.send(boost::asio::buffer(data, length), sender_endpoint);
			std::cout << "client:" << sender_endpoint.port() << std::endl;
		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
