#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define ASIO_STANDALONE
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"
#include "lib/lazy.h"

//using namespace std;

int main() {
    std::cout << "src/main.cpp called" << std::endl;

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
//    const char *endpoint_address = "93.184.216.34"; // www.example.com
    const char *endpoint_address = "172.217.162.206"; // www.youtube.com Brazil's mirror (SAO PAULO)
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(endpoint_address, error_code), 80);

    // Socket can be described as a doorway or bridge "the means through"
    // we're connecting to our endpoint
    asio::ip::tcp::socket socket1(context);

    // Tell the socket to try a connection

    socket1.connect(endpoint, error_code);

    if (!error_code)
    {
        std::cout << "Connected to \"" << endpoint_address << "\"" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to \""<< endpoint_address <<"\"" << std::endl
        << "Details:\n" << error_code.message() << std::endl;
    }

    if (socket1.is_open())
    {
        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        // asio::ip::tcp::socket (write_some) -> Sending data to our socket/doorway
        // asio::buffer -> Buffer is just a container of an array of bytes and its length
        socket1.write_some(asio::buffer(sRequest.data(), sRequest.size()), error_code);

        // asio::ip::tcp::socket (wait) -> bad because it doesn't count for the end of stream
        // will certainly cut the stream in half when the data-stream is too big!
        socket1.wait(socket1.wait_read);

        // Gathering the data returned from the endpoint (this is an asynchronous operation)
        size_t bytes = socket1.available();

        std::cout << "Bytes available: \"" << bytes << "\"" << std::endl;

        if (bytes > 0)
        {
            std::vector<char> vBuffer(bytes);

            // asio::ip::tcp::socket (read_some) ->  Is used to read data from the stream socket
            socket1.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), error_code);

            for (auto c : vBuffer)
                std::cout << c;
        }
    }
    return 0;
}