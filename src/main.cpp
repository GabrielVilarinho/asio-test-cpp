#include <iostream>

#define ASIO_STANDALONE
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

//using namespace std;

int main() {
    asio::error_code error_code;
    // ASIO needs a unique space to perform stuff and does it in
    // this space called io_context handles any specific platform
    // requirements

    asio::io_context context;

    // ASIO needs an endpoint to request a connection see more about
    // it uses a naming convention in namespace referring to the protocol
    // to be more concise, see IP and TCP protocols and network protocols
    // in general to know more!

    // As showed below we're resolving the following namespace:
    //
    // "Use from ASIO the protocol IP, and from IP use the TCP protocol
    // to create an endpoint"
    //
    // endpoint as the door or the destination we're trying to reach

//    const char *ip = "93.184.216.34";
//    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ip, error_code), 80);
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", error_code), 80);

    // Socket can be described as a doorway or bridge "the means through"
    // we're connecting to our endpoint

    asio::ip::tcp::socket socket1(context);

    // Tell the socket to try a connection

    socket1.connect(endpoint, error_code);

    if(!error_code)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect... \n Details:\n" << error_code.message() << std::endl;
    }

    std::cout << "src/main.cpp called" << std::endl;
    return 0;
}