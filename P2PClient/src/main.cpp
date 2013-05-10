//
//  main.cpp
//  P2PClient
//
//  Created by Wen ShaoHong on 10/25/12.
//  Copyright (c) 2012 Centny. All rights reserved.
//

#include <iostream>
#include "P2PBuilder/P2PBuilder.h"
#include <SocketBuilder.h>
#include <iostream>
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
		UDPBuilder _udp(ios, "127.0.0.1", 10000);
		using namespace std;
        while (1) {
            // For strlen.
            char request[max_length] = "client message";
            size_t request_length = strlen(request);
            _udp.send(boost::asio::buffer(request, request_length));

            char reply[max_length];
            udp::endpoint sender_endpoint;
            size_t reply_length = _udp.receive(
				boost::asio::buffer(reply, max_length), sender_endpoint);
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
            std::cout << "local host: " << _udp.socket().local_endpoint().port()
				<< endl;
            bsleep(5000);
        }
		std::getchar();
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

